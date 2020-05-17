#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhcpan-2.8a
cd ${BASE}/source/data/netmhcpan-2.8a
wget http://www.cbs.dtu.dk/services/NetMHCpan-2.8/data.tar.gz
