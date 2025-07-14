#pragma once

#include "IDescriptable.h"
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
class CKeySets : public IJsonable, public IDescriptable
{
public:
	using value_type = T;
	using key_sets = types::CKeySets::key_sets<T>;

public:
	/**
	 * @brief Member constructor.
	 * @param aKeySets \copybrief mKeySets
	 */
	explicit CKeySets( const key_sets& aKeySets = {} );

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

private:
	/**
	 * @copydoc IJsonable::ToJSON
	 */
	std::string Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept override;

public:
	//! Retrieves the \copybrief mKeySets
	const key_sets& GetKeySets() const noexcept;

	//! Retrieves the \copybrief mKeySets
	key_sets& KeySets() noexcept;

	/**
	 * @brief Adds a new key.
	 * @param aKey Key to add.
	 * @return Whether the element could be added.
	 */
	bool AddKey( std::string_view aKey );

	/**
	 * @brief Removes a key.
	 * @param aKey Key to remove.
	 * @return Whether the element could be removed.
	 */
	bool RemoveKey( std::string_view aKey );

	/**
	 * @brief Retrieves the set associated to a key.
	 * @details If the key is not found, creates a new one.
	 * @param aKey Key to access.
	 */
	std::set<T> Set( std::string_view aKey );

	/**
	 * @brief Adds a new element.
	 * @param aSetName Set where the element should be added to.
	 * @param aElement Element to be added.
	 * @return Whether the element could be added.
	 */
	bool AddElement( std::string_view aSetName, const T& aElement );

	/**
	 * @brief Removes an element.
	 * @param aSetName Group where the element should be removed from.
	 * @param aElement Element to be removed.
	 * @return Whether the element could be removed.
	 */
	bool RemoveElement( std::string_view aSetName, const T& aElement );

	/**
	 * @brief Modifies an element.
	 * @param aSetName Group where the element to be modifies is.
	 * @param aElement Modified element.
	 * @return Whether the element could be modified.
	 */
	bool ModifyElement( std::string_view aSetName, const T& aElement );

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
		if( !set.empty() )
		{
			json& keyRecipesJSON = aJSON[ key ];
			for( const auto& setElement : set )
				AddToJSONKey( keyRecipesJSON, setElement, setElement.GetKey() );
		}
	}
}

template <typename T>
std::string CKeySets<T>::Description( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	std::stringstream ss;
	for( const auto& [ key, set ] : mKeySets )
	{
		ss << std::string( aIndentDepth, aIndentChar ) << key << ":\n";
		for( const auto& setElement : set )
			ss << setElement.GetDescription( aIndentDepth + 1, aIndentChar );
	}
	return ss.str();
}

template <typename T>
const CKeySets<T>::key_sets& CKeySets<T>::GetKeySets() const noexcept
{
	return mKeySets;
}

template <typename T>
CKeySets<T>::key_sets& CKeySets<T>::KeySets() noexcept
{
	return mKeySets;
}

template <typename T>
bool CKeySets<T>::AddKey( std::string_view aKey )
{
	return mKeySets.emplace( aKey ).second;
}

template <typename T>
bool CKeySets<T>::RemoveKey( std::string_view aKey )
{
	return mKeySets.erase( aKey ) > 0;
}

template <typename T>
std::set<T> CKeySets<T>::Set( std::string_view aKey )
{
	return mKeySets[ aKey ];
}

template <typename T>
bool CKeySets<T>::AddElement( std::string_view aSetName, const T& aElement )
{
	auto found = mKeySets.find( aSetName.data() );
	if( found == mKeySets.end() )
		return false;
	return (*found).second.emplace( aElement ).second;
}

template <typename T>
bool CKeySets<T>::RemoveElement( std::string_view aSetName, const T& aElement )
{
	auto found = mKeySets.find( aSetName.data() );
	if( found == mKeySets.end() )
		return false;
	return (*found).second.erase( aElement ) > 0;
}

template <typename T>
bool CKeySets<T>::ModifyElement( std::string_view aSetName, const T& aElement )
{
	auto found = mKeySets.find( aSetName.data() );
	if( found == mKeySets.end() )
		return false;

	auto& foundSet = (*found).second;
	foundSet.extract( aElement );
	return foundSet.emplace( aElement ).second;
}

} // ypp_sm namespace
