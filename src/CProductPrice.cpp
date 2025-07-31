#include "CProductPrice.h"

#include "CDataBase.h"
#include "CRecipe.h"

#include <optional>
#include <sstream>

#include "ExceptionUtils.h"

namespace ypp_sm
{

namespace
{

using optional_recipe = std::optional<std::reference_wrapper<const CRecipe>>;

/*
 * @brief Find the prices table of an item.
 * @details Raises an exception if the item is not found.
 * @param aItem Item to find.
 * @param aPrices Prices to look for the item price.
 */
const CPricesTable& GetPricesTable( const types::CRecipe::ingredients_type::value_type& aItem, const types::CDataBase::prices& aPrices );

/*
 * @brief Find the prices table of an item.
 * @details Returns an empty optional if the recipe is not found.
 * @param aItem Item to find.
 * @param aRecipes Recipes to look for the item recipe.
 */
optional_recipe GetRecipe( const types::CRecipe::ingredients_type::value_type& aItem, const types::CDataBase::recipes& aRecipes );

/*
 * @brief Calculates the order price of a recipe.
 * @param aRecipe Recipe to calculate its price.
 * @param aDataBase Database to look for ingredients prices.
 */
types::CPricesTable::int_price CalculateOrderPrice( const CRecipe& aRecipe, const CDataBase& aDataBase );

/*
 * @brief Calculates the cost of a recipe.
 * @details It tries to find a recipe for each ingredient, if not found, defaults to its cost price.
 * @param aRecipe Recipe to calculate its cost.
 * @param aDataBase Database to look for ingredients cost.
 */
types::CPricesTable::price CalculateCost( const CRecipe& aRecipe, const CDataBase& aDataBase );

} // anonymous namespace

CProductPrice::CProductPrice( const CRecipe& aRecipe, const CDataBase& aDataBase ) try :
	AKeyable( aRecipe.GetKey() ),
	mOrderPrice( CalculateOrderPrice( aRecipe, aDataBase ) ),
	mCost( CalculateCost( aRecipe, aDataBase ) )
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
	ss << std::string( aIndentDepth + 1, aIndentChar ) << "Unit cost: " << mCost << "\n";
	return ss.str();
}

namespace
{

const CPricesTable& GetPricesTable( const types::CRecipe::ingredients_type::value_type& aItem, const types::CDataBase::prices& aPrices )
{
	for( const auto& [ key, pricesTables ] : aPrices.GetKeySets() )
	{
		const auto found = pricesTables.find( aItem );
		if( found != pricesTables.cend() )
			return *found;
	}
	throw std::invalid_argument{ aItem + " price table not found." };
}

optional_recipe GetRecipe( const types::CRecipe::ingredients_type::value_type& aItem, const types::CDataBase::recipes& aRecipes )
{
	for( const auto& [ key, recipes ] : aRecipes.GetKeySets() )
	{
		const auto found = recipes.find( types::AKeyable::key_type{ aItem } );
		if( found != recipes.cend() )
			return *found;
	}
	return {};
}

types::CPricesTable::int_price CalculateOrderPrice( const CRecipe& aRecipe, const CDataBase& aDataBase )
{
	using price = types::CPricesTable::price;
	price result = 0;

	for( const auto& ingredient : aRecipe.GetItems() )
	{
		const auto& priceTable = GetPricesTable( *ingredient.ingredients.cbegin(), aDataBase.GetPrices() );
		result += ( priceTable.GetTax() + static_cast<price>( priceTable.GetUsePrice() ) )
				* static_cast<price>( ingredient.ingredient_count );
	}

	return static_cast<types::CPricesTable::int_price>( result );
}

// NOLINTNEXTLINE(misc-no-recursion)
types::CPricesTable::price CalculateCost( const CRecipe& aRecipe, const CDataBase& aDataBase )
{
	using price = types::CPricesTable::price;
	price result = 0;

	for( const auto& ingredient : aRecipe.GetItems() )
	{
		if( const auto recipe = GetRecipe( *ingredient.ingredients.cbegin(), aDataBase.GetRecipes() ) )
			result += CalculateCost( *recipe, aDataBase ) * static_cast<price>( (*recipe).get().GetYield() );
		else
		{
			const auto& priceTable = GetPricesTable( *ingredient.ingredients.cbegin(), aDataBase.GetPrices() );
			result += ( priceTable.GetTax() + priceTable.GetCost() ) * static_cast<price>( ingredient.ingredient_count );
		}
	}
	result += static_cast<price>( aRecipe.GetDoubloonCount() * aDataBase.GetDoubloonPrice() );
	result /= static_cast<price>( aRecipe.GetYield() );

	return result;
}

} // anonymous namespace

} // namespace ypp_sm
