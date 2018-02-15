#include "C2SCalculatorController.h"

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_50;

namespace c2s
{
  namespace calculator
  {
  	
  	C2SCalculatorController::C2SCalculatorController():m_sCurrentNumber("0"),
  	m_sPreviousNumber("undefined"),m_sOperation("undefined"),m_sMemory("0"),m_bFloat(false)
  	{

  	}

  	void C2SCalculatorController::clear(){
  		m_sCurrentNumber = "0";
  		m_sPreviousNumber ="undefined";
  		m_sOperation = "undefined";
      m_bFloat = false;
  	}

  	std::string C2SCalculatorController::perform(std::string number,std::string operation) {

  		if(m_sOperation.compare("eql")!=0){
  			m_sOperation = operation;
  		}

  		if(m_sOperation.compare("pls")!=0){
        if(!m_bFloat){
          cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_int>::add(a,b);
        } else {
          cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_dec_float_50>::add(a,b);
        }
  		}

  		if(m_sOperation.compare("min")!=0){
        if(!m_bFloat){
          cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_int>::sub(a,b);
        } else {
          cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_dec_float_50>::sub(a,b);
        }
  		}

  		if(m_sOperation.compare("div")!=0){
        if(!m_bFloat){
          cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_int>::div(a,b);
        } else {
          cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_dec_float_50>::div(a,b);
        }
  		}

  		if(m_sOperation.compare("mul")!=0){
        if(!m_bFloat){
          cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_int>::mul(a,b);
        } else {
          cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_dec_float_50>::mul(a,b);
        }
  		}

  		if(m_sOperation.compare("mod")!=0){
        if(!m_bFloat){
          cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
          C2SCalculator<cpp_int>::mod(a,b);
        } 
  		}

  		if(m_sOperation.compare("mempls")!=0){

  		}

  		if(m_sOperation.compare("memin")!=0){

  		}

  		if(m_sOperation.compare("memrcl")!=0){

  		}

  		if(m_sOperation.compare("sqrt")!=0){

  		}

  		if(m_sOperation.compare("clear")!=0){
  			clear();
  			return m_sCurrentNumber;
  		}

  		if(m_sPreviousNumber.compare("undefined")!=0){

  		}

  		m_sPreviousNumber = m_sCurrentNumber;
  		m_sCurrentNumber = number;

  		return m_sCurrentNumber;
  	}
  }
}