#!/bin/bash

function info()
{
  echo ${@} > /dev/stderr
}

function message()
{
  cat << EOI > /dev/stderr

-=-=-=-=-=-=-=-
  ${@}
-=-=-=-=-=-=-=-

EOI
}

function usage()
{
  message "Usage: ${0} <configuration_file> <fasta_file_or_dir> [<output_dir>]"
  exit 1
}

function error()
{
  info "ERROR"
  message ${@}
  exit 1
}

function determine_base()
{
  BASE="$(dirname $(readlink -f ${0}))"
}

function check_input()
{
  if [ ${#} -ne 2 -a ${#} -ne 3 ]
  then
    usage
  fi
  CONFIGURATION="${1}"
  INPUT="${2}"
  OUT="${3:--}"
  if [ \! -e ${CONFIGURATION} -o \! -e ${INPUT} ]
  then
    usage
  fi
  CONFIGURATION_NAME="$(readlink -f ${CONFIGURATION})"
  if [ -f ${INPUT} ]
  then
    INPUT_IS_FILE="yes"
  else
    INPUT_IS_FILE="no"
  fi
  INPUT_NAME="$(readlink -f ${INPUT})"

  source ${CONFIGURATION}
  : ${CPU_NUMBER:=4}
  : ${WORK_SQL:=no}
  : ${WORK_NUMERIC:=no}
  : ${WORK_COMMAND:=no}
  : ${COMMAND:=-}
  : ${WORK_HYDRO:=no}
  : ${WORK_ANCHOR:=no}
  : ${WORK_DISEMBL:=no}
  : ${WORK_DISOPRED:=no}
  : ${WORK_ISUNSTRUCT:=no}
  : ${WORK_IUPRED_LONG:=no}
  : ${WORK_IUPRED_SHORT:=no}
  : ${WORK_OND:=no}
  : ${WORK_PREDISORDER:=no}
  : ${WORK_RONN:=no}
  : ${WORK_VSL2:=no}
  : ${WORK_NETMHC_1_30C:=no}
  : ${NETMHC_1_30C_ALLELE_FILE:=NetMhc.3.0c.pseudo}
  : ${NETMHC_1_30C_LENGTH_FROM:=8}
  : ${NETMHC_1_30C_LENGTH_TO:=11}
  : ${WORK_NETMHC_1_34A:=no}
  : ${NETMHC_1_34A_ALLELE_FILE:=NetMhc.3.4a.pseudo}
  : ${NETMHC_1_34A_LENGTH_FROM:=8}
  : ${NETMHC_1_34A_LENGTH_TO:=11}
  : ${WORK_NETMHC_2_22:=no}
  : ${NETMHC_2_22_ALLELE_FILE:=NetMhcII.2.2.pseudo}
  : ${NETMHC_2_22_LENGTH_FROM:=9}
  : ${NETMHC_2_22_LENGTH_TO:=15}
  : ${WORK_NETMHCPAN_1_20C:=no}
  : ${NETMHCPAN_1_20C_ALLELE_FILE:=NetMhcPan.2.0c.pseudo}
  : ${NETMHCPAN_1_20C_LENGTH_FROM:=8}
  : ${NETMHCPAN_1_20C_LENGTH_TO:=11}
  : ${WORK_NETMHCPAN_1_24A:=no}
  : ${NETMHCPAN_1_24A_ALLELE_FILE:=NetMhcPan.2.4a.pseudo}
  : ${NETMHCPAN_1_24A_LENGTH_FROM:=8}
  : ${NETMHCPAN_1_24A_LENGTH_TO:=11}
  : ${WORK_NETMHCPAN_1_28A:=no}
  : ${NETMHCPAN_1_28A_ALLELE_FILE:=NetMhcPan.2.8a.pseudo}
  : ${NETMHCPAN_1_28A_LENGTH_FROM:=8}
  : ${NETMHCPAN_1_28A_LENGTH_TO:=11}
  : ${WORK_NETMHCPAN_2_10B:=no}
  : ${NETMHCPAN_2_10B_ALLELE_FILE:=NetMhcIIPan.1.0b.pseudo}
  : ${NETMHCPAN_2_10B_LENGTH_FROM:=9}
  : ${NETMHCPAN_2_10B_LENGTH_TO:=15}
  : ${WORK_NETMHCPAN_2_20B:=no}
  : ${NETMHCPAN_2_20B_ALLELE_FILE:=NetMhcIIPan.2.0b.pseudo}
  : ${NETMHCPAN_2_20B_LENGTH_FROM:=9}
  : ${NETMHCPAN_2_20B_LENGTH_TO:=15}
  : ${WORK_NETMHCPAN_2_30C:=no}
  : ${NETMHCPAN_2_30C_ALLELE_FILE:=NetMhcIIPan.3.0c.pseudo}
  : ${NETMHCPAN_2_30C_LENGTH_FROM:=9}
  : ${NETMHCPAN_2_30C_LENGTH_TO:=15}
  : ${WORK_NETMHCPAN_2_31A:=no}
  : ${NETMHCPAN_2_31A_ALLELE_FILE:=NetMhcIIPan.3.1a.pseudo}
  : ${NETMHCPAN_2_31A_LENGTH_FROM:=9}
  : ${NETMHCPAN_2_31A_LENGTH_TO:=15}

  if [ ${CPU_NUMBER} -le 0 ]
  then
    error "CPU number is not positive"
  fi
  if [ ${WORK_COMMAND} = 'yes' ]
  then
    if [ ${COMMAND} = '-' ]
    then
      error "Missing COMMAND"
    fi
  fi
  if [ ${WORK_NETMHC_1_30C} = 'yes' ]
  then
    NETMHC_1_30C_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHC_1_30C_ALLELE_FILE})
    if [ \! -f ${NETMHC_1_30C_ALLELE_FILE} ]
    then
      error "No file ${NETMHC_1_30C_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHC_1_34A} = 'yes' ]
  then
    NETMHC_1_34A_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHC_1_34A_ALLELE_FILE})
    if [ \! -f ${NETMHC_1_34A_ALLELE_FILE} ]
    then
      error "No file ${NETMHC_1_34A_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHC_2_22} = 'yes' ]
  then
    NETMHC_2_22_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHC_2_22_ALLELE_FILE})
    if [ \! -f ${NETMHC_2_22_ALLELE_FILE} ]
    then
      error "No file ${NETMHC_2_22_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_1_20C} = 'yes' ]
  then
    NETMHCPAN_1_20C_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_1_20C_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_1_20C_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_1_20C_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_1_24A} = 'yes' ]
  then
    NETMHCPAN_1_24A_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_1_24A_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_1_24A_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_1_24A_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_1_28A} = 'yes' ]
  then
    NETMHCPAN_1_28A_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_1_28A_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_1_28A_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_1_28A_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_2_10B} = 'yes' ]
  then
    NETMHCPAN_2_10B_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_2_10B_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_2_10B_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_2_10B_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_2_20B} = 'yes' ]
  then
    NETMHCPAN_2_20B_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_2_20B_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_2_20B_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_2_20B_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_2_30C} = 'yes' ]
  then
    NETMHCPAN_2_30C_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_2_30C_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_2_30C_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_2_30C_ALLELE_FILE}"
    fi
  fi
  if [ ${WORK_NETMHCPAN_2_31A} = 'yes' ]
  then
    NETMHCPAN_2_31A_ALLELE_FILE=$(cd $(dirname ${CONFIGURATION}); readlink -f ${NETMHCPAN_2_31A_ALLELE_FILE})
    if [ \! -f ${NETMHCPAN_2_31A_ALLELE_FILE} ]
    then
      error "No file ${NETMHCPAN_2_31A_ALLELE_FILE}"
    fi
  fi
}

