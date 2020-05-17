#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhc-3.4a
cd ${BASE}/source/data/netmhc-3.4a
wget -c http://www.cbs.dtu.dk/services/NetMHC-3.4/net.tar.gz
