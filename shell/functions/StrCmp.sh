StrCmp() {
    if [ $# -ne 2 ]
    then
        echo "Usage: StrCmp string1 string2" 1>&2
        exit 1
    fi

    if [ "$1" = "$2" ]
    then
        echo "0"
    else
        # _TMP=`{ echo "$1"; echo "$2"; } | sort | sed -n '1p'`
        _TMP=`echo "$1\n$2" | sort | sed -n '1p'`

        if [ "$_TMP" = "$1" ]
        then
            echo "-1"
        else
            echo "1"
        fi
    fi
}
