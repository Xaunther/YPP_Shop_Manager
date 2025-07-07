#include "CRecipes.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

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

void CRecipes::JSON( json& aJSON ) const noexcept
{
	for( const auto& [ shop, recipes ] : mShopRecipes )
	{
		json& shopRecipesJSON = aJSON[ shop ];
		for( const auto& [ outputItem, items ] : recipes )
		{
			json& recipeJSON = shopRecipesJSON[ outputItem ];
			for( const auto& item : items )
				AddToJSONKey( recipeJSON, item, item.GetKey() );
		}
	}
}

const CRecipes::shop_recipes& CRecipes::GetShopRecipes() const noexcept
{
	return mShopRecipes;
}

} // ypp_sm namespace
