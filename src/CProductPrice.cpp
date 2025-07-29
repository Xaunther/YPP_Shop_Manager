#include "CProductPrice.h"

#include "CDataBase.h"
#include "CRecipe.h"

#include <sstream>

#include "ExceptionUtils.h"

namespace ypp_sm
{

namespace
{

/*
 * @brief Find the prices table of an item.
 * @details Raises an exception if the item is not found.
 * @param aItem Item to find.
 * @param aPrices Prices to look for the item price.
 */
const CPricesTable& GetPricesTable( const types::CRecipe::items::value_type& aItem, const types::CDataBase::prices& aPrices );

/*
 * @brief Calculates the order price of a recipe.
 * @param aRecipe Recipe to calculate its price.
 * @param aDataBase Database to look for ingredients prices.
 */
types::CPricesTable::int_price CalculateOrderPrice( const CRecipe& aRecipe, const CDataBase& aDatabase );

} // anonymous namespace

CProductPrice::CProductPrice( const CRecipe& aRecipe, const CDataBase& aDataBase ) try :
	AKeyable( aRecipe.GetKey() ),
	mOrderPrice( CalculateOrderPrice( aRecipe, aDataBase ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating " << aRecipe.GetKey() << " product price." )

CProductPrice::int_price CProductPrice::GetOrderPrice() const noexcept
{
	return mOrderPrice;
}

CProductPrice::price CProductPrice::GetCost() const noexcept
{
	return mCost;
}

std::string CProductPrice::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	ss << std::string( aIndentDepth, aIndentChar ) << GetKey() << ":\n";
	ss << std::string( aIndentDepth + 1, aIndentChar ) << "Order price: " << mOrderPrice << "\n";
	return ss.str();
}

namespace
{

const CPricesTable& GetPricesTable( const types::CRecipe::items::value_type& aItem, const types::CDataBase::prices& aPrices )
{
	for( const auto& [ key, pricesTables ] : aPrices.GetKeySets() )
	{
		const auto found = pricesTables.find( types::AKeyable::key_type{ aItem.GetKey() } );
		if( found != pricesTables.cend() )
			return *found;
	}
	throw std::invalid_argument{ std::string{ aItem.GetKey() } + " price table not found." };
}

types::CPricesTable::int_price CalculateOrderPrice( const CRecipe& aRecipe, const CDataBase& aDatabase )
{
	using price = types::CPricesTable::price;
	price result = 0;

	for( const auto& ingredient : aRecipe.GetItems() )
	{
		const auto& priceTable = GetPricesTable( ingredient, aDatabase.GetPrices() );
		result += ( priceTable.GetTax() + static_cast<price>( priceTable.GetUsePrice() ) )
				* static_cast<price>( ingredient.GetValue() );
	}

	return static_cast<types::CPricesTable::int_price>( result );
}

} // anonymous namespace

} // namespace ypp_sm
