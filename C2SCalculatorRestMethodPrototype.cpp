#include "C2SCalculatorRestMethodPrototype.h"

#include "C2SHttpEntityStreamerPlainText.h"
#include "DateTimeLogger.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_50;

namespace c2s
{
  namespace calculator
  {

    const std::string C2SCalculatorRestMethodPrototype::sPath = "calculator";
    const std::set<std::string> C2SCalculatorRestMethodPrototype::m_mOperations = {"eql","add","sub","div"
                                                                                        ,"mul","mod","sqrt"
                                                                                        ,"mempls","memmin","memrcl"};

    C2SCalculatorRestMethodPrototype::C2SCalculatorRestMethodPrototype()
      : C2SRestMethodPrototypeGET<std::string>( sPath ),
        m_pLogger( new io::DateTimeLogger( "calculator" ) ),
        m_sCNumber(),m_sPNumber(),m_sCMemory(),m_sOperation()
    {
      C2SRestMethodPrototypeGET<std::string>::installEntityStreamer( new C2SHttpEntityStreamerPlainText() );
      C2SRestMethodPrototypeGET<std::string>::addQueryParameter( "cnumber" , &m_sCNumber , "invalid" );
      C2SRestMethodPrototypeGET<std::string>::addQueryParameter( "pnumber" , &m_sPNumber , "invalid" );
      C2SRestMethodPrototypeGET<std::string>::addQueryParameter( "cmemory" , &m_sCMemory , "invalid" );
      C2SRestMethodPrototypeGET<std::string>::addQueryParameter( "operation" , &m_sOperation , "invalid" ); 
    }

    C2SCalculatorRestMethodPrototype::~C2SCalculatorRestMethodPrototype()
    {
      delete m_pLogger;
    }

    inline bool C2SCalculatorRestMethodPrototype::isInt(std::string &number){
        try { 
          cpp_int number(number);
        } 
        catch (const std::exception& e) {
          return false;
        }
        return true;
    }


    inline bool C2SCalculatorRestMethodPrototype::isFloat(std::string &number){
        try { 
            cpp_dec_float_50 number(number);
          } 
          catch (const std::exception& e) { 
            return false;
          }
        return true;
    }

    inline bool C2SCalculatorRestMethodPrototype::isNumber(std::string &number){
      return isInt(number) & isFloat(number);
    }

    C2SHttpResponse *C2SCalculatorRestMethodPrototype::process()
    {

      bool isFloat = false;
      if(m_sCNumber.compare("invalid")!=0 && isNumber(m_sCNumber)){
        if(!isInt(m_sCNumber)){
          isFloat = true; 
        }
      } else {
        m_sFinalResponseEntity = std::string("Current number is not specified in query.")+m_sCNumber;
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      }

      if(m_sPNumber.compare("invalid")!=0 && isNumber(m_sPNumber)){
        if(!isInt(m_sPNumber)){
          isFloat = true; 
        }
      } else {
        m_sFinalResponseEntity = std::string("Previous number is not specified in query.");
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      }

      if(m_sCMemory.compare("invalid")==0 || !isNumber(m_sCMemory)){
        m_sFinalResponseEntity = std::string("Current memory is not specified in query.");
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      }

      if(m_sOperation.compare("invalid")==0 || m_mOperations.find(m_sOperation) == m_mOperations.end()){
        m_sFinalResponseEntity = std::string("Operation not specified in query.");
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      }


      C2SCalculatorController cController(m_sCNumber,m_sPNumber,m_sOperation,m_sCMemory,isFloat);
      try{
        cController.perform();

        m_sFinalResponseEntity = "{\"CurrentNumber\":"+cController.getCurrentNumber()+"," 
        +"\"PreviousNumber\":"+cController.getPreviousNumber()+"," 
        +"\"Operation\":"+"\""+cController.getOperation()+"\""+"," 
        +"\"MemoryValue\":"+cController.getMemoryValue()+ 
        "}";

      }catch (const std::exception& e) {
        m_sFinalResponseEntity = std::string("Operation failed!");
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      }
      return C2SRestMethodPrototypeGET<std::string>::buildResponse( OK , m_sFinalResponseEntity );
    }

    C2SCalculatorRestMethodPrototype *C2SCalculatorRestMethodPrototype::clone() const
    {
      return new C2SCalculatorRestMethodPrototype();
    }

  }
}