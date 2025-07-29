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
	 * @brief Constructor to calculate all the product prices from a database.
	 * @param aDataBase Database.
	 */
	explicit CProductPrices( const CDataBase& aDataBase );

	/**
	 * @brief Constructor to calculate the product prices of one key in a database.
	 * @param aDataBase Database with other recipes and ingredient prices.
	 * @param aKey Name of the key to use.
	 */
	explicit CProductPrices( const CDataBase& aDataBase, std::string_view aKey );

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

