#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhciipan-3.0c
./netMHCIIpan -f test/example.fsa
