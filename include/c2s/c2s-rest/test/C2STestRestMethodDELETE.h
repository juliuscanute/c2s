/*
 * C2STestRestMethodDELETE.h
 *
 *  Created on: Mar 20, 2012
 *      Author: gack
 */

#ifndef C2STESTRESTMETHODDELETE_H_
#define C2STESTRESTMETHODDELETE_H_

#include "C2SRestMethodPrototypeDELETE.h"

namespace c2s
{

  namespace test
  {

    class C2STestRestMethodDELETE : public C2SRestMethodPrototypeDELETE
    {
    public:

      C2STestRestMethodDELETE();

      virtual ~C2STestRestMethodDELETE();

      C2SHttpResponse *process();

      C2SRestMethodPrototypeDELETE *clone() const;

      static const std::string sPath;

    };

  }

}

#endif /* C2STESTRESTMETHODDELETE_H_ */
