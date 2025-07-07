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
	//! Retrieves the \copybrief mItems
	const items& GetItems() const noexcept;

private:
	//! Items needed for the recipe.
	items mItems;
};

} // ypp_sm namespace
