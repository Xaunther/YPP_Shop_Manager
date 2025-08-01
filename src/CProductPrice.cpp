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

class SIngredientIteratorVector
{
	using ingredient_iterator_vector = std::vector<types::CRecipe::ingredients_type::const_iterator>;

public:
	/*
	 * @brief Constructs the ingredient iterator vector.
	 * @param aRecipe Recipe to iterate through ingredients.
	 * @post The size coincides with the number of items in the recipe.
	 */
	explicit SIngredientIteratorVector( const CRecipe& aRecipe ) noexcept;

	/*
	 * @brief Increments the iterators to the next combination.
	 * @param aRecipe Recipe to iterate through ingredients.
	 * @return If there is another combination.
	 * @pre Same recipe used in constructor.
	 */
	bool Increment( const CRecipe& aRecipe );

	/**
	 * @brief Obtain the key corresponding to the ingredient combination.
	 * @param aRecipe Recipe to iterate through ingredients.
	 * @pre Same recipe used in constructor.
	 */
	types::AKeyable::key_type GetKey( const CRecipe& aRecipe ) const;

	/**
	 * @brief Obtain the ingredient variant used for the item of index aIndex.
	 * @param aIndex Index of the item.
	 */
	const types::AKeyable::key_type& operator[]( std::size_t aIndex ) const;

private:
	ingredient_iterator_vector mIterators;
};

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
 * @brief Calculates the set of prices of a recipe.
 * @param aRecipe Recipe to calculate its prices.
 * @param aDataBase Database to look for ingredients prices.
 */
types::CProductPrice::product_price_set CalculateProductPriceSet( const CRecipe& aRecipe, const CDataBase& aDataBase );

/*
 * @brief Calculates the order price of a recipe.
 * @param aRecipe Recipe to calculate its price.
 * @param aDataBase Database to look for ingredients prices.
 * @param aIngredientIterators Iterators selecting an ingredient combination.
 */
types::CPricesTable::int_price CalculateOrderPrice( const CRecipe& aRecipe, const CDataBase& aDataBase,
		const SIngredientIteratorVector& aIngredientIterators );

/*
 * @brief Calculates the cost of a recipe.
 * @details It tries to find a recipe for each ingredient, if not found, defaults to its cost price.
 * @param aRecipe Recipe to calculate its cost.
 * @param aDataBase Database to look for ingredients cost.
 * @param aIngredientIterators Iterators selecting an ingredient combination.
 */
types::CPricesTable::price CalculateCost( const CRecipe& aRecipe, const CDataBase& aDataBase,
		const SIngredientIteratorVector& aIngredientIterators );

} // anonymous namespace

CProductPrice::CProductPrice( const CRecipe& aRecipe, const CDataBase& aDataBase ) try :
	AKeyable( aRecipe.GetKey() ),
	mProductPriceSet( CalculateProductPriceSet( aRecipe, aDataBase ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating " << aRecipe.GetKey() << " product price." )

const CProductPrice::product_price_set& CProductPrice::GetProductPriceSet() const noexcept
{
	return mProductPriceSet;
}

std::string CProductPrice::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	for( const auto& [ key, productPrice ] : mProductPriceSet )
	{
		ss << std::string( aIndentDepth, aIndentChar ) << std::string{ GetKey() } + key << ":\n";
		ss << std::string( aIndentDepth + 1, aIndentChar ) << "Order price: " << productPrice.order_price << "\n";
		ss << std::string( aIndentDepth + 1, aIndentChar ) << "Unit cost: " << productPrice.cost << "\n";
	}
	return ss.str();
}

namespace
{

SIngredientIteratorVector::SIngredientIteratorVector( const CRecipe& aRecipe ) noexcept
{
	for( const auto& item : aRecipe.GetItems() )
		mIterators.emplace_back( item.ingredients.cbegin() );
}

bool SIngredientIteratorVector::Increment( const CRecipe& aRecipe )
{
	bool carry = true;
	for( const auto& [ index, item ] : std::views::enumerate( aRecipe.GetItems() ) )
	{
		auto& it = mIterators[ index ];
		if( carry )
		{
			++it;
			carry = false;
		}
		if( it == item.ingredients.cend() )
		{
			it = item.ingredients.cbegin();
			carry = true;
		}
	}
	return !carry;
}

types::AKeyable::key_type SIngredientIteratorVector::GetKey( const CRecipe& aRecipe ) const
{
	types::AKeyable::key_type result;

	for( const auto& [ index, item ] : std::views::enumerate( aRecipe.GetItems() ) )
	{
		if( item.ingredients.size() > 1 )
		{
			if( result.empty() )
				result += " (";
			else
				result += ", ";
			result += *mIterators[ index ];
		}
	}
	if( !result.empty() )
		result += ")";

	return result;
}

const types::AKeyable::key_type& SIngredientIteratorVector::operator[]( std::size_t aIndex ) const
{
	return *mIterators[ aIndex ];
}

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

types::CProductPrice::product_price_set CalculateProductPriceSet( const CRecipe& aRecipe, const CDataBase& aDataBase )
{
	types::CProductPrice::product_price_set result;

	SIngredientIteratorVector ingredientIts{ aRecipe };
	do
	{
		result.emplace( ingredientIts.GetKey( aRecipe ), types::CProductPrice::product_price{
				.order_price = CalculateOrderPrice( aRecipe, aDataBase, ingredientIts ),
				.cost = CalculateCost( aRecipe, aDataBase, ingredientIts ) } );
	} while( ingredientIts.Increment( aRecipe ) );
	return result;
}

types::CPricesTable::int_price CalculateOrderPrice( const CRecipe& aRecipe, const CDataBase& aDataBase,
		const SIngredientIteratorVector& aIngredientIterators )
{
	using price = types::CPricesTable::price;
	price result = 0;

	for( const auto& [ index, ingredient ] : std::views::enumerate( aRecipe.GetItems() ) )
	{
		const auto& priceTable = GetPricesTable( aIngredientIterators[ index ], aDataBase.GetPrices() );
		result += ( priceTable.GetTax() + static_cast<price>( priceTable.GetUsePrice() ) )
				* static_cast<price>( ingredient.ingredient_count );
	}

	return static_cast<types::CPricesTable::int_price>( result );
}

// NOLINTNEXTLINE(misc-no-recursion)
types::CPricesTable::price CalculateCost( const CRecipe& aRecipe, const CDataBase& aDataBase,
		const SIngredientIteratorVector& aIngredientIterators )
{
	using price = types::CPricesTable::price;
	price result = 0;

	for( const auto& [ index, ingredient ] : std::views::enumerate( aRecipe.GetItems() ) )
	{
		if( const auto recipe = GetRecipe( aIngredientIterators[ index ], aDataBase.GetRecipes() ) )
			result += CalculateCost( *recipe, aDataBase, SIngredientIteratorVector{ *recipe } )
					* static_cast<price>( (*recipe).get().GetYield() );
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
