#pragma once

#include "traits/json.h"

#include <string_view>

namespace ypp_sm
{

class CRecipes;

template <> struct json_traits<CRecipes>
{
};

} // ypp_sm namespace
