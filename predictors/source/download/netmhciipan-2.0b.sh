#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhciipan-2.0b
cd ${BASE}/source/data/netmhciipan-2.0b
wget -c http://www.cbs.dtu.dk/services/NetMHCIIpan-2.0/data.tar.gz
