#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}
rm -rf netmhcpan-2.0c
tar xvvzf ${BASE}/source/data/netmhcpan-2.0c/netMHCpan-2.0c.Linux.tar.Z
mv netMHCpan-2.0 netmhcpan-2.0c
cat ${BASE}/source/patch/netmhcpan-2.0c.patch | patch -p0
cd netmhcpan-2.0c
ln -s Linux_i686 Linux_x86_64
