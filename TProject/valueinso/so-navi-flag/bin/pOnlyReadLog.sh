#!/bin/bash

show_usage()
{
	echo "usage: pOnlyReadLog.sh p2-run-log.txt"
	exit 1
}

if [ $# -ge 1 ]; then
	sed -i '/[0]/d' $1
	sed -i '/-------------------------------------------------/d' $1
	sed -i '/^\s*$/d' $1
else
	show_usage
fi



