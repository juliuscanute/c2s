#include "C2SCalculatorRestMethodPrototype.h"

#include "C2SHttpEntityStreamerPlainText.h"
#include "DateTimeLogger.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace c2s
{
  namespace calculator
  {

    const std::string C2SCalculatorRestMethodPrototype::sPath = "calculator";
    const std::set<std::string> C2SCalculatorRestMethodPrototype::m_mOperations = {"eql","pls","min","div"
                                                                                        ,"mul","mod","sqrt"
                                                                                        ,"mempls","memmin","memrcl"
                                                                                        ,"clear"};

    C2SCalculatorRestMethodPrototype::C2SCalculatorRestMethodPrototype()
      : C2SRestMethodPrototypeGET<std::string>( sPath ),
        m_pLogger( new io::DateTimeLogger( "calculator" ) ),
        m_sNumber(),
        m_sOperation()
    {
      C2SRestMethodPrototypeGET<std::string>::installEntityStreamer( new C2SHttpEntityStreamerPlainText() );
      C2SRestMethodPrototypeGET<std::string>::addQueryParameter( "number" , &m_sNumber , "invalid" );
      C2SRestMethodPrototypeGET<std::string>::addQueryParameter( "operation" , &m_sOperation , "invalid" ); 
    }

    C2SCalculatorRestMethodPrototype::~C2SCalculatorRestMethodPrototype()
    {
      delete m_pLogger;
    }

    C2SHttpResponse *C2SCalculatorRestMethodPrototype::process()
    {
      bool numIsInt = true,numIsFloat=false;
      using boost::multiprecision::cpp_int;
      using boost::multiprecision::cpp_dec_float_50;
      if(m_sNumber.compare("invalid")==0){
        m_sFinalResponseEntity = std::string("Number is not specified in query.");
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      } else {

        try { 
          cpp_int number(m_sNumber);
        } 
        catch (const std::exception& e) {
          numIsInt = false;
        }
        
        if(!numIsInt){
          try { 
            cpp_dec_float_50 number(m_sNumber);
            numIsFloat = true;
          } 
          catch (const std::exception& e) {
            m_sFinalResponseEntity = std::string("Number format unrecognized.");
            return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
          }
        }

      }
      if(m_mOperations.find(m_sOperation)==m_mOperations.end()){
        m_sFinalResponseEntity = std::string("Unsupported operation.");
        return C2SRestMethodPrototypeGET<std::string>::buildResponse( BadRequest , m_sFinalResponseEntity );
      }
      m_sFinalResponseEntity = std::string("Number: ")+m_sNumber+std::string(" Operation: ")+m_sOperation;
      return C2SRestMethodPrototypeGET<std::string>::buildResponse( OK , m_sFinalResponseEntity );
    }

    C2SCalculatorRestMethodPrototype *C2SCalculatorRestMethodPrototype::clone() const
    {
      return new C2SCalculatorRestMethodPrototype();
    }

  }
}
