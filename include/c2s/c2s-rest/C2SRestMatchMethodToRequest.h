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

#ifndef C2SRESTMATCHMETHODTOREQUEST_H_
#define C2SRESTMATCHMETHODTOREQUEST_H_

#include "C2SRestPathIDList.h"
#include "C2SRestMethodPrototypeList.h"

#include <string>
#include <map>

namespace c2s
{

  class C2SHttpRequest;

  class C2SRestMatchMethodToRequest
  {
  public:

    C2SRestMatchMethodToRequest( const std::string &sContextRootOfResource , const C2SRestMethodPrototypeList &listOfAvailableMethodPrototypes , const C2SHttpRequest &requestToMatch );

    virtual ~C2SRestMatchMethodToRequest();

    C2SRestMethodPrototype *getPrototypeWithBestMatchAndPrepareFromURI();

  private:

    C2SRestMatchMethodToRequest( const C2SRestMatchMethodToRequest & );

    C2SRestMatchMethodToRequest &operator=( const C2SRestMatchMethodToRequest & );

    C2SRestPathIDList createPathIDListFromRequest();

    std::map<int,C2SRestMethodPrototype*> getMethodCandidatesSortedByDistanceToPathIDs( const C2SRestPathIDList &listOfRequestPathIDs );

    C2SRestMethodPrototype *getPrototypeClosestToRequestByConsideringMediaType( const std::map<int,C2SRestMethodPrototype*> &listOfMethodCandidatesSortedByDistanceToPathIDs ) const;

    const std::string &m_sContextRootOfResource;

    const C2SRestMethodPrototypeList &m_listOfAvailableMethodPrototypes;

    const C2SHttpRequest &m_requestToMatch;

    bool m_bIsAvailableAsDifferentMethodType;

  };

}

#endif /* C2SRESTMATCHMETHODTOREQUEST_H_ */
