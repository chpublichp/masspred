#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

rm -rf ${BASE}/netmhciipan-1.0b
rm -rf ${BASE}/netmhciipan-3.0c
rm -rf ${BASE}/netmhcpan-2.0c
rm -rf ${BASE}/netmhcpan-2.4a
