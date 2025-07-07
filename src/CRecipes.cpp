#include "CRecipes.h"

#include <nlohmann/json.hpp>

#include "ExceptionUtils.h"

namespace ypp_sm
{

CRecipes::CRecipes( const shop_recipes& aShopRecipes ) try :
	mShopRecipes( aShopRecipes )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the recipes." )

CRecipes::CRecipes( const json& aJSON ) try
{
	for( const auto& commodityRecipesJSON : aJSON.items() )
	{
		types::CRecipes::recipes recipes;
		for( const auto& recipeJSON : commodityRecipesJSON.value().items() )
		{
			types::CRecipes::recipe_items recipeItems;
			for( const auto& item : recipeJSON.value().items() )
				recipeItems.emplace( item.value(), item.key() );
			recipes.emplace( recipeJSON.key(), std::move( recipeItems ) );
		}
		mShopRecipes.emplace( commodityRecipesJSON.key(), std::move( recipes ) );
	}
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating from the JSON object " << aJSON.dump() << "." )

const CRecipes::shop_recipes& CRecipes::GetShopRecipes() const noexcept
{
	return mShopRecipes;
}

} // ypp_sm namespace
