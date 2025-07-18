#pragma once

#include <set>

#include "types/AKeyable.h"

/**
 * @brief Types defined for \ref CRecipe.
*/
namespace ypp_sm
{

template <typename T> class CKeyItem;

namespace types::CRecipe
{

//! Type for a number of items.
using count = unsigned int;
//! Type for a set of recipe items.
using items = std::set<ypp_sm::CKeyItem<count>,AKeyable::SKeyCompare>;

} // types::CRecipe namespace

} // ypp_sm namespace
