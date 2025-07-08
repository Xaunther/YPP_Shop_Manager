#include "CPrices.h"

#include "ExceptionUtils.h"

namespace ypp_sm
{

CPrices::CPrices( const prices_map& aPricesMap ) try :
	mPricesMap( aPricesMap )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the prices." )

const CPrices::prices_map& CPrices::GetPricesMap() const noexcept
{
	return mPricesMap;
}

} // ypp_sm namespace
