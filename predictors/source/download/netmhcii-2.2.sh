#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/netmhcii-2.2
cd ${BASE}/source/data/netmhcii-2.2
wget -c http://www.cbs.dtu.dk/services/NetMHCII/data.tar.gz
