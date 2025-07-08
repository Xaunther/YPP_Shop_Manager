#pragma once

#include "AKeyable.h"

#include <map>
#include <set>

/**
 * @brief Types defined for \ref CPrices.
*/
namespace ypp_sm
{

template <typename T> class CKeyItem;

namespace types::CPrices
{

//! Type for price.
using price = float;
//! Type for prices.
using prices = std::set<CKeyItem<price>>;
//! Type for prices classified by some key.
using prices_map = std::map<AKeyable::key_type, prices>;

} // types::CPrices namespace

} // ypp_sm namespace
