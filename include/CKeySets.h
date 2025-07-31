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

	/*
	 * @brief Returns if the given item is present in any of the sets.
	 * @detauls The item must be comparable to the items in the sets.
	 * @param aItem item to find.
	 */
	template <typename U> bool Contains( const U& aItem ) const;
private:
	//! Sets classified by some key.
	key_sets mKeySets;
};

namespace detail
{

template <typename T>
CKeySets<T>::key_sets CreateKeySets( const types::IJsonable::json& aJSON );

template <typename T>
const CKeySets<T>::key_sets& CheckUniqueness( const typename CKeySets<T>::key_sets& aKeySets );

} // detail namespace

template <typename T>
CKeySets<T>::CKeySets( const key_sets& aKeySets ) try :
	mKeySets( detail::CheckUniqueness<T>( aKeySets ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating key sets." )

template <typename T>
CKeySets<T>::CKeySets( const json& aJSON ) try :
	mKeySets( detail::CheckUniqueness<T>( detail::CreateKeySets<T>( aJSON ) ) )
{
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
template <typename U> bool CKeySets<T>::Contains( const U& aItem ) const
{
	for( const auto& [ key, set ] : mKeySets )
		if( set.contains( aItem ) )
			return true;
	return false;
}

namespace detail
{

template <typename T>
CKeySets<T>::key_sets CreateKeySets( const types::IJsonable::json& aJSON )
{
	typename CKeySets<T>::key_sets result;
	for( const auto& keySetsJSON : aJSON.items() )
	{
		typename CKeySets<T>::key_sets::mapped_type set;
		for( const auto& setJSON : keySetsJSON.value().items() )
			set.emplace( setJSON.value(), setJSON.key() );
		result.emplace( keySetsJSON.key(), std::move( set ) );
	}
	return result;
}

template <typename T>
const CKeySets<T>::key_sets& CheckUniqueness( const typename CKeySets<T>::key_sets& aKeySets )
{
	std::set<T> repeatedItems;
	for( auto it1 = aKeySets.cbegin(); it1 != aKeySets.cend(); ++it1 )
	{
		for( auto it2 = aKeySets.cbegin(); it2 != it1; ++it2 )
			std::ranges::set_intersection( (*it1).second, (*it2).second, std::inserter( repeatedItems, repeatedItems.end() ) );

	}
	if( !repeatedItems.empty() )
	{
		auto itemIt = repeatedItems.cbegin();
		std::stringstream ss;
		ss << "The following items are repeated: " << (*itemIt).GetKey();
		for( ++itemIt; itemIt != repeatedItems.cend(); ++itemIt )
			ss << ", " << (*itemIt).GetKey();
		ss << ".";
		throw( std::invalid_argument{ ss.str() } );
	}
	return aKeySets;
}

} // detail namespace

} // ypp_sm namespace
