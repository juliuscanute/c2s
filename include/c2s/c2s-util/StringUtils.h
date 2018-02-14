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

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace c2s
{
  namespace util
  {

    template <class ElementT>
    inline std::string toString( ElementT val )
    {
      std::stringstream s;
      s << val;
      return s.str();
    }

    template <class ElementT>
    inline ElementT toNumber( const std::string &s )
    {
      std::stringstream str( s );
      ElementT val;
      str >> val;
      return val;
    }

    std::string urlEncode( const std::string &s );

    std::string urlDecode( const std::string &s );

    bool substract( const std::string &from , const std::string &what , std::string *dest );

    std::string substract( const std::string &from , const std::string &what );

    std::vector<std::string> splitString( const std::string& s , const char sSep , bool bDiscardEmptyStrings = false );

    std::string extractExtension( const std::string &s );

    std::string extractBaseName( const std::string &s );

    unsigned int removeChar( std::string *from , char what );

    inline bool isEqualCaseInsensitive( const std::string &sLeft , const std::string &sRight )
    {
      if ( sLeft.size() != sRight.size() )
        return false;
      for ( unsigned int i = 0; i < sLeft.size(); ++i )
      {
        if ( ::tolower( sLeft[ i ] ) != ::tolower( sRight[ i ] ) )
          return false;
      }
      return true;
    }

    inline void toLowerCaseInplace( std::string &s )
    {
      std::transform( s.begin() , s.end() , s.begin() , ::tolower );
    }

    inline std::string toLowerCase( const std::string &s )
    {
      std::string ls = s;
      toLowerCaseInplace( ls );
      return ls;
    }

  }
}

#endif /*STRINGUTILS_H_*/
