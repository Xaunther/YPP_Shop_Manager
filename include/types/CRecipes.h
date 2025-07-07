#pragma once

#include "AKeyable.h"

#include <map>
#include <set>

/**
 * @brief Types defined for \ref CRecipes.
*/
namespace ypp_sm
{

class CRecipeItem;

namespace types::CRecipes
{

//! Type for a set of recipe items
using recipe_items = std::set<ypp_sm::CRecipeItem>;
//! Type for recipes.
using recipes = std::map<AKeyable::key_type, recipe_items>;
//! Type for recipes classified by shop.
using shop_recipes = std::map<AKeyable::key_type, recipes>;

} // types::CRecipes namespace

} // ypp_sm namespace
