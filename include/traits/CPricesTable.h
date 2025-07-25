#pragma once

#include "traits/json.h"

#include <string_view>

namespace ypp_sm
{

class CPricesTable;

template <> struct json_traits<CPricesTable>
{
	//! JSON key for the \copybrief CPricesTable::mCost
	static inline constexpr std::string_view COST_KEY = "Cost";
	//! JSON key for the \copybrief CPricesTable::mUsePrice
	static inline constexpr std::string_view USE_PRICE_KEY = "Use price";
	//! JSON key for the \copybrief CPricesTable::mTax
	static inline constexpr std::string_view TAX_KEY = "Tax";
};

} // ypp_sm namespace

