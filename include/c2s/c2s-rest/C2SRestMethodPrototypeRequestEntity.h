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


#ifndef C2SRESTMETHODPROTOTYPEREQUESTENTITY_H_
#define C2SRESTMETHODPROTOTYPEREQUESTENTITY_H_

#include "C2SRestMethodPrototypeResponseEntity.h"

#include "C2SHttpEntityUnstreamerBase.h"

#include <map>
#include <iostream>

namespace c2s
{

  template <class ResponseEntityType>
  class C2SRestMethodPrototypeRequestEntity : public C2SRestMethodPrototypeResponseEntity<ResponseEntityType>
  {
  public:

    virtual C2SHttpResponse *processRequest( const C2SHttpRequest &request );

  protected:

    C2SRestMethodPrototypeRequestEntity( C2SHttpMethod method , const std::string &sPath );

    virtual ~C2SRestMethodPrototypeRequestEntity(){};

    virtual void installRequestEntityUnstreamer( C2SHttpEntityUnstreamerBase *pRequestEntityUnstreamer );

  private:

    C2SRestMethodPrototypeRequestEntity( const C2SRestMethodPrototypeRequestEntity & );

    C2SRestMethodPrototypeRequestEntity &operator=( const C2SRestMethodPrototypeRequestEntity & );

    void unstreamRequestEntity( const C2SHttpRequest &request );

    C2SHttpEntityUnstreamerBase *detectRequestEntityUnstreamerForMediaType( const C2SHttpMediaType &requestEntityMediaType );

    bool isMediaTypeInstalled( const C2SHttpMediaType &mediaType ) const;

    std::map<std::string,C2SHttpEntityUnstreamerBase*> m_requestEntityStreamersByMediaType;

  };

  template <class ResponseEntityType>
  C2SRestMethodPrototypeRequestEntity<ResponseEntityType>::C2SRestMethodPrototypeRequestEntity( C2SHttpMethod method , const std::string &sPath )
    : C2SRestMethodPrototypeResponseEntity<ResponseEntityType>( method , sPath )
  {

  }

  template <class ResponseEntityType>
  C2SHttpResponse *C2SRestMethodPrototypeRequestEntity<ResponseEntityType>::processRequest( const C2SHttpRequest &request )
  {
    this->unstreamRequestEntity( request );
    return C2SRestMethodPrototypeResponseEntity<ResponseEntityType>::processRequest( request );
  }

  template <class ResponseEntityType>
  void C2SRestMethodPrototypeRequestEntity<ResponseEntityType>::unstreamRequestEntity( const C2SHttpRequest &request )
  {
    C2SHttpEntityUnstreamerBase *pRequestEntityMediaTypeUnstreamer = this->detectRequestEntityUnstreamerForMediaType( request.header().Fields.getContentType() );
    if ( pRequestEntityMediaTypeUnstreamer )
      pRequestEntityMediaTypeUnstreamer->unstream( request.entity() );
  }

  template <class ResponseEntityType>
  C2SHttpEntityUnstreamerBase *C2SRestMethodPrototypeRequestEntity<ResponseEntityType>::detectRequestEntityUnstreamerForMediaType( const C2SHttpMediaType &requestEntityMediaType )
  {
    if ( m_requestEntityStreamersByMediaType.size() == 0 && requestEntityMediaType.Type == C2SHttpMediaType::wildcard )
      return NULL;

    if ( !this->isMediaTypeInstalled( requestEntityMediaType ) )
      throw C2SRestException( "C2SRestMethodPrototypeRequestEntity::detectRequestEntityUnstreamerForMediaType: " , "Request media type cannot be handled by server" , UnsupportedMediaType );

    return m_requestEntityStreamersByMediaType.find( requestEntityMediaType.Type )->second;
  }

  template <class ResponseEntityType>
  void C2SRestMethodPrototypeRequestEntity<ResponseEntityType>::installRequestEntityUnstreamer( C2SHttpEntityUnstreamerBase *pRequestEntityUnstreamer )
  {
    C2SHttpMediaType acceptedMediaTypeForNewUnstreamer = pRequestEntityUnstreamer->getAcceptedMediaType();
    if ( this->isMediaTypeInstalled( acceptedMediaTypeForNewUnstreamer ) )
      throw C2SRestException( "C2SRestMethodPrototypeRequestEntity::installRequestEntityUnstreamer: " , "Entity unstreamer for media type already installed: " + acceptedMediaTypeForNewUnstreamer.Type , InternalServerError );

    m_requestEntityStreamersByMediaType[ acceptedMediaTypeForNewUnstreamer.Type ] = pRequestEntityUnstreamer;
  }

  template <class ResponseEntityType>
  bool C2SRestMethodPrototypeRequestEntity<ResponseEntityType>::isMediaTypeInstalled( const C2SHttpMediaType &mediaType ) const
  {
    return m_requestEntityStreamersByMediaType.find( mediaType.Type ) != m_requestEntityStreamersByMediaType.end();
  }

}

#endif /* C2SRESTMETHODPROTOTYPEREQUESTENTITY_H_ */