function check_tools()
{
  if \
  [ \
    \! -d ${BASE}/bin -o \
    \! -x ${BASE}/bin/fasta_tool -o \
    \! -x ${BASE}/bin/parjob -o \
    \! -x ${BASE}/bin/region_fail -o \
    \! -x ${BASE}/bin/region_filter -o \
    \! -x ${BASE}/bin/epitope_fail -o \
    \! -x ${BASE}/bin/epitope_filter -o \
    \! -x ${BASE}/bin/hydro \
  ]
  then
    make -C ${BASE} clean
    make -C ${BASE} all
    message "Created ${BASE}/bin/ with tools"
  fi
}

function make_out()
{
  if [ "${OUT}" = "-" ]
  then
    OUT="$(readlink -f $(dirname ${INPUT_NAME})/$(basename ${INPUT_NAME}).out)"
  else
    OUT="$(readlink -f ${OUT})"
  fi
  rm -rf ${OUT}
  mkdir -p ${OUT} 2> /dev/null
  if [ ${?} -ne 0 ]
  then
    error "Cannot make dir ${OUT}"
  fi
}

function make_tmp()
{
  TMP="${OUT}/tmp"
  mkdir -p ${TMP} 2> /dev/null
  if [ ${?} -ne 0 ]
  then
    error "Cannot make dir ${TMP}"
  fi
}

