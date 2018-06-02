#!/bin/sh

PATH=$PATH:`dirname $0`

source "../functions/SystemType.sh"
source "../functions/GetYesNo.sh"

CMDNAME=`basename $0`
USAGE="Usage: $CMDNAME [-signal] ProcessName"
OLD_IFS=$IFS
SIGNAL=
NAME=
PID=
PROCNAME=
OWNER=
PS_OPTS=
PROCESS_LIST=/tmp/list.$$
TITLE_PRINTED=FALSE
FOUND=FALSE
LINE=
COL=
SYSTEM=`SystemType`

trap `rm -f /tmp/*.$$; exit 1` 1 2 3 15

case $1 in
    -- ) shift
         ;;
    -* ) SIGNAL=$1
         shift
         ;;
esac

if [ $# -ne 1 ]
then
    echo "$USAGE" 1>&2
    exit 1
fi

NAME=$1

case $SYSTEM in
    LINUX   ) PS_OPTS="auxw"  ;;
    FREEBSD ) PS_OPTS="-auxw" ;;
    DARWIN  ) PS_OPTS="auxw"  ;;
    *       ) PS_OPTS="-ef"   ;;
esac

ps $PS_OPTS | sed '1d' | grep "$NAME" | grep -v "$0" | grep -v "ps $PS_OPTS" > $PROCESS_LIST

exec < $PROCESS_LIST

IFS=

while read LINE
do
    IFS=$OLD_IFS

    set $LINE
    OWNER=$1
    PID=$2

    case $SYSTEM in
        LINUX   ) COL=64 ;;
        FREEBSD ) COL=63 ;;
        DARWIN  ) COL=64 ;;
        *       ) echo "Unexpected system type." 1>&2
                  exit 1
                  ;;
    esac

    LINE=`echo "$LINE" | cut -c$COL-`
    set dummy $LINE
    shift
    PROCNAME=$1

    if [ "$PROCNAME" = "$NAME" -o "`basename $PROCNAME`" = "$NAME" ]
    then
        FOUND=TRUE

        if [ "$TITLE_PRINTED" = "FALSE" ]
        then
            echo "PID Owner Process"
            TITLE_PRINTED=TRUE
        fi

        if GetYesNo "$PID $OWNER $PROCNAME (y/n)? " < /dev/tty
        then
            kill $SIGNAL $PID
        fi
    fi

    IFS=

done

if [ "$FOUND" = "FALSE" ]
then
    echo "Process \"$NAME\" not found"
fi

rm -f /tmp/*.$$
exit 0


