#include "CRecipes.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

CRecipes::CRecipes( const recipes_map& aRecipesMap ) try :
	mRecipesMap( aRecipesMap )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the recipes." )

CRecipes::CRecipes( const json& aJSON ) try
{
	for( const auto& commodityRecipesJSON : aJSON.items() )
	{
		types::CRecipes::recipes recipes;
		for( const auto& recipeJSON : commodityRecipesJSON.value().items() )
			recipes.emplace( recipeJSON.value(), recipeJSON.key() );
		mRecipesMap.emplace( commodityRecipesJSON.key(), std::move( recipes ) );
	}
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating from the JSON object " << aJSON.dump() << "." )

void CRecipes::JSON( json& aJSON ) const noexcept
{
	for( const auto& [ key, recipes ] : mRecipesMap )
	{
		json& keyRecipesJSON = aJSON[ key ];
		for( const auto& recipe : recipes )
			AddToJSONKey( keyRecipesJSON, recipe, recipe.GetKey() );
	}
}

const CRecipes::recipes_map& CRecipes::GetRecipesMap() const noexcept
{
	return mRecipesMap;
}

} // ypp_sm namespace
