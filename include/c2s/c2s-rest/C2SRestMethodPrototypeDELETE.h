/*
 * C2SRestMethodPrototypeDELETE.h
 *
 *  Created on: Mar 20, 2012
 *      Author: gack
 */

#ifndef C2SRESTMETHODPROTOTYPEDELETE_H_
#define C2SRESTMETHODPROTOTYPEDELETE_H_

#include "C2SRestMethodPrototype.h"

namespace c2s
{

  class C2SRestMethodPrototypeDELETE : public C2SRestMethodPrototype
  {
  public:

    C2SRestMethodPrototypeDELETE( const std::string &sPath )
      : C2SRestMethodPrototype( C2S_DELETE , sPath )
    {}

  private:

    C2SRestMethodPrototypeDELETE( const C2SRestMethodPrototypeDELETE & );

    C2SRestMethodPrototypeDELETE &operator=( const C2SRestMethodPrototypeDELETE & );

  };

}

#endif /* C2SRESTMETHODPROTOTYPEDELETE_H_ */
