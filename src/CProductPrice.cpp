#include "CProductPrice.h"

#include <sstream>

namespace ypp_sm
{

CProductPrice::int_price CProductPrice::GetOrderPrice() const noexcept
{
	return mOrderPrice;
}

std::string CProductPrice::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	ss << std::string( aIndentDepth, aIndentChar ) << GetKey() << ":\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << "Order price: " << mOrderPrice << "\n";
	return ss.str();
}

} // namespace ypp_sm
