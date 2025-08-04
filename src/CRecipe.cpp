#include "CRecipe.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

namespace ypp_sm
{

CRecipe::CRecipe( std::string_view aName,
		const items& aItems,
		count aDoubloonCount,
		count aYield,
		int_price aPriceAdjustment ) try :
	AKeyable( aName ),
	mItems( aItems ),
	mDoubloonCount( aDoubloonCount ),
	mYield( CheckPositiveness( aYield, "recipe yield" ) ),
	mPriceAdjustment( aPriceAdjustment )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a recipe." )

CRecipe::CRecipe( const json& aJSON, std::string_view aName ) try :
	AKeyable( aName ),
	mDoubloonCount( ValueFromOptionalJSONKey<count>( aJSON, DOUBLOONS_KEY ) ),
	mYield( CheckPositiveness( ValueFromOptionalJSONKey( aJSON, YIELD_KEY, DEFAULT_YIELD ), "recipe yield" ) )
{
	for( const auto& ingredientJSON : aJSON[ INGREDIENTS_KEY ].items() )
		mItems.emplace_back( types::CRecipe::item{ ValueFromRequiredJSONKey<types::CRecipe::ingredients_type>(
				ingredientJSON.value(), INGREDIENT_KEY ), ValueFromRequiredJSONKey<count>( ingredientJSON.value(), COUNT_KEY ) } );
}

YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe from JSON " << aJSON.dump() <<"." )

void CRecipe::JSON( json& aJSON ) const noexcept
{
	AddToOptionalJSONKey( aJSON, mDoubloonCount, DOUBLOONS_KEY );
	AddToOptionalJSONKey( aJSON, mYield, YIELD_KEY, DEFAULT_YIELD );

	if( !mItems.empty() )
	{
		auto& ingredientsJSON = aJSON[ INGREDIENTS_KEY ];
		for( const auto& item : mItems )
		{
			json ingredientJSON;
			AddToJSONKey( ingredientJSON, item.ingredients, INGREDIENT_KEY );
			AddToJSONKey( ingredientJSON, item.ingredient_count, COUNT_KEY );
			ingredientsJSON.push_back( ingredientJSON );
		}
	}
}

std::string CRecipe::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	ss << std::string( aIndentDepth, aIndentChar ) << GetKey() << ":\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << DOUBLOONS_KEY << ": " << mDoubloonCount << "\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << YIELD_KEY << ": " << mYield << "\n";
	if( !mItems.empty() )
	{
		ss << std::string( aIndentDepth + 1, aIndentChar ) << INGREDIENTS_KEY << ":\n";
		for( const auto& item : mItems )
		{
			ss << std::string( aIndentDepth + 2, aIndentChar ) << item.ingredient_count << " of:\n";
			for( const auto& ingredient : item.ingredients )
				ss << std::string( aIndentDepth + 3, aIndentChar ) << ingredient << "\n";
		}
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

CRecipe::int_price CRecipe::GetPriceAdjustment() const noexcept
{
	return mPriceAdjustment;
}

const CRecipe::items& CRecipe::GetItems() const noexcept
{
	return mItems;
}

} // ypp_sm namespace
