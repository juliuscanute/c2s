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

#ifndef C2SRESTPARAMETER_H_
#define C2SRESTPARAMETER_H_

#include "C2SRestParameterBase.h"
#include "C2SRestException.h"

#include <sstream>

namespace c2s
{

  template <class Type>
  class C2SRestParameter : public C2SRestParameterBase
  {
  public:

    C2SRestParameter( Type *pObjectToWriteParameterValue )
      : m_pObjectToWriteParameterValue( pObjectToWriteParameterValue )
    {};

    virtual ~C2SRestParameter(){};

    virtual bool isPossibleToConvert( const std::string &sParameterValueAsString ) const;

    virtual void convertAndSetParameterValue( const std::string &sParameterValueAsString );

    void setParameterValue( const Type &parameterValueToSet );

  protected:

    Type *m_pObjectToWriteParameterValue;

  };

  template <class Type>
  bool C2SRestParameter<Type>::isPossibleToConvert( const std::string &sParameterValueAsString ) const
  {
    std::istringstream strs( sParameterValueAsString );
    Type dummy = Type( 0 );
    return ( strs >> dummy ) != 0;
  }

  //specialized for strings
  template <>
  inline bool C2SRestParameter<std::string>::isPossibleToConvert( const std::string & ) const
  {
    //will always match
    return true;
  }

  template <class Type>
  void C2SRestParameter<Type>::convertAndSetParameterValue( const std::string &sParameterValueAsString )
  {
    std::istringstream strs( sParameterValueAsString );
    if( !( strs >> ( *m_pObjectToWriteParameterValue ) ) )
      throw C2SRestException( "C2SRestPathParameter::convertAndSetParameterValue: " , "Cannot cast parameter \"" + sParameterValueAsString + "\"" , BadRequest );
  }

  //specialized for strings
  template <>
  void inline C2SRestParameter<std::string>::convertAndSetParameterValue( const std::string &sParameterValueAsString )
  {
    *m_pObjectToWriteParameterValue = sParameterValueAsString;
  }

  template <class Type>
  void C2SRestParameter<Type>::setParameterValue( const Type &parameterValueToSet )
  {
    *m_pObjectToWriteParameterValue = parameterValueToSet;
  }

}

#endif /* C2SRESTPARAMETER_H_ */
