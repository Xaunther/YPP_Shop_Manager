#pragma once

#include <set>
#include <vector>

#include "types/AKeyable.h"

/**
 * @brief Types defined for \ref CRecipe.
*/
namespace ypp_sm::types::CRecipe
{

//! Type for a set of ingredients.
using ingredients_type = std::set<AKeyable::key_type>;
//! Type for a number of items.
using count = unsigned int;

//! Type for a recipe item.
struct item
{
	ingredients_type ingredients;
	count ingredient_count;
};

//! Type for the items of a recipe.
using items = std::vector<item>;

} // ypp_sm::types::CRecipe namespace
