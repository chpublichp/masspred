#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

export PATH=${PATH}:${BASE}/app/bin
export LD_LIBRARY_PATH=${BASE}/predictors/app/lib
cd ${BASE}/ond-1.0
./OnD-CRF.sh example.fa example.out
