/* config.h. Generated by cmake from config.h.cmake */

#ifndef TAGLIB_CONFIG_H
#define TAGLIB_CONFIG_H

/* Defined if required for large files support */
#cmakedefine   _LARGE_FILES      ${_LARGE_FILES}
#cmakedefine   _LARGEFILE_SOURCE ${_LARGEFILE_SOURCE}
#cmakedefine   _FILE_OFFSET_BITS ${_FILE_OFFSET_BITS}

/* Defined if your compiler supports some byte swap functions */
#cmakedefine   HAVE_GCC_BYTESWAP 1
#cmakedefine   HAVE_GLIBC_BYTESWAP 1
#cmakedefine   HAVE_MSC_BYTESWAP 1
#cmakedefine   HAVE_MAC_BYTESWAP 1
#cmakedefine   HAVE_OPENBSD_BYTESWAP 1

/* Defined if your compiler supports some safer version of vsprintf */
#cmakedefine   HAVE_VSNPRINTF 1
#cmakedefine   HAVE_VSPRINTF_S 1

/* Defined if your compiler supports ISO _strdup */
#cmakedefine   HAVE_ISO_STRDUP 1

/* Defined if zlib is installed */
#cmakedefine   HAVE_ZLIB 1

/* Indicates whether debug messages are shown even in release mode */
#cmakedefine   TRACE_IN_RELEASE 1

#cmakedefine TESTS_DIR "@TESTS_DIR@"

#endif
