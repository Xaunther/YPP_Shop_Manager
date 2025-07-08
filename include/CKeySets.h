#pragma once

#include "IJsonable.h"

#include "types/CKeySets.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

/**
 * @brief Class for some sets classified by keys.
 */
template <typename T>
class CKeySets : public IJsonable
{
protected:
	using key_sets = types::CKeySets::key_sets<T>;

public:
	/**
	 * @brief Member constructor.
	 * @param aKeySets \copybrief mKeySets
	 */
	explicit CKeySets( const key_sets& aKeySets );

	/**
	 * @brief JSON constructor.
	 * @param aJSON JSON object
	 */
	explicit CKeySets( const json& aJSON );

protected:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	void JSON( json& aJSON ) const noexcept override;

public:
	//! Retrieves the \copybrief mKeySets
	const key_sets& GetKeySets() const noexcept;

private:
	//! Sets classified by some key.
	key_sets mKeySets;
};

template <typename T>
CKeySets<T>::CKeySets( const key_sets& aKeySets ) try :
	mKeySets( aKeySets )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating key sets." )

template <typename T>
CKeySets<T>::CKeySets( const json& aJSON ) try
{
	for( const auto& keySetsJSON : aJSON.items() )
	{
		typename key_sets::mapped_type set;
		for( const auto& setJSON : keySetsJSON.value().items() )
			set.emplace( setJSON.value(), setJSON.key() );
		mKeySets.emplace( keySetsJSON.key(), std::move( set ) );
	}
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating from the JSON object " << aJSON.dump() << "." )

template <typename T>
void CKeySets<T>::JSON( json& aJSON ) const noexcept
{
	for( const auto& [ key, set ] : mKeySets )
	{
		json& keyRecipesJSON = aJSON[ key ];
		for( const auto& setElement : set )
			AddToJSONKey( keyRecipesJSON, setElement, setElement.GetKey() );
	}
}

template <typename T>
const CKeySets<T>::key_sets& CKeySets<T>::GetKeySets() const noexcept
{
	return mKeySets;
}

} // ypp_sm namespace
