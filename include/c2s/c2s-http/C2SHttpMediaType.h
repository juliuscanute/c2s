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

#ifndef C2SHTTPMEDIATYPE_H_
#define C2SHTTPMEDIATYPE_H_

#include <string>

namespace c2s
{

  class C2SHttpMediaType
  {
  public:

    C2SHttpMediaType( const std::string &sType );

    C2SHttpMediaType();

    bool operator<( const C2SHttpMediaType &t ) const { return fQ < t.fQ; }

    std::string Type;

    std::string Charset;

    float fQ;

    void detect( const char *data , unsigned int size );

    std::string toString() const;

    static const std::string wildcard;

    static const std::string text__plain;

    static const std::string text__css;

    static const std::string text__html;

    static const std::string application__xhtml_xml;

    static const std::string application__xml;

    static const std::string application__json;

    static const std::string application__x_www_form_urlencoded;

  private:

    template <class Handler>
    friend void splitNhandle( const char *data , unsigned int size , char separator , Handler *pHandler );

    void operator()( const char *data , unsigned int size );

    void detectMediaType( const char *data , unsigned int size );

    void detectQualityValue( const char *data , unsigned int size );

    void detectCharset( const char *data , unsigned int size );

    bool isCharSet( const char *data , unsigned int size );

    static const std::string sCharSetID;

    unsigned int iArgIdx;

  };

}

#endif /* C2SHTTPMEDIATYPE_H_ */
