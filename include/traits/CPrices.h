#pragma once

#include "traits/json.h"

#include <string_view>

namespace ypp_sm
{

class CPrices;

template <> struct json_traits<CPrices>
{
	//! JSON key for the class.
	static inline constexpr std::string_view KEY = "Prices";
};

} // ypp_sm namespace
