#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhciipan-3.1a
cd ${BASE}/source/data/netmhciipan-3.1a
wget -c http://www.cbs.dtu.dk/services/NetMHCIIpan-3.1/data.tar.gz
