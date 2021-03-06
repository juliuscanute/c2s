#ifndef C2S_CALCULATOR_H
#define C2S_CALCULATOR_H
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>
namespace c2s
{
  namespace calculator
  {
  	template <class T>
  	class C2SCalculator{
  	public:
  		static T add(T a,T b){
  			return a+b;
  		}

  		static T sub(T a,T b){
  			return a-b;
  		}

  		static T mul(T a,T b){
  			return a*b;
  		}

  		static T div(T a,T b){
  			if(b == 0)
  				throw std::invalid_argument( "divide by zero" );
  			return a/b;
  		}

  		static T mod(T a, T b){
  			if(b == 0)
  				throw std::invalid_argument( "divide by zero" );
  			return a%b;
  		}

  		static T sqrt(T num){
  			if(num < 0)
  				throw std::invalid_argument( "imaginary number" );
  			return boost::multiprecision::sqrt(num);
  		}
  	};
  }
}
#endif