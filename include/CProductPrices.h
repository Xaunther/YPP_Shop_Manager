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

public:
	//! Retrieves the \copybrief mPrices
	product_prices GetPrices() const noexcept;

private:
	//! Sets of product prices
	product_prices mPrices;
};

} // ypp_sm namespace

