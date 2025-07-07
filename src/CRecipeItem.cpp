#include "CRecipeItem.h"

namespace ypp_sm
{

const CRecipeItem::count& CRecipeItem::GetCount() const noexcept
{
	return mCount;
}

const float& CRecipeItem::GetPrice() const noexcept
{
	return mPrice;
}

} // ypp_sm namespace
