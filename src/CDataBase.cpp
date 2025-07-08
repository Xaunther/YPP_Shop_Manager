#include "CDataBase.h"

namespace ypp_sm
{

CDataBase::CDataBase( const recipes& aRecipes, const prices& aPrices ) :
	mRecipes( aRecipes ),
	mPrices( aPrices )
{
}

CDataBase::CDataBase( const json& aJSON ) try :
	mRecipes( ValueFromOptionalJSONKey<recipes>( aJSON, RECIPES_KEY ) ),
	mPrices( ValueFromOptionalJSONKey<prices>( aJSON, PRICES_KEY ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe from JSON " << aJSON.dump() << "." )

const CDataBase::recipes& CDataBase::GetRecipes() const noexcept
{
	return mRecipes;
}
const CDataBase::prices& CDataBase::GetPrices() const noexcept
{
	return mPrices;
}

} // ypp_sm namespace
