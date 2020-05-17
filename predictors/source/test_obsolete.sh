#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

${BASE}/source/test/netmhciipan-1.0b.sh
${BASE}/source/test/netmhciipan-3.0c.sh
${BASE}/source/test/netmhcpan-2.0c.sh
${BASE}/source/test/netmhcpan-2.4a.sh
