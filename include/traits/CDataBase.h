#pragma once

#include "traits/json.h"

#include <string_view>

namespace ypp_sm
{

class CDataBase;

template <> struct json_traits<CDataBase>
{
	//! JSON key for the \copybrief CDataBase::mRecipes
	static inline constexpr std::string_view RECIPES_KEY = "Recipes";
	//! JSON key for the \copybrief CDataBase::mPrices
	static inline constexpr std::string_view PRICES_KEY = "Prices";
};

} // ypp_sm namespace
