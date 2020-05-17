#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhcpan-2.0c
./netMHCpan test/test.fsa
