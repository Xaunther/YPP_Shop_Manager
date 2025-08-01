#pragma once

#include "AKeyable.h"
#include "IDescriptable.h"

#include "types/CProductPrice.h"

namespace ypp_sm
{

class CDataBase;
class CRecipe;

/**
 * @brief Class for a product price.
 */
class CProductPrice : public IDescriptable, public AKeyable
{
protected:
	using product_price_set = types::CProductPrice::product_price_set;

public:
	/**
	 * @brief Constructor to calculate the product price from its recipe and a database.
	 * @param aRecipe Recipe of the product.
	 * @param aDataBase Database with other recipes and ingredient prices.
	 */
	explicit CProductPrice( const CRecipe& aRecipe, const CDataBase& aDataBase );

private:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	std::string Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept override;

public:
	//! Retrieves the \copybrief mProductPriceSet
	const product_price_set& GetProductPriceSet() const noexcept;

private:
	//! Prices of all ingredient combinations.
	product_price_set mProductPriceSet;
};

} // ypp_sm namespace
