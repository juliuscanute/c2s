#ifndef C2S_CALCULATOR_CONTROLLER_H
#define C2S_CALCULATOR_CONTROLLER_H
#include<string>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>

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
  		std::string perform(std::string number,std::string operation);
  	};
  }
}
#endif