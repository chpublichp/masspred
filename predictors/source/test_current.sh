#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

${BASE}/source/test/anchor-1.0.sh
${BASE}/source/test/disembl-1.4.sh
${BASE}/source/test/disopred-2.43.sh
${BASE}/source/test/isunstruct-2.02.sh
${BASE}/source/test/iupred-1.0.sh
${BASE}/source/test/netmhc-3.0c.sh
${BASE}/source/test/netmhc-3.4a.sh
${BASE}/source/test/netmhcii-2.2.sh
${BASE}/source/test/netmhciipan-2.0b.sh
${BASE}/source/test/netmhciipan-3.1a.sh
${BASE}/source/test/netmhcpan-2.8a.sh
${BASE}/source/test/ond-1.0.sh
${BASE}/source/test/predisorder-1.1.sh
${BASE}/source/test/ronn-3.1.sh
${BASE}/source/test/vsl2.sh
