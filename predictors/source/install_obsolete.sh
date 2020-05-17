#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

${BASE}/source/install/netmhciipan-1.0b.sh
${BASE}/source/install/netmhciipan-3.0c.sh
${BASE}/source/install/netmhcpan-2.0c.sh
${BASE}/source/install/netmhcpan-2.4a.sh
