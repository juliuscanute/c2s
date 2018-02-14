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

#ifndef C2SHTTPRESPONSE_H_
#define C2SHTTPRESPONSE_H_

#include "C2SHttpResponseHeader.h"
#include "C2SHttpEntity.h"
#include "C2SHttpParser.h"

#include <sstream>

namespace c2s
{

  class C2SHttpResponse
  {
  public:

    C2SHttpResponse( const C2SHttpResponseHeader &header );

    C2SHttpResponse();

    C2SHttpResponse( const C2SHttpResponse & );

    virtual ~C2SHttpResponse();

    C2SHttpResponse &operator=( const C2SHttpResponse & );

    void push( char *data , unsigned int size );

    const C2SHttpResponseHeader &header() const { return m_header; }

    C2SHttpResponseHeader &header() { return m_header; }

    //entity will be deleted
    void setEntity( C2SHttpEntity *pEntity );

    template <class Streamable>
    void getEntity( Streamable *pO ) const;

    const C2SHttpEntity *getEntity() const { return m_pBody; }

    void finished();

    static C2SHttpResponse *build( C2SHttpStatus status );

  private:

    C2SHttpParser m_parser;

    C2SHttpResponseHeader m_header;

    C2SHttpEntity *m_pBody;

  };

  template <class Streamable>
  void C2SHttpResponse::getEntity( Streamable *pO ) const
  {
    if ( !m_pBody )
      //TODO: throw exception???
      throw C2SHttpException( "C2SHttpResponse::getEntity: " , "Entity is NULL!" , InternalServerError );

    std::stringstream strs( std::string( m_pBody->data , m_pBody->size ) );
    if ( !( strs >> ( *pO ) ) )
      throw C2SHttpException( "C2SHttpResponse::getEntity: " , "Cannot stream entity to object!" , InternalServerError );
  }

  template <>
  inline void C2SHttpResponse::getEntity( std::string *pO ) const
  {
    if ( !m_pBody )
      //TODO: throw exception???
      throw C2SHttpException( "C2SHttpResponse::getEntity: " , "Entity is NULL!" , InternalServerError );

    *pO = std::string( m_pBody->data , m_pBody->size );
  }


}

#endif /* C2SHTTPRESPONSE_H_ */
