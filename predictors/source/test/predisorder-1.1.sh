#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/predisorder-1.1
./bin/predict_diso.sh test/seq.fasta test/seq.out
