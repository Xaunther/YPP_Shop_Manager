#pragma once

#include "IJsonable.h"

#include "traits/CPrices.h"
#include "types/CPrices.h"

namespace ypp_sm
{

/**
 * @brief Class for the prices.
 * @details The prices are classified by some key.
 */
class CPrices : public IJsonable, protected json_traits<CPrices>
{
};

} // ypp_sm namespace
