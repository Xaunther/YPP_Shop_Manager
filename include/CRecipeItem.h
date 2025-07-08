#pragma once

#include "AKeyable.h"
#include "IJsonable.h"

#include "types/CRecipeItem.h"

namespace ypp_sm
{

/**
 * @brief Class for a recipe item.
 */
class CRecipeItem : public IJsonable, public AKeyable
{
protected:
	using count = types::CRecipeItem::count;

public:
	/**
	 * @brief Member constructor.
	 * @param aName Name of the item.
	 * @param aCount \copybrief mCount
	 */
	explicit CRecipeItem( std::string_view aName, const count& aCount );

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

private:
	//! Quantity required.
	count mCount;
};

} // ypp_sm namespace
