#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/disopred-2.43
./rundisopred small_example.fasta
