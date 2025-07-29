#pragma once

#include "IDescriptable.h"
#include "IJsonable.h"

#include "CKeySets.h"
#include "CPricesTable.h"
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
	using recipes = types::CDataBase::recipes;
	using prices = types::CDataBase::prices;
	using int_price = types::CPricesTable::int_price;

public:
	/**
	 * @brief Member constructor.
	 * @param aRecipes \copybrief mRecipes
	 * @param aPrices \copybrief mPrices
	 * @param aDoubloonPrice \copybrief mDoubloonPrice
	 */
	explicit CDataBase( const recipes& aRecipes, const prices& aPrices, const int_price& aDoubloonPrice );

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
	//! Retrieves the \copybrief mRecipes
	recipes& Recipes() noexcept;
	//! Retrieves the \copybrief mPrices
	const prices& GetPrices() const noexcept;
	//! Retrieves the \copybrief mPrices
	prices& Prices() noexcept;

	//! Retrieves the \copybrief mDoubloonPrice
	int_price GetDoubloonPrice() const noexcept;

private:
	//! List of recipes, classified by a keyword
	recipes mRecipes;
	//! List of prices, classified by a keyword
	prices mPrices;
	//! Doubloon exchange price.
	int_price mDoubloonPrice;
};

} // ypp_sm namespace
