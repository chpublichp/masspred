#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/ronn-3.1
./RONN ./test_seq.txt 1
