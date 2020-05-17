#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

mkdir -p ${BASE}/source/data/ond-1.0
cd ${BASE}/source/data/ond-1.0
wget -c http://babel.ucmp.umu.se/ond-crf/stand_alone/OnD.tar.gz
