/**

	Copyright (c) 2011, C2Serve (http://www.c2serve.eu)
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement: "This product includes software of the C2Serve project".
	4. Neither the name of the C2Serve project nor the
	   names of its contributors may be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY C2SERVE ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL C2SERVE BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef C2SSTRINGUTILS_H_
#define C2SSTRINGUTILS_H_

#include <cstring>

namespace c2s
{

  inline bool equals( const char *data , unsigned int size , const char *ref )
  {
    unsigned int iRefSize = std::strlen( ref );

    if ( size != iRefSize )
      return false;

    for ( unsigned int i = 0; i < iRefSize; ++i, ++data, ++ref )
    {
      if ( *data != *ref )
        return false;
    }

    return true;
  }

  inline bool equals( const char *s1 , unsigned int size1 , const char *s2 , unsigned int size2 )
  {
    if ( size1 != size2 )
      return false;

    for ( unsigned int i = 0; i < size2; ++i, ++s1, ++s2 )
    {
      if ( *s1 != *s2 )
        return false;
    }

    return true;
  }

  inline bool uriEquals( const char *s1 , unsigned int size1 , const char *s2 , unsigned int size2 , bool bCheckLeadingSlash = true )
  {
    if ( bCheckLeadingSlash )
    {
      //check if we have slashes at the beginning of both strings
      if ( size1 && s1[ 0 ] == '/' )
      {
        if ( !size2 )
          return false;

        if ( s2[ 0 ] != '/' )
          return false;
      }
      else
      {
        if ( size2 && s2[ 0 ] == '/' )
          return false;
      }
    }

    while ( size1 || size2 )
    {
      //skip slashes
      while( *s1 == '/' && size1 )
      {
        ++s1;
        --size1;
      }

      //get path segment
      unsigned int l1 = 0;
      while( l1 < size1 && s1[ l1 ] != '/' )
        ++l1;

      //skip slashes
      while ( *s2 == '/' && size2 )
      {
        ++s2;
        --size2;
      }

      //get path segment
      unsigned int l2 = 0;
      while( l2 < size2 && s2[ l2 ] != '/' )
        ++l2;

      if ( !equals( s1 , l1 , s2 , l2 ) )
        return false;

      s1 += l1;
      size1 -= l1;

      s2 += l2;
      size2 -= l2;
    }

    return true;
  }

  inline int uriSkip( const char *data , unsigned int datasize , const char *toskip , unsigned int toskipsize , bool bCheckLeadingSlash = true )
  {
    if ( bCheckLeadingSlash )
    {
      //check if we have slashes at the beginning of both strings
      if ( datasize && data[ 0 ] == '/' )
      {
        if ( !toskipsize )
          return -1;

        if ( toskip[ 0 ] != '/' )
          return -1;
      }
      else
      {
        if ( toskipsize && toskip[ 0 ] == '/' )
          return -1;
      }
    }
    else
    {
      //skip slashes
      while ( *toskip == '/' && toskipsize )
      {
        ++toskip;
        --toskipsize;
      }
    }

    int iChars2Skip = 0;

    while ( datasize && toskipsize )
    {
      //skip slashes
      while( *data == '/' && datasize )
      {
        ++data;
        --datasize;
        ++iChars2Skip;
      }

      //get path segment
      unsigned int l1 = 0;
      while( l1 < datasize && data[ l1 ] != '/' )
      {
        ++l1;
        ++iChars2Skip;
      }

      //skip slashes
      while ( *toskip == '/' && toskipsize )
      {
        ++toskip;
        --toskipsize;
      }

      //get path slice
      unsigned int l2 = 0;
      while( l2 < toskipsize && toskip[ l2 ] != '/' )
        ++l2;

      if ( !equals( data , l1 , toskip , l2 ) )
        return -1;

      data += l1;
      datasize -= l1;

      toskip += l2;
      toskipsize -= l2;

      //remove adjacent slashes
      while( toskipsize && *toskip == '/' )
      {
        --toskipsize;
        ++toskip;
      }

    }

    if ( toskipsize )
      return -1;

    //skip adjacent slashes
    while( *data == '/' && datasize )
    {
      ++data;
      --datasize;
      ++iChars2Skip;
    }

    return iChars2Skip;
  }

  inline bool startsWith( const char *data , unsigned int datasize, const char *ref , unsigned int refsize )
  {
    if ( datasize < refsize )
      return false;

    for ( unsigned int i = 0; i < refsize; ++i, ++data, ++ref )
    {
      if ( *data != *ref )
        return false;
    }

    return true;
  }

  template <class Handler>
  inline void splitNhandle( const char *data , unsigned int size , char separator , Handler *pHandler )
  {
    const char *currentLine = data;
    unsigned int iCurrentSize = 1;
    for ( unsigned int i = 0; i < size; ++i, ++data, ++iCurrentSize )
    {
      if ( *data == separator )
      {
        //ignore empty bodies
        if ( iCurrentSize == 1 )
          continue;

        //ignore empty lines in header
        if ( iCurrentSize > 1 )
          pHandler->operator()( currentLine , iCurrentSize - 1 );

        currentLine = data + 1;
        iCurrentSize = 0;
      }
    }

    pHandler->operator()( currentLine , iCurrentSize - 1 );

  }

}

#endif /* C2SSTRINGUTILS_H_ */
