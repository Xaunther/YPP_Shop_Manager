#pragma once

#include "AKeyable.h"
#include "IJsonable.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

/**
 * @brief Class for a price item.
 */
template <typename T>
class CKeyItem : public IJsonable, public AKeyable
{
public:
	/**
	 * @brief Member constructor.
	 * @param aName Name of the item.
	 * @param aValue \copybrief mValue
	 */
	explicit CKeyItem( std::string_view aName, const T& aValue );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 * @param aName Name of the item.
	 */
	explicit CKeyItem( const json& aJSON, std::string_view aName );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mValue
	const T& GetValue() const noexcept;

private:
	//! Value of the item
	T mValue;
};

template <typename T>
CKeyItem<T>::CKeyItem( std::string_view aName, const T& aValue ) try :
	AKeyable( aName ),
	mValue( aValue )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating key item." )

template <typename T>
CKeyItem<T>::CKeyItem( const json& aJSON, std::string_view aName ) try :
	CKeyItem( aName, ValueFromJSON<T>( aJSON ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating key item from JSON " << aJSON.dump() )

template <typename T>
void CKeyItem<T>::JSON( json& aJSON ) const noexcept
{
	AddToJSON( aJSON, mValue );
}

template <typename T>
const T& CKeyItem<T>::GetValue() const noexcept
{
	return mValue;
}

} // ypp_sm namespace
