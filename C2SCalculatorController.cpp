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
      std::cout<<"Created Now"<<std::endl;
  	}

  	void C2SCalculatorController::clear(){
  		m_sCurrentNumber = "0";
  		m_sPreviousNumber ="undefined";
  		m_sOperation = "undefined";
      m_bFloat = false;
  	}

  	std::string C2SCalculatorController::perform(std::string number,std::string operation) {
      
      cpp_int intResult;
      cpp_dec_float_50 decResult;

  		if(!(m_sOperation.compare("mempls")!=0||m_sOperation.compare("memin")!=0||
        m_sOperation.compare("memrcl")!=0||m_sOperation.compare("clear")!=0)){
  			m_sOperation = operation;
  		}

      try{
        m_sCurrentNumber = number;
        if(m_sPreviousNumber.compare("undefined")!=0){
      		if(m_sOperation.compare("pls")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::add(a,b);
            } else {
              cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::add(a,b);
            }
      		}

      		if(m_sOperation.compare("min")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::sub(a,b);
            } else {
              cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::sub(a,b);
            }
      		}

      		if(m_sOperation.compare("div")==0){
            m_bFloat = true;
            cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
            decResult = C2SCalculator<cpp_dec_float_50>::div(a,b);
      		}

      		if(m_sOperation.compare("mul")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::mul(a,b);
            } else {
              cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::mul(a,b);
            }
      		}

      		if(m_sOperation.compare("mod")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::mod(a,b);
            } else {
              throw std::invalid_argument( "should be integer to mod" );
            }
      		}

          if(m_sOperation.compare("sqrt")==0){
            m_bFloat = true;
            cpp_dec_float_50 num(m_sCurrentNumber);
            decResult = C2SCalculator<cpp_dec_float_50>::sqrt(num);
          }
          std::cout<<intResult<<" "<<decResult<<std::endl;
          m_sPreviousNumber = m_sCurrentNumber;
          m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);

          return m_sCurrentNumber;
        }

    		if(m_sOperation.compare("mempls")==0){
            if(!m_bFloat){
              cpp_int a(m_sMemory),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::add(a,b);
            } else {
              cpp_dec_float_50 a(m_sMemory),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::add(a,b);
            }
            m_sMemory = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
    		}

    		if(m_sOperation.compare("memin")==0){
            if(!m_bFloat){
              cpp_int a(m_sMemory),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::sub(a,b);
            } else {
              cpp_dec_float_50 a(m_sMemory),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::sub(a,b);
            }
            m_sMemory = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
    		}

    		if(m_sOperation.compare("memrcl")==0){
            return m_sMemory;
    		}

    		if(m_sOperation.compare("clear")==0){
    			clear();
    			return m_sCurrentNumber;
    		}
      } catch (const std::exception& e) {
          clear();
          throw std::invalid_argument( "Operation failed!" );
      }
      return m_sCurrentNumber;
  	}
  }
}