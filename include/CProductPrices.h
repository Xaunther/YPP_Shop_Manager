#pragma once

#include "IDescriptable.h"

#include "CKeySets.h"
#include "CProductPrice.h"

namespace ypp_sm
{

/**
 * @brief Class for the product prices.
 */
class CProductPrices : public IDescriptable
{
protected:
	using product_prices = types::CKeySets::key_sets<CProductPrice>;
};

} // ypp_sm namespace

