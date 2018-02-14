/**

 Copyright (c) 2012, C2Serve (http://www.c2serve.eu)
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

#ifndef C2SLOGBASE_H_
#define C2SLOGBASE_H_

#include "C2SLogInterface.h"
#include "C2SLogLevel.h"

namespace c2s
{
  class C2SLogMutex;
  class C2SLogPublicationInterface;

  class C2SLogBase : public C2SLogInterface
  {
  public:

    virtual ~C2SLogBase();

    virtual void error( const std::string &sLogMessage ) const;

    virtual void warning( const std::string &sLogMessage ) const;

    virtual void note( const std::string &sLogMessage ) const;

    virtual void info( const std::string &sLogMessage ) const;

    virtual void debug( const std::string &sLogMessage ) const;

    virtual void verbose( const std::string &sLogMessage ) const;

    static ELogLevel LogLevel;

  protected:

    C2SLogBase( const C2SLogPublicationInterface &logPublication );

    void publishMessageSynchronized( const std::string &sLogMessage ) const;

    const C2SLogPublicationInterface &m_logPublication;

    C2SLogMutex *m_pLogMutex;

  private:

    C2SLogBase( const C2SLogBase & );

    C2SLogBase &operator=( const C2SLogBase & );

  };

}

#endif /* C2SLOGBASE_H_ */
