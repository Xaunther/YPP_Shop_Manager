#pragma once

#include "traits/json.h"

#include <string_view>

namespace ypp_sm
{

class CRecipeItem;

template <> struct json_traits<CRecipeItem>
{
	//! JSON key for the \copybrief CRecipeItem::mCount
	static inline constexpr std::string_view COUNT_KEY = "Quantity";
	//! JSON key for the \copybrief CRecipeItem::mPrice
	static inline constexpr std::string_view PRICE_KEY = "Price";
};

} // ypp_sm namespace
