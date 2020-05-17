#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

${BASE}/source/download/netmhciipan-3.0c.sh
${BASE}/source/download/netmhcpan-2.4a.sh
