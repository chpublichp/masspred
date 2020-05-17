#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhciipan-3.0c
tar xzvvf ${BASE}/source/data/netmhciipan-3.0c/netMHCIIpan-3.0c.Linux.tar.gz
mv netMHCIIpan-3.0 netmhciipan-3.0c
cat ${BASE}/source/patch/netmhciipan-3.0c.patch | patch -p0
cd netmhciipan-3.0c
tar xzvvf ${BASE}/source/data/netmhciipan-3.0c/data.tar.gz
