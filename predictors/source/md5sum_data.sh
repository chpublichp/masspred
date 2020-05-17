#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

cd ${BASE}/source
find data -type f | sort | xargs -n1 md5sum
