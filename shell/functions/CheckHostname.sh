CheckHostname() {
    _PING=
    _HOST=${1:-`hostname`}

    case `uname -s` in
        FreeBSD ) _PING="ping -c1 $_HOST" ;;
        Linux   ) _PING="ping -c1 $_HOST" ;;
        Darwin  ) _PING="ping -c1 $_HOST" ;;
        SunOS   ) _PING="ping $_HOST"     ;;
        *       ) return 1 ;;
    esac

    return $_PING >/dev/null 2>&1
    # if [ `$_PING 2>&1 | grep -ci "Unknown host"` -eq 0 ]
    # then
    #     return 0
    # else
    #     return 1
    # fi
}
