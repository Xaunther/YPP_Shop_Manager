#pragma once

#include "AKeyable.h"
#include "IJsonable.h"

#include "CRecipeItem.h"

#include "types/CRecipe.h"

namespace ypp_sm
{

/**
 * @brief Class for a recipe.
 */
class CRecipe : public IJsonable, public AKeyable
{
protected:
	using items = types::CRecipe::items;

public:
	/**
	 * @brief Member constructor.
	 * @param aName Name of the recipe.
	 * @param aItems \copybrief mItems
	 */
	explicit CRecipe( std::string_view aName, const items& aItems );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 * @param aName Name of the item.
	 */
	explicit CRecipe( const json& aJSON, std::string_view aName );

	//! Retrieves the \copybrief mItems
	const items& GetItems() const noexcept;

private:
	//! Items needed for the recipe.
	items mItems;
};

} // ypp_sm namespace
