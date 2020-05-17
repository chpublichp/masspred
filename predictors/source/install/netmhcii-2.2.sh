#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhcii-2.2
tar xzvvf ${BASE}/source/data/netmhcii-2.2/netMHCII-2.2.Linux.tar.Z
mv netMHCII-2.2 netmhcii-2.2
cat ${BASE}/source/patch/netmhcii-2.2.patch | patch -p0
cd netmhcii-2.2
tar xzvvf ${BASE}/source/data/netmhcii-2.2/data.tar.gz
