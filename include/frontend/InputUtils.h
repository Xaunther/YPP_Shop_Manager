#pragma once

#include <functional>
#include <iostream>
#include <set>
#include <string>
#include "type_traits"

namespace ypp_sm::frontend
{

template <typename T> using conversion_function = std::function<T( const std::string& )>;
template <typename T> using condition_function = std::function<bool( const std::string& )>;

//! Concept to check that the type is a std::vector.
template <typename T> concept is_vector = std::same_as<std::remove_cvref_t<T>,
		 std::vector<typename T::value_type, typename T::allocator_type>>;
//! Concept to check that the type is a std::set.
template <typename T> concept is_set = std::same_as<std::remove_cvref_t<T>,
		 std::set<typename T::value_type, typename T::key_compare, typename T::allocator_type>>;

//! Concept to check that the type is a container type.
template <typename T> concept is_container = is_vector<T> || is_set<T>;
template <typename T> concept is_not_container = !is_container<T>;

template <typename T> T DEFAULT_CONVERSION( const std::string& aInput );
template <> unsigned int DEFAULT_CONVERSION( const std::string& aInput );
template <> float DEFAULT_CONVERSION( const std::string& aInput );

template <typename T> bool DEFAULT_CONDITION( const std::string& aInput );

/**
 * @brief Asks user for an input.
 * @details Uses default condition and conversion.
 * @param aMessage Message before user input.
 */
template <is_not_container T> T AskInput( std::string_view aMessage );
template <is_container T> T AskInput( std::string_view aMessage );

/**
 * @brief Asks user for an input.
 * @details It keeps asking until an input satisfying the condition given is passed.
 * @param aMessage Message before user input.
 * @param aConvert Conversion from the input string to the input type.
 * @param aCondition Condition that the input must pass.
 */
template <typename T>
T AskInput( std::string_view aMessage, const conversion_function<T>& aConvert, const condition_function<T>& aCondition );

template <typename T> T DEFAULT_CONVERSION( const std::string& aInput )
{
	return T{ aInput };
}

template <typename T> bool DEFAULT_CONDITION( const std::string& aInput )
{
	try
	{
		DEFAULT_CONVERSION<T>( aInput );
	}
	catch( const std::invalid_argument& )
	{
		return false;
	}
	return true;
}

template <is_not_container T> T AskInput( std::string_view aMessage )
{
	return AskInput<T>( aMessage, DEFAULT_CONVERSION<T>, DEFAULT_CONDITION<T> );
}

template <is_container T> T AskInput( std::string_view aMessage )
{
	T result;
	while( AskInput<std::string>( "Add " + std::string{ aMessage } + "? y/[n]:" ) == "y" )
	{
		auto input = AskInput<typename T::value_type>(
				std::string{ aMessage } + " " + std::to_string( result.size() + 1 ) + ":" );
		if constexpr( is_vector<T> )
			result.emplace_back( std::move( input ) );
		else
			result.emplace( std::move( input ) );
	}
	return result;
}

template <typename T>
T AskInput( std::string_view aMessage, const conversion_function<T>& aConvert, const condition_function<T>& aCondition )
{
	std::string result;
	do
	{
		std::cout << aMessage << " ";
		std::getline( std::cin, result );
	} while( !aCondition( result ) );
	return aConvert( result );
}

} // ypp_sm::frontend namespace
