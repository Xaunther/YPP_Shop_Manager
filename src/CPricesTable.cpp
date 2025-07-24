#include "CPricesTable.h"

#include "ExceptionUtils.h"
#include "NumberUtils.h"

namespace ypp_sm
{

CPricesTable::CPricesTable( price aCost, int_price aUsePrice, price aTax ) try :
	mCost( CheckNonNegativeness( aCost, "average cost" ) ),
	mUsePrice( aUsePrice ),
	mTax( CheckNonNegativeness( aTax, "tax" ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a prices table." )

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
