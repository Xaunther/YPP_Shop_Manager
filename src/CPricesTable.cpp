#include "CPricesTable.h"

namespace ypp_sm
{

CPricesTable::price CPricesTable::GetCost() const noexcept
{
	return mCost;
}

CPricesTable::int_price CPricesTable::GetUsePrice() const noexcept
{
	return mUsePrice;
}

CPricesTable::price CPricesTable::GetTax() const noexcept
{
	return mTax;
}

} // namespace ypp_sm
