#pragma once

#include "IJsonable.h"

#include "CRecipeItem.h"

#include "traits/CRecipes.h"
#include "types/CRecipes.h"

namespace ypp_sm
{

/**
 * @brief Class for the recipes.
 * @details The recipes are classified by shop the shop producing the item.
 */
class CRecipes : public IJsonable, protected json_traits<CRecipes>
{
protected:
	using recipes_map = types::CRecipes::recipes_map;

public:
	/**
	 * @brief Member constructor.
	 * @param aRecipesMap \copybrief mRecipesMap
	 */
	explicit CRecipes( const recipes_map& aRecipesMap );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 */
	explicit CRecipes( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mRecipesMap
	const recipes_map& GetRecipesMap() const noexcept;

private:
	//! Recipes map classified by commodity type.
	recipes_map mRecipesMap;
};

} // ypp_sm namespace
