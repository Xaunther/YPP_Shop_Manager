#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "types/CRecipeItem.h"

#include <string_view>

namespace ypp_sm
{

class CRecipe;

template <> struct default_traits<CRecipe>
{
protected:
	using count = types::CRecipeItem::count;
public:
	//! Default \copybrief CRecipe::mYield
	static inline constexpr count DEFAULT_YIELD = 1;
};

template <> struct json_traits<CRecipe>
{
	//! JSON key for the \copybrief CRecipe::mYield
	static inline constexpr std::string_view YIELD_KEY = "Yield";
};

} // ypp_sm namespace
