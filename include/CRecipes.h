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
};

} // ypp_sm namespace
