#include "CPricesTable.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"
#include "NumberUtils.h"

namespace ypp_sm
{

CPricesTable::CPricesTable( std::string_view aName, optional_price aCost, int_price aUsePrice, price aTax ) try :
	AKeyable( aName ),
	mCost( aCost.transform( []( const auto& aCost ){ return CheckNonNegativeness( aCost, "average cost" ); } ) ),
	mUsePrice( aUsePrice ),
	mTax( CheckNonNegativeness( aTax, "tax" ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating '" << aName << "' prices table." )

CPricesTable::CPricesTable( const json& aJSON, std::string_view aName ) try :
	CPricesTable( aName, ValueFromOptionalJSONKey<optional_price>( aJSON, COST_KEY ),
			ValueFromRequiredJSONKey<int_price>( aJSON, USE_PRICE_KEY ),
			ValueFromOptionalJSONKey<price>( aJSON, TAX_KEY ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating '" << aName << "' prices table from JSON." )

void CPricesTable::JSON( json& aJSON ) const noexcept
{
	if( mCost )
		AddToJSONKey( aJSON, *mCost, COST_KEY );
	AddToJSONKey( aJSON, mUsePrice, USE_PRICE_KEY );
	AddToOptionalJSONKey( aJSON, mTax, TAX_KEY );
}

std::string CPricesTable::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	ss << std::string( aIndentDepth, aIndentChar ) << GetKey() << ":\n";
	if( mCost )
		ss << std::string( aIndentDepth + 1, aIndentChar ) << COST_KEY << ": " << *mCost << "\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << USE_PRICE_KEY << ": " << mUsePrice << "\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << TAX_KEY << ": " << mTax << "\n";
	return ss.str();
}

CPricesTable::optional_price CPricesTable::GetCost() const noexcept
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
