#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhcpan-2.4a
tar xzvvf ${BASE}/source/data/netmhcpan-2.4a/netMHCpan-2.4a.Linux.tar.Z
mv netMHCpan-2.4 netmhcpan-2.4a
cat ${BASE}/source/patch/netmhcpan-2.4a.patch  | patch -p0
cd netmhcpan-2.4a
tar xzvvf ${BASE}/source/data/netmhcpan-2.4a/data.tar.gz
