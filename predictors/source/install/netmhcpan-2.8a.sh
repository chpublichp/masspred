#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhcpan-2.8a
tar xzvvf ${BASE}/source/data/netmhcpan-2.8a/netMHCpan-2.8a.Linux.tar.gz
mv netMHCpan-2.8 netmhcpan-2.8a
cat ${BASE}/source/patch/netmhcpan-2.8a.patch  | patch -p0
cd netmhcpan-2.8a
tar xzvvf ${BASE}/source/data/netmhcpan-2.8a/data.tar.gz
