#include "CPricesTable.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
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

CPricesTable::CPricesTable( const json& aJSON ) try :
	CPricesTable( ValueFromRequiredJSONKey<price>( aJSON, COST_KEY ),
			ValueFromRequiredJSONKey<int_price>( aJSON, USE_PRICE_KEY ),
			ValueFromOptionalJSONKey<price>( aJSON, TAX_KEY ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a prices table from JSO from JSON." )

void CPricesTable::JSON( json& aJSON ) const noexcept
{
	AddToJSONKey( aJSON, mCost, COST_KEY );
	AddToJSONKey( aJSON, mUsePrice, USE_PRICE_KEY );
	AddToOptionalJSONKey( aJSON, mTax, TAX_KEY );
}

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
