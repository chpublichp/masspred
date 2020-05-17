#!/bin/bash

function error()
{
  echo "ERROR ${1}" > /dev/stderr
  exit 1
}

function check_input()
{
  if [ ${#} -ne 6 -a ${#} -ne 8 ]
  then
    error "Bad input"
  fi
  MODUL="${1}"
  BASE="${2}"
  CONFIGURATION="${3}"
  INPUT="$(readlink -f ${4})"
  INPUT_POSITION="${5}"
  OUTPUT="${6}"
  if [ ${#} -eq 8 ]
  then
    if \
    [ \
      ${MODUL} != "netmhc_1_30c" -a \
      ${MODUL} != "netmhc_1_34a" -a \
      ${MODUL} != "netmhc_2_22" -a \
      ${MODUL} != "netmhcpan_1_20c" -a \
      ${MODUL} != "netmhcpan_1_24a" -a \
      ${MODUL} != "netmhcpan_1_28a" -a \
      ${MODUL} != "netmhcpan_2_10b" -a \
      ${MODUL} != "netmhcpan_2_20b" -a \
      ${MODUL} != "netmhcpan_2_30c" -a \
      ${MODUL} != "netmhcpan_2_31a" \
    ]
    then
      error "Bad modul"
    fi
    IS_EPITOPE="yes"
    ALLELE="${7}"
    EPITOPE_LENGTH="${8}"
  else
    IS_EPITOPE="no"
  fi
}

function configuration()
{
  source ${CONFIGURATION}
  : ${WORK_SQL:=no}
  : ${WORK_COMMAND:=no}
  : ${COMMAND:=-}
  : ${WORK_NUMERIC:=no}
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

  if [ ${WORK_SQL} = 'yes' ]
  then
    SQL=-s
  else
    SQL=
  fi
}

function make_tmp()
{
  TMP="/tmp/masspred-dir-$(date +%s)-${$}"
  mkdir -p ${TMP}
  if [ ${?} -ne 0 ]
  then
    error "Cannot make ${TMP}"
  fi
}

function clean_tmp()
{
  rm -rf ${TMP}
}

function gzip_file()
{
  if [ -f ${1} ]
  then
    gzip -n -9 ${1}
  fi
}

function gzip_hydro()
{
  gzip_file ${OUTPUT}_hydro.load
  if [ ${WORK_SQL} = 'yes' ]
  then
    gzip_file ${OUTPUT}_hydro.sql
  fi
}

function gzip_region()
{
  if [ ${WORK_NUMERIC} = 'yes' ]
  then
    gzip_file ${OUTPUT}_region_success_numeric.load
  fi
  gzip_file ${OUTPUT}_region_success.load
  gzip_file ${OUTPUT}_region_fail.load
  if [ ${WORK_SQL} = 'yes' ]
  then
    if [ ${WORK_NUMERIC} = 'yes' ]
    then
      gzip_file ${OUTPUT}_region_success_numeric.sql
    fi
    gzip_file ${OUTPUT}_region_success.sql
    gzip_file ${OUTPUT}_region_fail.sql
  fi
}

function gzip_epitope()
{
  if [ ${WORK_NUMERIC} = 'yes' ]
  then
    gzip_file ${OUTPUT}_epitope_success_numeric.load
  fi
  gzip_file ${OUTPUT}_epitope_success.load
  gzip_file ${OUTPUT}_epitope_fail.load
  if [ ${WORK_SQL} = 'yes' ]
  then
    if [ ${WORK_NUMERIC} = 'yes' ]
    then
      gzip_file ${OUTPUT}_epitope_success_numeric.sql
    fi
    gzip_file ${OUTPUT}_epitope_success.sql
    gzip_file ${OUTPUT}_epitope_fail.sql
  fi
}

function work()
{
  mkdir -p $(dirname ${OUTPUT})
  if [ ${?} -ne 0 ]
  then
    error "Cannot make $(dirname ${OUTPUT})"
  fi
  ${BASE}/bin/fasta_tool -g ${INPUT_POSITION} ${INPUT} > ${TMP}/in 2> /dev/null
  eval $(${BASE}/bin/fasta_tool -i ${TMP}/in 2> /dev/null)
  : ${FASTA_DB:=x}
  : ${FASTA_ID:=0}
  : ${FASTA_REFERENCE_DB:=x}
  : ${FASTA_REFERENCE:=0}
  FILE_NAME=$(basename ${INPUT} .faa)

  cd ${TMP}
  case ${MODUL} in
    command)
      source ${BASE}/processing_command.ish
      ;;
    hydro)
      source ${BASE}/processing_hydro.ish
      gzip_hydro
      ;;
    anchor)
      source ${BASE}/processing_anchor.ish
      gzip_region
      ;;
    disembl)
      source ${BASE}/processing_disembl.ish
      gzip_region
      ;;
    disopred)
      source ${BASE}/processing_disopred.ish
      gzip_region
      ;;
    isunstruct)
      source ${BASE}/processing_isunstruct.ish
      gzip_region
      ;;
    iupred_long)
      source ${BASE}/processing_iupred_long.ish
      gzip_region
      ;;
    iupred_short)
      source ${BASE}/processing_iupred_short.ish
      gzip_region
      ;;
    ond)
      source ${BASE}/processing_ond.ish
      gzip_region
      ;;
    predisorder)
      source ${BASE}/processing_predisorder.ish
      gzip_region
      ;;
    ronn)
      source ${BASE}/processing_ronn.ish
      gzip_region
      ;;
    vsl2)
      source ${BASE}/processing_vsl2.ish
      gzip_region
      ;;
    netmhc_1_30c)
      source ${BASE}/processing_netmhc_1_30c.ish
      gzip_epitope
      ;;
    netmhc_1_34a)
      source ${BASE}/processing_netmhc_1_34a.ish
      gzip_epitope
      ;;
    netmhc_2_22)
      source ${BASE}/processing_netmhc_2_22.ish
      gzip_epitope
      ;;
    netmhcpan_1_20c)
      source ${BASE}/processing_netmhcpan_1_20c.ish
      gzip_epitope
      ;;
    netmhcpan_1_24a)
      source ${BASE}/processing_netmhcpan_1_24a.ish
      gzip_epitope
      ;;
    netmhcpan_1_28a)
      source ${BASE}/processing_netmhcpan_1_28a.ish
      gzip_epitope
      ;;
    netmhcpan_2_10b)
      source ${BASE}/processing_netmhcpan_2_10b.ish
      gzip_epitope
      ;;
    netmhcpan_2_20b)
      source ${BASE}/processing_netmhcpan_2_20b.ish
      gzip_epitope
      ;;
    netmhcpan_2_30c)
      source ${BASE}/processing_netmhcpan_2_30c.ish
      gzip_epitope
      ;;
    netmhcpan_2_31a)
      source ${BASE}/processing_netmhcpan_2_31a.ish
      gzip_epitope
      ;;
    *)
      error "Bad modul ${MODUL}"
      ;;
  esac
}

check_input ${@}
configuration
make_tmp
work
clean_tmp
if [ ${IS_EPITOPE} = "yes" ]
then
  echo "DONE ${MODUL} (${ALLELE} ${EPITOPE_LENGTH}) ${INPUT} ${INPUT_POSITION}" > /dev/stderr
else
  echo "DONE ${MODUL} ${INPUT} ${INPUT_POSITION}" > /dev/stderr
fi
