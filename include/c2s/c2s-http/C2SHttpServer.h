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

#ifndef C2SHTTPSERVER_H_
#define C2SHTTPSERVER_H_

#include <cstdlib>

namespace c2s
{
  class C2SRuntime;
  class C2SHttpDataHandlingImpl;
  class C2SHttpResourcePrototype;
  class C2SHttpResourcePrototypeList;
  class C2SHttpResourceManager;
  class C2SLogAbstractFactory;

  struct C2SSettings;

  class C2SHttpServer
  {
  public:

    C2SHttpServer( const C2SSettings &settings , C2SLogAbstractFactory *pLogFactory = NULL );

    virtual ~C2SHttpServer();

    void start();

    void run();

    void shutdown();

    void registerResourcePrototype( C2SHttpResourcePrototype *pResourcePrototype );

  private:

    C2SHttpResourcePrototypeList *m_pHttpResourcePrototypes;

    C2SHttpDataHandlingImpl *m_pHttpDataHandling;

    C2SRuntime *m_pServiceRuntime;

  };

}

#endif /* C2SHTTPSERVER_H_ */
