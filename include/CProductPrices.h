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
	/**
	 * @brief Constructor to calculate the product price from its recipe and a database.
	 * @param aDataBase Database with other recipes and ingredient prices.
	 */
	explicit CProductPrices( const CDataBase& aDataBase );

private:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	std::string Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept override;

public:
	//! Retrieves the \copybrief mPrices
	product_prices GetPrices() const noexcept;

private:
	//! Sets of product prices
	product_prices mPrices;
};

} // ypp_sm namespace

