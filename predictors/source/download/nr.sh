#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/nr
cd ${BASE}/source/data/nr
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.00.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.01.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.02.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.03.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.04.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.05.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.06.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.07.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.08.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.09.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/db/nr.10.tar.gz
