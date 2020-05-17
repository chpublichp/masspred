#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/netmhcpan-2.4a
./netMHCpan test/test.fsa
