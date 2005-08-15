#! /bin/sh
#

cachefile=Zebra.cache
niops=8
if [ $# -ne 2 -a $# -ne 0 ]; then
    echo "Usage: $0 [cache-file-name num-iops]"
    exit 1
fi
if [ $# -eq 2 ]; then
    cachefile="$1"
    niops="$2"
fi

iopdir="/scr/data/iops"
cd $iopdir
iops=`find . -name 'iop_*' -type d -prune | sed -e 's/^\.\///' | sort -r`
first=1
if /bin/false ; then
    # Add only the last N IOPs, besides the first one defined in ds.config
    iops=`echo $iops | cut -f2 -d " "`
    first=0
else
    # Add only the first N IOPs, including the main default one.
    iops=`echo $iops | cut -f1-$niops -d " "`
fi
cat <<EOF
! This file is automatically generated by scaniops.
! Do not edit, re-run scaniops or restart zebra instead.
!
! Generated by `id -u -n` on `date -u`
!
! All but the first source set dirconst to avoid the initial scan and rely
! on the cache files instead, since only the first source will be changing.
!
EOF
for iop in $iops END ; do

test "$iop" = END && break
cat <<EOF

source $iop
	directory $iopdir/$iop
	fileconst true
	cachefile $cachefile
EOF
if [ $first -ne 0 ]; then
cat <<EOF
	PlatDir elev #elevdir
EOF
first=0
else
	echo "	dirconst true"
fi
echo "endsource"

done