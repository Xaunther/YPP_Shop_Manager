#pragma once

#include "IDescriptable.h"
#include "IJsonable.h"

#include "types/CPricesTable.h"

namespace ypp_sm
{

/**
 * @brief Class for a table of different prices for an item.
 */
class CPricesTable : public IJsonable, public IDescriptable
{
protected:
	using price = types::CPricesTable::price;
	using int_price = types::CPricesTable::int_price;

public:
	/**
	 * @brief Member constructor.
	 * @param aCost \copybrief mCost
	 * @param aUsePrice \copybrief mUsePrice
	 * @param aTax \copybrief mTax
	 */
	explicit CPricesTable( price aCost, int_price aUsePrice, price aTax = 0 );

	//! Retrieves the \copybrief mCost
	price GetCost() const noexcept;

	//! Retrieves the \copybrief mUsePrice
	int_price GetUsePrice() const noexcept;

	//! Retrieves the \copybrief mTax
	price GetTax() const noexcept;

private:
	//! Average cost.
	price mCost;
	//! Use price.
	int_price mUsePrice;
	//! Tax.
	price mTax;
};

} // namespace ypp_sm
