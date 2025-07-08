#pragma once

/**
 * @brief Types defined for \ref CDataBase.
*/
namespace ypp_sm
{

template <typename T> class CKeyItem;
template <typename T> class CKeySets;
class CRecipe;

namespace types::CDataBase
{

//! Type for the price
using price = float;
//! Type for the recipes sets.
using recipes = ypp_sm::CKeySets<ypp_sm::CRecipe>;
//! Type for the prices sets.
using prices = ypp_sm::CKeySets<ypp_sm::CKeyItem<price>>;

} // ypp_sm namespace

} // types::CDataBase namespace
