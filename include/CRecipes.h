#pragma once

#include "IJsonable.h"

#include "traits/CRecipes.h"
#include "types/CRecipes.h"

namespace ypp_sm
{

/**
 * @brief Class for the recipes.
 * @details The recipes are classified by shop the shop producing the item.
 */
class CRecipes : public IJsonable, protected json_traits<CRecipes>
{
protected:
	using shop_recipes = types::CRecipes::shop_recipes;

public:
	//! Retrieves the \copybrief mShopRecipes
	const shop_recipes& GetShopRecipes() const noexcept;

private:
	//! Recipes map classified by commodity type.
	shop_recipes mShopRecipes;
};

} // ypp_sm namespace
