#!/bin/sh

source CheckHostname.sh

if [ $# -eq 0 ]
then
    HOST=`hostname`
else
    HOST=$1
fi

CheckHostname $HOST

STATUS=$?

if [ "$STATUS" -eq 0 ]
then
    echo "$1 is available"
else
    echo "$1 is not available"
fi
