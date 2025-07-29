#include "CProductPrices.h"

#include "CDataBase.h"

namespace ypp_sm
{

CProductPrices::CProductPrices( const CDataBase& aDataBase ) try
{
	for( const auto& [ key, recipes ] : aDataBase.GetRecipes().GetKeySets() )
	{
		product_prices::value_type::second_type productPrices;
		for( const auto& recipe : recipes )
			productPrices.emplace( recipe, aDataBase );
		mPrices.emplace( key, std::move( productPrices ) );
	}
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the product prices." )

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
