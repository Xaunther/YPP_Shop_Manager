#pragma once

#include <set>

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
using items = std::set<ypp_sm::CKeyItem<count>>;

} // types::CRecipe namespace

} // ypp_sm namespace
