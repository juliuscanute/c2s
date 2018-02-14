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

#ifndef C2SRESTMETHODPROTOTYPE_H_
#define C2SRESTMETHODPROTOTYPE_H_

#include "C2SHttpMethod.h"

#include "C2SHttpRequest.h"
#include "C2SHttpResponse.h"

#include "C2SRestPathParameter.h"
#include "C2SRestQueryParameter.h"
#include "C2SRestPathSegmentList.h"

#include <map>
#include <list>
#include <string>

namespace c2s
{

  class C2SRestMethodPrototype
  {
  public:

    virtual ~C2SRestMethodPrototype();

    virtual C2SHttpResponse *processRequest( const C2SHttpRequest &request );

    virtual C2SRestMethodPrototype *clone() const = 0;

    int getDistanceToPathIDs( const C2SRestPathIDList &pathList ) const;

    void processPathIDs( const C2SRestPathIDList &pathList );

    bool isMethodType( C2SHttpMethod methodType ) const;

    bool operator==( const C2SRestMethodPrototype &methodPrototypeToCheck ) const;

  protected:

    C2SRestMethodPrototype( C2SHttpMethod methodType , const std::string &sPath );

    virtual C2SHttpResponse *process() = 0;

    void addPathSegment( const std::string &sPathSegment );

    template <class Type>
    void addPathParameter( const std::string &sParameterID , Type *pParameterObjectToWrite );

    template <class Type>
    void addQueryParameter( const std::string &sParameterID , Type *pParameterObjectToWrite , const Type &parameterDefaultValue );

    void addQueryParameter( const std::string &sParameterID , std::string *pParameterObjectToWrite , const char *pParameterDefaultValue );

    template <class Type>
    void addQueryParameter( const std::string &sParameterID , Type *pParameterObjectToWrite );

    C2SHttpResponse *buildResponse( C2SHttpStatus status ) const;

  private:

    typedef std::map<std::string,C2SRestQueryParameterBase*> QueryParameterList;

    C2SHttpMethod m_methodType;

    C2SRestPathSegmentList m_pathSegments;

    QueryParameterList m_queryParameters;

  };

  template <class Type>
  void C2SRestMethodPrototype::addPathParameter( const std::string &sID , Type *pDest )
  {
    m_pathSegments.appendPathSegment( new C2SRestPathParameter( sID , new C2SRestParameter<Type>( pDest ) ) );
  }

  template <class Type>
  void C2SRestMethodPrototype::addQueryParameter( const std::string &sID , Type *pDest , const Type &defaultv )
  {
    if ( m_queryParameters.find( sID ) != m_queryParameters.end() )
      throw C2SRestException( "C2SRestMethodPrototype::addQueryParameter: " , "Query parameter already exists: " + sID , InternalServerError );

    m_queryParameters.insert( std::make_pair( sID , new C2SRestQueryParameter<Type>( sID , pDest , defaultv ) ) );
  }

  template <class Type>
  void C2SRestMethodPrototype::addQueryParameter( const std::string &sID , Type *pDest )
  {
    if ( m_queryParameters.find( sID ) != m_queryParameters.end() )
      throw C2SRestException( "C2SRestMethodPrototype::addQueryParameter: " , "Query parameter already exists: " + sID , InternalServerError );

    m_queryParameters.insert( std::make_pair( sID , new C2SRestQueryParameter<Type>( sID , pDest ) ) );
  }

}

#endif /* C2SRESTMETHODPROTOTYPE_H_ */
