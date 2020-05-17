#!/bin/bash

BASE=$(dirname $(dirname $(dirname $(readlink -f ${0}))))

cd ${BASE}/vsl-2
java -jar VSL2.jar -s:testseq.flat
