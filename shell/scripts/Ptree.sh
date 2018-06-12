#!/bin/sh

LANG=C
export LANG
PATH=$PATH:`dirname $0`

. ../functions/SystemType.sh

CMDNAME=`basename $0`
USAGE="Usage: $CMDNAME [-n] [pid]"
RECURSIVE=TRUE
PROCESS=
LEVEL=
DATAFILE=
PSFILE=/tmp/ps.$$
PS_OPTS=
OLD_IFS=$IFS
SYSTEM=`SystemType`

PID=
PRTPID=
OWNER=
NAME=
LINE=
OUTLINE=
INDENT=

trap `rm -f /tmp/*.$$; exit 1` 1 2 3 15

FillLine() {
    _LINE="$1"
    _COLUMN=$2
    _LEN=`expr "$_LINE" : '.*'`

    while [ $_LEN -lt $_COLUMN ]
    do
        _LINE="$_LINE "
        _COLUMN=`expr $_COLUMN - 1`
    done

    echo "$_LINE"
}

while getopts n OPT
do
    case $OPT in
        n ) RECURSIVE=FALSE
            ;;
        * ) echo "$USAGE" 1>&2
            exit 1
            ;;
    esac
done

shift `expr $OPTIND - 1`

if [ $# -eq 0 ]
then
    PROCESS=1
    LEVEL=0
    DATAFILE=/tmp/ptree.$$
elif [ $# -eq 1 ]
then
    PROCESS=$1
    LEVEL=0
    DATAFILE=/tmp/ptree.$$
elif [ $# -eq 2 ]
then
    PROCESS=$1
    LEVEL=$2
    DATAFILE=/tmp/ptree.$$
elif [ $# -eq 3 ]
then
    PROCESS=$1
    LEVEL=$2
    DATAFILE=$3
else
    echo "$USAGE" 1>&2
    exit 1
fi

if [ "$LEVEL" = 0 ]
then
    case $SYSTEM in
        LINUX         ) PS_OPTS="alxw"  ;;
        FREEBSD | Mac ) PS_OPTS="-alxw" ;;
        *             ) PS_OPTS="-ef"   ;;
    esac

    rm -f $DATAFILE $PSFILE

    ps $PS_OPTS | sed '1d' | sort > $PSFILE

    exec < $PSFILE

    IFS=

    while read LINE
    do
        IFS=$OLD_IFS

        set $LINE

        if [ $SYSTEM = LINUX ]
        then
            shift
        fi

        OWNER=$1
        PID=$2
        PRTPID=$3

        case $SYSTEM in
            LINUX         ) COL=70 ;;
            FREEBSD | Mac ) COL=68 ;;
            *             ) echo "Unexpected system type." 1>&2
                            exit 1
                            ;;
        esac

        LINE=`echo "$LINE" | cut -c$COL-`
        set dummy $LINE
        shift
        NAME=$1

        echo $PID $PRTPID $OWNER $NAME >> $DATAFILE

        IFS=
    done

    IFS=$OLD_IFS

fi

INDENT=`expr $LEVEL \* 2`
OUTLINE=`FillLine "" $INDENT`

LINE=`grep "^$PROCESS " $DATAFILE`

if [ "$LINE" = "" ]
then
    echo "No such process: $PROCESS" 1>&2
    exit 1
fi

set $LINE

OUTLINE="$OUTLINE $1"
OUTLINE=`FillLine "$OUTLINE" 30`
OUTLINE="$OUTLINE $3 $4"
echo "$OUTLINE"

if [ "$RECURSIVE" = "TRUE" ]
then
    LEVEL=`expr $LEVEL + 1`

    while read LINE
    do
        set dummy $LINE
        shift

        if [ "$2" = "$PROCESS" ]
        then
            $0 $1 $LEVEL $DATAFILE
        fi
    done < $DATAFILE
fi

rm -f /tmp/*.$$

exit 0
