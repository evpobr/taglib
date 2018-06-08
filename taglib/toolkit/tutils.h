/***************************************************************************
    copyright            : (C) 2013 by Tsuda Kageyu
    email                : tsuda.kageyu@gmail.com
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_TUTILS_H
#define TAGLIB_TUTILS_H

// THIS FILE IS NOT A PART OF THE TAGLIB API

#ifndef DO_NOT_DOCUMENT  // tell Doxygen not to document this header

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if defined(HAVE_MSC_BYTESWAP)
# include <stdlib.h>
#elif defined(HAVE_GLIBC_BYTESWAP)
# include <byteswap.h>
#elif defined(HAVE_MAC_BYTESWAP)
# include <libkern/OSByteOrder.h>
#elif defined(HAVE_OPENBSD_BYTESWAP)
# include <sys/endian.h>
#endif

#include <tstring.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <climits>

namespace TagLib
{
  namespace Utils
  {
    namespace
    {

      /*!
       * Reverses the order of bytes.
       */
      template <typename T>
      T byteSwap(T u)
      {
        static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

        union
        {
          T u;
          unsigned char u8[sizeof(T)];
      } source, dest;

        source.u = u;

        for (size_t k = 0; k < sizeof(T); k++)
          dest.u8[k] = source.u8[sizeof(T) - k - 1];

        return dest.u;
      }

      /*!
       * Returns a formatted string just like standard sprintf(), but makes use of
       * safer functions such as snprintf() if available.
       */
      inline String formatString(const char *format, ...)
      {
        // Sufficient buffer size for the current internal uses.
        // Consider changing this value when you use this function.

        static const size_t BufferSize = 128;

        va_list args;
        va_start(args, format);

        char buf[BufferSize];
        int length;

#if defined(HAVE_VSNPRINTF)

        length = vsnprintf(buf, BufferSize, format, args);

#elif defined(HAVE_VSPRINTF_S)

        length = vsprintf_s(buf, format, args);

#else

        // The last resort. May cause a buffer overflow.

        length = vsprintf(buf, format, args);
        if(length >= BufferSize) {
          debug("Utils::formatString() - Buffer overflow! Returning an empty string.");
          length = -1;
        }

#endif

        va_end(args);

        if(length > 0)
          return String(buf);
        else
          return String();
      }

      /*!
       * Returns the byte order of the system.
       */
      inline ByteOrder systemByteOrder()
      {
        union {
          int  i;
          char c;
        } u;

        u.i = 1;
        if(u.c == 1)
          return LittleEndian;
        else
          return BigEndian;
      }
    }
  }
}

#endif

#endif
