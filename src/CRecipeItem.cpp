#include "CRecipeItem.h"

#include "ExceptionUtils.h"
#include "NumberUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

CRecipeItem::CRecipeItem( std::string_view aName, const count& aCount, const float& aPrice ) :
	AKeyable( aName ),
	mCount( aCount ),
	mPrice( CheckNonNegativeness( aPrice, "price of each item" ) )
{
}

CRecipeItem::CRecipeItem( const json& aJSON, std::string_view aName ) try :
	CRecipeItem( aName, ValueFromRequiredJSONKey<count>( aJSON, COUNT_KEY ),
			ValueFromRequiredJSONKey<float>( aJSON, PRICE_KEY ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe item from JSON " << aJSON.dump() )

const CRecipeItem::count& CRecipeItem::GetCount() const noexcept
{
	return mCount;
}

const float& CRecipeItem::GetPrice() const noexcept
{
	return mPrice;
}

} // ypp_sm namespace
