#include "CProductPrices.h"

namespace ypp_sm
{

std::string CProductPrices::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	if( !mPrices.empty() )
	{
		ss << std::string( aIndentDepth, aIndentChar ) << "Product prices:\n";
		for( const auto& [ key, productPrices ] : mPrices )
		{
			ss << std::string( aIndentDepth + 1, aIndentChar ) << key << ":\n";
			for( const auto& productPrice : productPrices )
				ss << productPrice.GetDescription( aIndentDepth + 2, aIndentChar );
		}
	}
	return ss.str();
}

CProductPrices::product_prices CProductPrices::GetPrices() const noexcept
{
	return mPrices;
}

} // namespace ypp_sm
