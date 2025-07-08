#include <fstream>

#include "CDataBase.h"
#include "frontend/CInputArguments.h"

using namespace ypp_sm;
using namespace frontend;

namespace
{

template <typename T> T CreateFromJSONFile( std::string_view aFileName );

} // anonymous namespace

int main( const int aArgsCount, const char** aArgs )
{
	CInputArguments inputArguments( aArgsCount, aArgs );
	if( !inputArguments.WillRun() )
		return 0;

	auto dataBase = CreateFromJSONFile<CDataBase>( inputArguments.GetJSONFileName() );

	return 0;
}

namespace
{

template <typename T> T CreateFromJSONFile( std::string_view aFileName )
{
	return T{ types::IJsonable::json::parse( std::ifstream{ aFileName.data() } ) };
}


} // anonymous namespace
