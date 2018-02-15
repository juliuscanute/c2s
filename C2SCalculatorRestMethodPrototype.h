#ifndef C2S_CALCULATOR_REST_METHOD_PROTOTYPE_H
#define C2S_CALCULATOR_REST_METHOD_PROTOTYPE_H

#include <set>
#include "C2SRestMethodPrototypeGET.h"
#include "C2SCalculatorController.h"

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
      bool isInt(std::string &number);
      bool isFloat(std::string &number);
      bool isNumber(std::string &number);

      C2SCalculatorRestMethodPrototype *clone() const;

    private:

      const static std::string sPath;
      const static std::set<std::string> m_mOperations;

      io::DateTimeLogger *m_pLogger;

      std::string m_sCNumber;
      std::string m_sPNumber;
      std::string m_sCMemory;
      std::string m_sOperation;

      std::string m_sFinalResponseEntity;


    };

  }
}

#endif 
