#pragma once

#include "AKeyable.h"

#include <set>

/**
 * @brief Types defined for \ref CRecipe.
*/
namespace ypp_sm
{

class CRecipeItem;

namespace types::CRecipe
{

//! Type for a set of recipe items.
using items = std::set<ypp_sm::CRecipeItem>;

} // types::CRecipe namespace

} // ypp_sm namespace
