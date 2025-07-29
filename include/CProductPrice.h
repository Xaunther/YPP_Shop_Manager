#pragma once

#include "AKeyable.h"
#include "IDescriptable.h"

#include "types/CPricesTable.h"

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
	using int_price = types::CPricesTable::int_price;

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
	//! Retrieves the \copybrief mOrderPrice
	int_price GetOrderPrice() const noexcept;

private:
	//! Price shown in the Order Commodities menu.
	int_price mOrderPrice;
};

} // ypp_sm namespace
