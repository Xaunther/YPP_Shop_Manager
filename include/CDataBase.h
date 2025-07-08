#pragma once

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
class CDataBase : public IJsonable, protected json_traits<CDataBase>
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

public:
	//! Retrieves the \copybrief mRecipes
	const recipes& GetRecipes() const noexcept;
	//! Retrieves the \copybrief mPrices
	const prices& GetPrices() const noexcept;

private:
	//! List of recipes, classified by a keyword
	recipes mRecipes;
	//! List of prices, classified by a keyword
	prices mPrices;
};

} // ypp_sm namespace
