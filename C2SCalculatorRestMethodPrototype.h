#ifndef C2S_CALCULATOR_REST_METHOD_PROTOTYPE_H
#define C2S_CALCULATOR_REST_METHOD_PROTOTYPE_H

#include <set>
#include "C2SRestMethodPrototypeGET.h"

namespace c2s
{
  namespace io
  {
    class DateTimeLogger;
  }

  namespace calculator
  {

    class C2SCalculatorRestMethodPrototype : public C2SRestMethodPrototypeGET<std::string>
    {
    public:

      C2SCalculatorRestMethodPrototype();

      virtual ~C2SCalculatorRestMethodPrototype();

      C2SHttpResponse *process();

      C2SCalculatorRestMethodPrototype *clone() const;

    private:

      const static std::string sPath;
      const static std::set<std::string> m_mOperations;

      io::DateTimeLogger *m_pLogger;

      std::string m_sNumber;

      std::string m_sOperation;

      std::string m_sFinalResponseEntity;

    };

  }
}

#endif 
