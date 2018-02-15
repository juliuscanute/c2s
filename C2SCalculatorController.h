#ifndef C2S_CALCULATOR_CONTROLLER_H
#define C2S_CALCULATOR_CONTROLLER_H
#include <string>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <sstream>

#define TOSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

#include "C2SCalculator.h"

namespace c2s
{
  namespace calculator
  {
  	class C2SCalculatorController {
  	private:
  		std::string m_sCurrentNumber;
  		std::string m_sPreviousNumber;
  		std::string m_sOperation;
  		std::string m_sMemory;
      bool m_bFloat;
      void clear();
  	public:
  		C2SCalculatorController();
      C2SCalculatorController(std::string currentNumber,std::string previousNumber,std::string operation,std::string memory,bool isFloat);
  		void perform();
      std::string getCurrentNumber();
      std::string getPreviousNumber();
      std::string getOperation();
      std::string getMemoryValue();
  	};
  }
}
#endif