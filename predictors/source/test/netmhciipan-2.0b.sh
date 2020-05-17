#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhciipan-2.0b
./netMHCIIpan test/test.fsa
