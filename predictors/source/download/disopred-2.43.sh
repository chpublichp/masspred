#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/disopred-2.43
cd ${BASE}/source/data/disopred-2.43
wget -c http://bioinfadmin.cs.ucl.ac.uk/downloads/DISOPRED/disopred2.43.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/executables/release/2.2.26/blast-2.2.26-ia32-linux.tar.gz
wget -c ftp://ftp.ncbi.nlm.nih.gov/blast/executables/release/2.2.26/blast-2.2.26-x64-linux.tar.gz
