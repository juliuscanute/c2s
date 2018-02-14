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


#ifndef C2STHREADWINDOWS_H_
#define C2STHREADWINDOWS_H_

#include <windows.h>

namespace c2s
{
  namespace thread
  {

    class C2SThreadWindows
    {
    public:

      C2SThreadWindows();

      virtual ~C2SThreadWindows();

      inline void start();

      inline void runInThread();

    protected:

      virtual void doWork() = 0;

    private:

      HANDLE m_pThreadHandle;

      DWORD m_dwThreadId;

    };

    static DWORD WINAPI c2sThreadCallback( LPVOID lpParam )
    {
      C2SThreadWindows *pThreadObject = ( C2SThreadWindows* ) lpParam;
      pThreadObject->runInThread();
      return 0;
    }

    inline C2SThreadWindows::C2SThreadWindows()
      : m_pThreadHandle( NULL ),
        m_dwThreadId( 0 )
    {};

    inline C2SThreadWindows::~C2SThreadWindows()
    {
      CloseHandle( m_pThreadHandle );
    };

    inline void C2SThreadWindows::start()
    {
      m_pThreadHandle = CreateThread(
          NULL,                   // default security attributes
          0,                      // use default stack size
          c2sThreadCallback,       // thread function name
          this,          // argument to thread function
          0,                      // use default creation flags
          &m_dwThreadId
        );
    }

    inline void C2SThreadWindows::runInThread()
    {
      this->doWork();
    }

  }
}

#endif /* C2STHREADWINDOWS_H_ */
