#include "CPrices.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

CPrices::CPrices( const prices_map& aPricesMap ) try :
	mPricesMap( aPricesMap )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the prices." )

CPrices::CPrices( const json& aJSON ) try
{
	for( const auto& pricesJSON : aJSON.items() )
	{
		types::CPrices::prices prices;
		for( const auto& priceJSON : pricesJSON.value().items() )
			prices.emplace( priceJSON.value(), priceJSON.key() );
		mPricesMap.emplace( pricesJSON.key(), std::move( prices ) );
	}
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating from the JSON object " << aJSON.dump() << "." )

void CPrices::JSON( json& aJSON ) const noexcept
{
	for( const auto& [ key, prices ] : mPricesMap )
	{
		json& keyPricesJSON = aJSON[ key ];
		for( const auto& price : prices )
			AddToJSONKey( keyPricesJSON, price, price.GetKey() );
	}
}

const CPrices::prices_map& CPrices::GetPricesMap() const noexcept
{
	return mPricesMap;
}

} // ypp_sm namespace
