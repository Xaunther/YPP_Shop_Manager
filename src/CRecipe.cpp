#include "CRecipe.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

namespace ypp_sm
{

CRecipe::CRecipe( std::string_view aName, const items& aItems, count aDoubloonCount, count aYield ) try :
	AKeyable( aName ),
	mItems( aItems ),
	mDoubloonCount( aDoubloonCount ),
	mYield( CheckPositiveness( aYield, "recipe yield" ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a recipe." )

CRecipe::CRecipe( const json& aJSON, std::string_view aName ) try :
	AKeyable( aName ),
	mDoubloonCount( ValueFromOptionalJSONKey<count>( aJSON, DOUBLOONS_KEY ) ),
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

std::string CRecipe::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	ss << std::string( aIndentDepth, aIndentChar ) << GetKey() << ":\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << YIELD_KEY << ": " << mYield << "\n";
	if( !mItems.empty() )
	{
		ss << std::string( aIndentDepth + 1, aIndentChar ) << INGREDIENTS_KEY << ":\n";
		for( const auto& item : mItems )
			ss << item.GetDescription( aIndentDepth + 2, aIndentChar );
	}
	return ss.str();
}

CRecipe::count CRecipe::GetYield() const noexcept
{
	return mYield;
}

CRecipe::count CRecipe::GetDoubloonCount() const noexcept
{
	return mDoubloonCount;
}

const CRecipe::items& CRecipe::GetItems() const noexcept
{
	return mItems;
}

} // ypp_sm namespace
