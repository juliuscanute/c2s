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

#ifndef _G_IO_LOGGER_H_
#define _G_IO_LOGGER_H_

#include <string>
#include <iostream>

namespace c2s
{
  namespace io
  {

    class Logger
    {
    public:

      typedef enum { Error = 0 , Warning = 1 , Note = 2 , Info = 3 , Debug = 4 , Verbose = 5 } Level;

      Logger( const std::string &id );

      virtual ~Logger();

      virtual void error( const std::string &message , bool bLineBreak = true ) const;

      virtual void warning( const std::string &message , bool bLineBreak = true ) const;

      virtual void note( const std::string &message , bool bLineBreak = true ) const;

      virtual void info( const std::string &message , bool bLineBreak = true ) const;

      virtual void debug( const std::string &message , bool bLineBreak = true ) const;

      virtual void verbose( const std::string &message , bool bLineBreak = true ) const;

      static void setOutputStream( std::ostream &os );

      static void setLevel( Level level );

      static void setLevel( int iLevel );

      static Level getLevel();

    protected:

      virtual void print( const std::string &level , const std::string &message , bool bLineBreak ) const;

      virtual int printPrefix( std::ostream &os , const std::string &level ) const;

      static int level2int( Level level );

      static Level int2level( int iLevel );

      static int m_iLoggingLevel;

      static bool m_bWasLastLineNoLineBreak;

      std::string m_id;

      static std::ostream *m_pGlobalStream;

    };

  }
}

#endif /* _G_IO_LOGGER_H_ */
