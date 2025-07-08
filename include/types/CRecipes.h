#pragma once

#include "AKeyable.h"

#include <map>
#include <set>

/**
 * @brief Types defined for \ref CRecipes.
*/
namespace ypp_sm
{

class CRecipe;
class CRecipeItem;

namespace types::CRecipes
{

//! Type for recipes.
using recipes = std::set<ypp_sm::CRecipe>;
//! Type for recipes classified by some key.
using recipes_map = std::map<AKeyable::key_type, recipes>;

} // types::CRecipes namespace

} // ypp_sm namespace
