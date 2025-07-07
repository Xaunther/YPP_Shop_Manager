#pragma once

#include "traits/json.h"

#include <string_view>

namespace ypp_sm
{

class CRecipes;

template <> struct json_traits<CRecipes>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Recipes";
};

} // ypp_sm namespace
