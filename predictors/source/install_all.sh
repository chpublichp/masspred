#!/bin/bash

BASE=$(dirname $(dirname $(readlink -f ${0})))

${BASE}/source/install/nr.sh
${BASE}/source/install/anchor-1.0.sh
${BASE}/source/install/disembl-1.4.sh
${BASE}/source/install/disopred-2.43.sh
${BASE}/source/install/isunstruct-2.02.sh
${BASE}/source/install/iupred-1.0.sh
${BASE}/source/install/netmhc-3.0c.sh
${BASE}/source/install/netmhc-3.4a.sh
${BASE}/source/install/netmhcii-2.2.sh
${BASE}/source/install/netmhciipan-1.0b.sh
${BASE}/source/install/netmhciipan-2.0b.sh
${BASE}/source/install/netmhciipan-3.0c.sh
${BASE}/source/install/netmhciipan-3.1a.sh
${BASE}/source/install/netmhcpan-2.0c.sh
${BASE}/source/install/netmhcpan-2.4a.sh
${BASE}/source/install/netmhcpan-2.8a.sh
${BASE}/source/install/ond-1.0.sh
${BASE}/source/install/predisorder-1.1.sh
${BASE}/source/install/ronn-3.1.sh
${BASE}/source/install/vsl-2.sh
