#!/bin/sh
. /etc/profile
module avail
module load gcc/12.1.0

perf stat -a -r 5 arq-release/fluid/fluid 1000 in/large.fld out.fld
