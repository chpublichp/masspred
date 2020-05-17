#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhciipan-3.1a
tar xzvvf ${BASE}/source/data/netmhciipan-3.1a/netMHCIIpan-3.1a.Linux.tar.gz
mv netMHCIIpan-3.1 netmhciipan-3.1a
cat ${BASE}/source/patch/netmhciipan-3.1a.patch | patch -p0
cd netmhciipan-3.1a
tar xzvvf ${BASE}/source/data/netmhciipan-3.1a/data.tar.gz
