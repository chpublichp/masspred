#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhc-3.4a
tar xzvvf ${BASE}/source/data/netmhc-3.4a/netMHC-3.4a.Linux.tar.gz
mv netMHC-3.4 netmhc-3.4a
cat ${BASE}/source/patch/netmhc-3.4a.patch | patch -p0
cd netmhc-3.4a/etc
tar xzvvf ${BASE}/source/data/netmhc-3.4a/net.tar.gz
