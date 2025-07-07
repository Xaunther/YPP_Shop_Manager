#pragma once

#include "AKeyable.h"

#include "types/CRecipeItem.h"

namespace ypp_sm
{

/**
 * @brief Class for a recipe item.
 */
class CRecipeItem : public AKeyable
{
protected:
	using count = types::CRecipeItem::count;

public:
	//! Retrieves the \copybrief mCount
	const count& GetCount() const noexcept;

	//! Retrieves the \copybrief mPrice
	const float& GetPrice() const noexcept;

private:
	//! Quantity required.
	count mCount;
	//! Price of each unit.
	float mPrice;
};

} // ypp_sm namespace
