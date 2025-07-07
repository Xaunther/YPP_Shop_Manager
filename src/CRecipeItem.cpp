#include "CRecipeItem.h"

#include "NumberUtils.h"

namespace ypp_sm
{

CRecipeItem::CRecipeItem( std::string_view aName, const count& aCount, const float& aPrice ) :
	AKeyable( aName ),
	mCount( aCount ),
	mPrice( CheckNonNegativeness( aPrice, "price of each item" ) )
{
}

const CRecipeItem::count& CRecipeItem::GetCount() const noexcept
{
	return mCount;
}

const float& CRecipeItem::GetPrice() const noexcept
{
	return mPrice;
}

} // ypp_sm namespace
