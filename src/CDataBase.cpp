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

void CDataBase::JSON( json& aJSON ) const noexcept
{
	if( !mRecipes.GetKeySets().empty() )
		AddToJSONKey( aJSON, mRecipes, RECIPES_KEY );
	if( !mPrices.GetKeySets().empty() )
		AddToJSONKey( aJSON, mPrices, PRICES_KEY );
}

std::string CDataBase::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	if( !mRecipes.GetKeySets().empty() )
	{
		ss << std::string( aIndentDepth, aIndentChar ) << RECIPES_KEY << ":\n";
		ss << mRecipes.GetDescription( aIndentDepth + 1, aIndentChar );
	}
if( !mPrices.GetKeySets().empty() )
	{
		ss << std::string( aIndentDepth, aIndentChar ) << PRICES_KEY << ":\n";
		ss << mPrices.GetDescription( aIndentDepth + 1, aIndentChar );
	}
	return ss.str();
}

const CDataBase::recipes& CDataBase::GetRecipes() const noexcept
{
	return mRecipes;
}
const CDataBase::prices& CDataBase::GetPrices() const noexcept
{
	return mPrices;
}

} // ypp_sm namespace
