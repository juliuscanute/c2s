/*
 * C2STestRestMethodAddDuplicatePOST.h
 *
 *  Created on: Mar 20, 2012
 *      Author: gack
 */

#ifndef C2STESTRESTMETHODADDDUPLICATEPOST_H_
#define C2STESTRESTMETHODADDDUPLICATEPOST_H_

#include "C2SRestMethodPrototypePOST.h"

namespace c2s
{
  namespace test
  {

    class C2STestRestMethodAddDuplicatePOST : public C2SRestMethodPrototypePOST<unsigned int>
    {
    public:

      C2STestRestMethodAddDuplicatePOST();

      C2SHttpResponse *process();

      C2STestRestMethodAddDuplicatePOST *clone() const;

    private:

      unsigned int m_iArg1;

      unsigned int m_iArg2;

    };

  }
}

#endif /* C2STESTRESTMETHODADDDUPLICATEPOST_H_ */
