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


    C2SCalculatorController::C2SCalculatorController(std::string currentNumber,std::string previousNumber,
      std::string operation,std::string memory,bool isFloat):m_sCurrentNumber(currentNumber),
    m_sPreviousNumber(previousNumber),m_sOperation(operation),m_sMemory(memory),m_bFloat(isFloat){

    }

  	void C2SCalculatorController::clear(){
  		m_sCurrentNumber = "undefined";
  		m_sPreviousNumber ="undefined";
  		m_sOperation = "undefined";
      m_bFloat = false;
  	}


    std::string C2SCalculatorController::getCurrentNumber(){
      return m_sCurrentNumber;
    }
    
    std::string C2SCalculatorController::getPreviousNumber(){
      return m_sPreviousNumber;
    }
    
    std::string C2SCalculatorController::getOperation(){
      return m_sOperation;
    }

    std::string C2SCalculatorController::getMemoryValue(){
      return m_sMemory;
    }

  	void C2SCalculatorController::perform() {
      
      cpp_int intResult;
      cpp_dec_float_50 decResult;
      std::string current = m_sCurrentNumber;
      try{
      		if(m_sOperation.compare("add")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::add(a,b);
            } else {
              cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::add(a,b);
            }
            m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
      		}

      		if(m_sOperation.compare("sub")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::sub(a,b);
            } else {
              cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::sub(a,b);
            }
            m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
      		}

      		if(m_sOperation.compare("div")==0){
            m_bFloat = true;
            cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
            decResult = C2SCalculator<cpp_dec_float_50>::div(a,b);
            m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
      		}

      		if(m_sOperation.compare("mul")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::mul(a,b);
            } else {
              cpp_dec_float_50 a(m_sPreviousNumber),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::mul(a,b);
            }
            m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
      		}

      		if(m_sOperation.compare("mod")==0){
            if(!m_bFloat){
              cpp_int a(m_sPreviousNumber),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::mod(a,b);
            } else {
              throw std::invalid_argument( "should be integer to mod" );
            }
            m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
      		}

          if(m_sOperation.compare("sqrt")==0){
            m_bFloat = true;
            cpp_dec_float_50 num(m_sCurrentNumber);
            decResult = C2SCalculator<cpp_dec_float_50>::sqrt(num);
            m_sCurrentNumber = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
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
            return;
    		}

    		if(m_sOperation.compare("memmin")==0){
            if(!m_bFloat){
              cpp_int a(m_sMemory),b(m_sCurrentNumber);
              intResult = C2SCalculator<cpp_int>::sub(a,b);
            } else {
              cpp_dec_float_50 a(m_sMemory),b(m_sCurrentNumber);
              decResult = C2SCalculator<cpp_dec_float_50>::sub(a,b);
            }
            m_sMemory = (m_bFloat)?TOSTR(decResult):TOSTR(intResult);
            return;
    		}

    		if(m_sOperation.compare("memrcl")==0){
            // return m_sMemory;
          m_sCurrentNumber = m_sMemory;
    		}

    		if(m_sOperation.compare("clear")==0){
    			clear();
          return;
    			// return m_sCurrentNumber;
    		}
      } catch (const std::exception& e) {
          clear();
          std::cerr << e.what();
          throw std::invalid_argument( "Operation failed!" );
      }
      // std::cout<<"value of current: "<<m_sCurrentNumber<<std::endl;
      m_sPreviousNumber = current;
      // return m_sCurrentNumber;
  	}
  }
}