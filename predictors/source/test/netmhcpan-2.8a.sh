#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhcpan-2.8a
./netMHCpan test/test.fsa
