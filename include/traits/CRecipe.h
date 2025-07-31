#pragma once

#include "traits/default.h"
#include "traits/json.h"

#include "types/CRecipe.h"

#include <string_view>

namespace ypp_sm
{

class CRecipe;

template <> struct default_traits<CRecipe>
{
protected:
	using count = types::CRecipe::count;
public:
	//! Default \copybrief CRecipe::mYield
	static inline constexpr count DEFAULT_YIELD = 1;
};

template <> struct json_traits<CRecipe>
{
	//! JSON key for the \copybrief CRecipe::mYield
	static inline constexpr std::string_view YIELD_KEY = "Yield";
	//! JSON key for the \copybrief CRecipe::mDoubloonCount
	static inline constexpr std::string_view DOUBLOONS_KEY = "Doubloons";
	//! JSON key for the \copybrief CRecipe::mItems
	static inline constexpr std::string_view INGREDIENTS_KEY = "Ingredients";
	//! JSON key for an ingredient.
	static inline constexpr std::string_view INGREDIENT_KEY = "Ingredient";
	//! JSON key for an ingredient count
	static inline constexpr std::string_view COUNT_KEY = "Count";
};

} // ypp_sm namespace
