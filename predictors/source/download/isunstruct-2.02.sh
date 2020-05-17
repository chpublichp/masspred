#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/isunstruct-2.02
cd ${BASE}/source/data/isunstruct-2.02
wget -c http://bioinfo.protres.ru/IsUnstruct/IsUnstruct_2.02.tar.gz
