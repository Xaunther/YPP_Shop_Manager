#pragma once

#include <map>

#include "types/AKeyable.h"
#include "types/CPricesTable.h"

/**
 * @brief Types defined for \ref CProductPrice.
*/
namespace ypp_sm::types::CProductPrice
{

//! Aggregate for the prices for a recipe for a single ingredient combination.
struct product_price
{
	//! Price shown in the Order Commodities menu.
	types::CPricesTable::int_price order_price;
	//! Cost of a single item.
	types::CPricesTable::price cost;
};

//! Type for the prices of all ingredient combinations.
using product_price_set = std::map<AKeyable::key_type,product_price>;

} // ypp_sm::types::CProductPrice namespace
