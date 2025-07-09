#pragma once

#include "IDescriptable.h"
#include "IJsonable.h"

#include "CKeyItem.h"
#include "CKeySets.h"
#include "CRecipe.h"

#include "traits/CDataBase.h"
#include "types/CDataBase.h"

namespace ypp_sm
{

/**
 * @brief Class for a database.
 */
class CDataBase : public IJsonable, public IDescriptable, protected json_traits<CDataBase>
{
protected:
	using price = types::CDataBase::price;
	using recipes = types::CDataBase::recipes;
	using prices = types::CDataBase::prices;

public:
	/**
	 * @brief Member constructor.
	 * @param aRecipes \copybrief mRecipes
	 * @param aPrices \copybrief mPrices
	 */
	explicit CDataBase( const recipes& aRecipes, const prices& aPrices );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 */
	explicit CDataBase( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	void JSON( json& aJSON ) const noexcept override;

private:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	std::string Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept override;

public:
	//! Retrieves the \copybrief mRecipes
	const recipes& GetRecipes() const noexcept;
	//! Retrieves the \copybrief mPrices
	const prices& GetPrices() const noexcept;

	/**
	 * @brief Adds a new recipe.
	 * @param aSetName Group where the recipe should be added.
	 * @param aRecipe Recipe to be added.
	 * @return Whether the recipe could be added.
	 */
	bool AddRecipe( std::string_view aSetName, const CRecipe& aRecipe );

	/**
	 * @brief Removes a recipe.
	 * @param aSetName Group where the recipe should be removed from.
	 * @param aItemName Name of the recipe.
	 * @return Whether the recipe could be removed.
	 */
	bool RemoveRecipe( std::string_view aSetName, std::string_view aItemName );

	/**
	 * @brief Modifies a recipe.
	 * @param aSetName Group where the recipe to be modified is.
	 * @param aRecipe Recipe to be added.
	 * @return Whether the recipe could be modified.
	 */
	bool ModifyRecipe( std::string_view aSetName, const CRecipe& aRecipe );

	/**
	 * @brief Adds a new price.
	 * @param aSetName Group where the price should be added.
	 * @param aItemName Name of the item.
	 * @param aPrice Price of the item.
	 * @return Whether the price could be added.
	 */
	bool AddPrice( std::string_view aSetName, std::string_view aItemName, price aPrice );

	/**
	 * @brief Removes a price.
	 * @param aSetName Group where the price should be removed from.
	 * @param aItemName Name of the item.
	 * @return Whether the price could be removed.
	 */
	bool RemovePrice( std::string_view aSetName, std::string_view aItemName );

	/**
	 * @brief Modifies a price.
	 * @param aSetName Group where the price to be modified is.
	 * @param aItemName Name of the item which price will be modified.
	 * @param aPrice New price for the item.
	 * @return Whether the price could be modified.
	 */
	bool ModifyPrice( std::string_view aSetName, std::string_view aItemName, price aPrice );

private:
	//! List of recipes, classified by a keyword
	recipes mRecipes;
	//! List of prices, classified by a keyword
	prices mPrices;
};

} // ypp_sm namespace
