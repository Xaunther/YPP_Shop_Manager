#include "CDataBase.h"

namespace ypp_sm
{

const CDataBase::recipes& CDataBase::GetRecipes() const noexcept
{
	return mRecipes;
}
const CDataBase::prices& CDataBase::GetPrices() const noexcept
{
	return mPrices;
}

} // ypp_sm namespace
