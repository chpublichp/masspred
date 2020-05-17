#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

export IUPred_PATH=${BASE}/iupred-1.0
cd ${BASE}/iupred-1.0
./iupred P53_HUMAN.seq long
