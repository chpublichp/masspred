#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/predisorder-1.1
cd ${BASE}/source/data/predisorder-1.1
wget -c http://sysbio.rnet.missouri.edu/multicom_toolbox/tools/predisorder1.1.tar.gz
wget -c http://sysbio.rnet.missouri.edu/multicom_toolbox/tools/sspro4.1.tar.gz
wget -c ftp://ftp.ncbi.nih.gov/blast/executables/release/2.2.17/blast-2.2.17-ia32-linux.tar.gz
