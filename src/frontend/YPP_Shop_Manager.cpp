#include "CDataBase.h"
#include "frontend/CInputArguments.h"
#include "frontend/CMainMenuSelector.h"

#include "JsonUtils.h"

using namespace ypp_sm;
using namespace frontend;

int main( const int aArgsCount, const char** aArgs )
{
	if( CInputArguments inputArguments( aArgsCount, aArgs ); inputArguments.WillRun() )
	{
		auto dataBase = ValueFromJSONFile<CDataBase>( inputArguments.GetJSONFileName() );
		CMainMenuSelector{}( dataBase, inputArguments.GetJSONFileName() );
	}
	return 0;
}
