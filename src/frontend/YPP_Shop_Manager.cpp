#include "CDataBase.h"
#include "frontend/CInputArguments.h"

#include "JsonUtils.h"

using namespace ypp_sm;
using namespace frontend;

int main( const int aArgsCount, const char** aArgs )
{
	CInputArguments inputArguments( aArgsCount, aArgs );
	if( !inputArguments.WillRun() )
		return 0;

	auto dataBase = ValueFromJSONFile<CDataBase>( inputArguments.GetJSONFileName() );

	return 0;
}
