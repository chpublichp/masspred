#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhciipan-3.0c
cd ${BASE}/source/data/netmhciipan-3.0c
wget -c http://www.cbs.dtu.dk/services/NetMHCIIpan-3.0/data.tar.gz
