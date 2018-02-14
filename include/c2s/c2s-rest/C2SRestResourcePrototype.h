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

#ifndef C2SRESTRESOURCEPROTOTYPE_H_
#define C2SRESTRESOURCEPROTOTYPE_H_

#include "C2SHttpResourcePrototype.h"

#include "C2SRestMethodPrototype.h"
#include "C2SRestMethodPrototypeList.h"
#include "C2SRestResourceDescription.h"

#include <list>

namespace c2s
{

  class C2SRestResourcePrototype: public C2SHttpResourcePrototype
  {
  public:

    virtual ~C2SRestResourcePrototype();

    static C2SRestResourcePrototype *createRestResourceWithContextRoot( const std::string &sContextRootOfRestResource );

    void processRequest( const C2SHttpRequest &request );

    C2SHttpResourcePrototype *clone() const;

    void registerMethodPrototype( C2SRestMethodPrototype *pMethod );

  private:

    C2SRestResourcePrototype( const std::string &sHostName , const std::string &sContextRoot );

    C2SRestResourcePrototype( const C2SRestResourcePrototype &r );

    //TODO: implement
    bool existsMethodPrototype( const C2SRestMethodPrototype *pMethod ) const;

    bool isAccessToContextRoot( const std::string &sResourceContext ) const;

    void createAndSendResponseFromResourceDescription( const C2SHttpRequest &request );

    void createAndSendResponseFromMethodWithBestMatchForRequest( const C2SHttpRequest &request );

    C2SRestMethodPrototype *getMethodWithBestMatchForRequest( const C2SHttpRequest &request );

    C2SRestMethodPrototypeList m_registeredMethodPrototypes;

    C2SRestResourceDescription m_resourceDescription;

  };

}

#endif /* C2SRESTRESOURCEPROTOTYPE_H_ */
