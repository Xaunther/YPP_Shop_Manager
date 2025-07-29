#pragma once

#include "AKeyable.h"
#include "IDescriptable.h"

#include "types/CPricesTable.h"

namespace ypp_sm
{

/**
 * @brief Class for a product price.
 */
class CProductPrice : public IDescriptable, public AKeyable
{
protected:
	using int_price = types::CPricesTable::int_price;

public:
	//! Retrieves the \copybrief mOrderPrice
	int_price GetOrderPrice() const noexcept;

private:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	std::string Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept override;

	//! Price shown in the Order Commodities menu.
	int_price mOrderPrice;
};

} // ypp_sm namespace