function clean_tmp()
{
  rm -rf ${TMP}
}

function make_job()
{
  JOB="${OUT}/parjob.tasks"
  touch ${JOB}
  if [ ${?} -ne 0 ]
  then
    error "Cannot create ${JOB}"
  fi
}

function clean_job()
{
  rm -f ${JOB}
}

function make_output_name()
{
  eval $(${BASE}/bin/fasta_tool -c ${1}.${COUNT} 2> /dev/null)
  : ${DIR_1:=.}
  : ${DIR_2:=.}
  OUTPUT_NAME="${TMP}/${DIR_1}/${DIR_2}/${1}.${COUNT}"
  COUNT=$((${COUNT}+1))
}

function analyze_file_single()
{
  INPUT_NAME_NORMALIZED="$(readlink -f ${INPUT_NAME}/${1})"
  if [ ${WORK_COMMAND} = 'yes' ]
  then
    OUTPUT_NAME="$(readlink -m ${OUT}/command/${1}.${POSITION})"
    echo "${BASE}/processing.sh command ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
  fi
  if [ ${WORK_HYDRO} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh hydro ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_ANCHOR} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh anchor ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_DISEMBL} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh disembl ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_DISOPRED} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh disopred ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_ISUNSTRUCT} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh isunstruct ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_IUPRED_LONG} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh iupred_long ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_IUPRED_SHORT} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh iupred_short ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_OND} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh ond ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_PREDISORDER} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh predisorder ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_RONN} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh ronn ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_VSL2} = 'yes' ]
  then
    make_output_name ${1}
    echo "${BASE}/processing.sh vsl2 ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME}" >> $JOB
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHC_1_30C} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHC_1_30C_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHC_1_30C_LENGTH_FROM} ${NETMHC_1_30C_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhc_1_30c ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHC_1_34A} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHC_1_34A_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHC_1_34A_LENGTH_FROM} ${NETMHC_1_34A_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhc_1_34a ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHC_2_22} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHC_2_22_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHC_2_22_LENGTH_FROM} ${NETMHC_2_22_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhc_2_22 ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_1_20C} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_1_20C_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_1_20C_LENGTH_FROM} ${NETMHCPAN_1_20C_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_1_20c ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_1_24A} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_1_24A_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_1_24A_LENGTH_FROM} ${NETMHCPAN_1_24A_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_1_24a ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_1_28A} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_1_28A_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_1_28A_LENGTH_FROM} ${NETMHCPAN_1_28A_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_1_28a ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_2_10B} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_2_10B_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_2_10B_LENGTH_FROM} ${NETMHCPAN_2_10B_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_2_10b ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_2_20B} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_2_20B_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_2_20B_LENGTH_FROM} ${NETMHCPAN_2_20B_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_2_20b ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_2_30C} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_2_30C_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_2_30C_LENGTH_FROM} ${NETMHCPAN_2_30C_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_2_30c ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
  if [ ${WORK_NETMHCPAN_2_31A} = 'yes' ]
  then
    for ALLELE in $(cat ${NETMHCPAN_2_31A_ALLELE_FILE} | cut -d \  -f 1)
    do
      for EPITOPE_LENGTH in $(seq ${NETMHCPAN_2_31A_LENGTH_FROM} ${NETMHCPAN_2_31A_LENGTH_TO})
      do
        make_output_name ${1}
        echo "${BASE}/processing.sh netmhcpan_2_31a ${BASE} ${CONFIGURATION_NAME} ${INPUT_NAME_NORMALIZED} ${2} ${OUTPUT_NAME} ${ALLELE} ${EPITOPE_LENGTH}" >> $JOB
      done
    done
    WORK_COLLECT=yes
  fi
}

