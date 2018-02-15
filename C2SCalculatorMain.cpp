#include "C2SSettings.h"
#include "C2SRestResourcePrototype.h"
#include "C2SHttpServer.h"
#include "C2SCalculatorRestMethodPrototype.h"

const unsigned short iServerPort = 8888;

const std::string sCalculatorRESTResourceContextRoot = "calculator";

int main( int , char ** )
{
  using namespace c2s;
  using namespace c2s::calculator;

  C2SSettings settingsForServer;
  settingsForServer.iPort = iServerPort;

  C2SRestResourcePrototype *pResource = C2SRestResourcePrototype::createRestResourceWithContextRoot( sCalculatorRESTResourceContextRoot );

  pResource->registerMethodPrototype( new C2SCalculatorRestMethodPrototype() );

  C2SHttpServer httpServer( settingsForServer );

  httpServer.registerResourcePrototype( pResource );

  httpServer.run();
}
