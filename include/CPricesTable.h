#pragma once

#include "AKeyable.h"
#include "IDescriptable.h"
#include "IJsonable.h"

#include "types/CPricesTable.h"
#include "traits/CPricesTable.h"

namespace ypp_sm
{

/**
 * @brief Class for a table of different prices for an item.
 */
class CPricesTable : public IJsonable, public IDescriptable, public AKeyable, protected json_traits<CPricesTable>
{
protected:
	using price = types::CPricesTable::price;
	using int_price = types::CPricesTable::int_price;

public:
	/**
	 * @brief Member constructor.
	 * @param aName Name of the prices table.
	 * @param aCost \copybrief mCost
	 * @param aUsePrice \copybrief mUsePrice
	 * @param aTax \copybrief mTax
	 */
	explicit CPricesTable( std::string_view aName, price aCost, int_price aUsePrice, price aTax = 0 );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 * @param aName Name of the item.
	 */
	explicit CPricesTable( const json& aJSON, std::string_view aName );

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
	//! Retrieves the \copybrief mCost
	price GetCost() const noexcept;

	//! Retrieves the \copybrief mUsePrice
	int_price GetUsePrice() const noexcept;

	//! Retrieves the \copybrief mTax
	price GetTax() const noexcept;

private:
	//! Average cost.
	price mCost;
	//! Use price.
	int_price mUsePrice;
	//! Tax.
	price mTax;
};

} // namespace ypp_sm
