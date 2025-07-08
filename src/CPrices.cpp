#include "CPrices.h"

namespace ypp_sm
{

const CPrices::prices_map& CPrices::GetPricesMap() const noexcept
{
	return mPricesMap;
}

} // ypp_sm namespace
