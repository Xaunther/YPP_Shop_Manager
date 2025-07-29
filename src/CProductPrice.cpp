#include "CProductPrice.h"

namespace ypp_sm
{

CProductPrice::int_price CProductPrice::GetOrderPrice() const noexcept
{
	return mOrderPrice;
}

} // namespace ypp_sm
