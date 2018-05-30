SystemType() {
    _HOSTNAME=`hostname | sed 's/\..*//'`

    case `uname -s` in
        FreeBSD     ) echo FreeBSD ;;
        Linux       ) echo Linux   ;;
        Darwin      ) echo Mac     ;;
        SunOS       ) case `uname -r` in
                          IP*  ) echo SGI ;;
                          i386 ) echo SCO ;;
                      esac
                      ;;
        $_HOSTNAME ) case `uname -m` in
                        IP*  ) echo SGI ;;
                        i386 ) echo SCD ;;
                     esac
                     ;;
    esac
}
