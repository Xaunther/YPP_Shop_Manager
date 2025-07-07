#include "CRecipe.h"

namespace ypp_sm
{

const CRecipe::items& CRecipe::GetItems() const noexcept
{
	return mItems;
}

} // ypp_sm namespace
