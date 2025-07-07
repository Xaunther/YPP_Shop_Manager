#pragma once

#include "AKeyable.h"
#include "IJsonable.h"

#include "traits/CRecipeItem.h"
#include "types/CRecipeItem.h"

namespace ypp_sm
{

/**
 * @brief Class for a recipe item.
 */
class CRecipeItem : public IJsonable, public AKeyable, protected json_traits<CRecipeItem>
{
protected:
	using count = types::CRecipeItem::count;

public:
	/**
	 * @brief Member constructor.
	 * @param aName Name of the item.
	 * @param aCount \copybrief mCount
	 * @param aPrice \copybrief mPrice
	 */
	explicit CRecipeItem( std::string_view aName, const count& aCount, const float& aPrice );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 * @param aName Name of the item.
	 */
	explicit CRecipeItem( const json& aJSON, std::string_view aName );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	void JSON( json& aJSON ) const noexcept override;

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