function analyze_file()
{
  info "ANALYZE file ${INPUT_NAME}/${1}"
  eval $(${BASE}/bin/fasta_tool -l ${INPUT_NAME}/${1} 2> /dev/null)
  : ${FASTA_LENGTH:=0}

  if [ ${FASTA_LENGTH} -gt 0 ]
  then
    for POSITION in $(seq 1 ${FASTA_LENGTH})
    do
      analyze_file_single ${1} ${POSITION}
    done
  fi
}

function analyze()
{
  WORK_COLLECT=no
  COUNT=0
  if [ ${INPUT_IS_FILE} = "yes" ]
  then
    INPUT_NAME_OLD=${INPUT_NAME}
    INPUT_NAME=$(dirname ${INPUT_NAME_OLD})
    analyze_file $(basename ${INPUT_NAME_OLD})
  else
    cd ${INPUT_NAME}
    for FILE in $(find . -type f -print)
    do
      analyze_file ${FILE}
    done
  fi
}

function work()
{
  ${BASE}/bin/parjob -n ${CPU_NUMBER} ${JOB}
}

function gzip_collect_class()
{
  for FILE in $(find ${1} -type f -name \*${2}.gz -print)
  do
    cat ${FILE} >> ${OUT}/${2}.gz
    rm -f ${FILE}
  done
}

function gzip_collect_dir
{
  gzip_collect_class ${1} hydro.load
  if [ ${WORK_NUMERIC} = 'yes' ]
  then
    gzip_collect_class ${1} region_success_numeric.load
    gzip_collect_class ${1} epitope_success_numeric.load
  fi
  gzip_collect_class ${1} region_success.load
  gzip_collect_class ${1} region_fail.load
  gzip_collect_class ${1} epitope_success.load
  gzip_collect_class ${1} epitope_fail.load
  if [ ${WORK_SQL} = 'yes' ]
  then
    gzip_collect_class ${1} hydro.sql
    if [ ${WORK_NUMERIC} = 'yes' ]
    then
      gzip_collect_class ${1} region_success_numeric.sql
      gzip_collect_class ${1} epitope_success_numeric.sql
    fi
    gzip_collect_class ${1} region_success.sql
    gzip_collect_class ${1} region_fail.sql
    gzip_collect_class ${1} epitope_success.sql
    gzip_collect_class ${1} epitope_fail.sql
  fi
}

function gzip_collect_all()
{
  for DIR_1 in ${TMP}/*
  do
    if [ -d ${DIR_1} ]
    then
      for DIR_2 in ${DIR_1}/*
      do
        info "COLLECT dir ${DIR_2}"
        gzip_collect_dir ${DIR_2}
        rm -rf ${DIR_2}
      done
      rm -rf ${DIR_1}
    fi
  done
}

determine_base
check_input ${@}
check_tools
make_out
make_tmp
make_job
message "ANALYZE"
analyze
message "WORK"
work
clean_job
if [ ${WORK_COLLECT} = 'yes' ]
then
  message "COLLECT"
  gzip_collect_all
fi
clean_tmp
message "DONE ALL, look at ${OUT}"
