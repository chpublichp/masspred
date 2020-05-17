#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhcpan-2.4a
cd ${BASE}/source/data/netmhcpan-2.4a
wget http://www.cbs.dtu.dk/services/NetMHCpan-2.4/data.tar.gz
