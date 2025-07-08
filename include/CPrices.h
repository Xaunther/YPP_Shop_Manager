#pragma once

#include "IJsonable.h"

#include "CKeyItem.h"

#include "traits/CPrices.h"
#include "types/CPrices.h"

namespace ypp_sm
{

/**
 * @brief Class for the prices.
 * @details The prices are classified by some key.
 */
class CPrices : public IJsonable, protected json_traits<CPrices>
{
protected:
	using prices_map = types::CPrices::prices_map;

public:
	/**
	 * @brief Member constructor.
	 * @param aPricesMap \copybrief mPricesMap
	 */
	explicit CPrices( const prices_map& aPricesMap );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 */
	explicit CPrices( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mPricesMap
	const prices_map& GetPricesMap() const noexcept;

private:
	//! Prices map classified by some key.
	prices_map mPricesMap;
};

} // ypp_sm namespace
