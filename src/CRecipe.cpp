#include "CRecipe.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

namespace ypp_sm
{

CRecipe::CRecipe( std::string_view aName, const items& aItems, count aYield ) try :
	AKeyable( aName ),
	mItems( aItems ),
	mYield( CheckPositiveness( aYield, "recipe yield" ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a recipe." )

CRecipe::CRecipe( const json& aJSON, std::string_view aName ) try :
	AKeyable( aName ),
	mYield( CheckPositiveness( ValueFromOptionalJSONKey( aJSON, YIELD_KEY, DEFAULT_YIELD ), "recipe yield" ) )
{
	const auto foundIngredients = aJSON.find( INGREDIENTS_KEY );
	if( foundIngredients != aJSON.cend() )
		for( const auto& itemJSON : (*foundIngredients).items() )
			mItems.emplace( itemJSON.value(), itemJSON.key() );
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe from JSON " << aJSON.dump() <<"." )

void CRecipe::JSON( json& aJSON ) const noexcept
{
	AddToOptionalJSONKey( aJSON, mYield, YIELD_KEY, DEFAULT_YIELD );

	if( !mItems.empty() )
	{
		auto& ingredientsJSON = aJSON[ INGREDIENTS_KEY ];
		for( const auto& item : mItems )
			AddToJSONKey( ingredientsJSON, item, item.GetKey() );
	}
}

CRecipe::count CRecipe::GetYield() const noexcept
{
	return mYield;
}

const CRecipe::items& CRecipe::GetItems() const noexcept
{
	return mItems;
}

} // ypp_sm namespace
