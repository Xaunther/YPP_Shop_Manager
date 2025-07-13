#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace ypp_sm::frontend
{

template <typename T> using conversion_function = std::function<T( const std::string& )>;
template <typename T> using condition_function = std::function<bool( const std::string& )>;

template <typename T> T DEFAULT_CONVERSION( const std::string& aInput );
template <> unsigned int DEFAULT_CONVERSION( const std::string& aInput );
template <> float DEFAULT_CONVERSION( const std::string& aInput );

template <typename T> bool DEFAULT_CONDITION( const std::string& aInput );

/**
 * @brief Asks user for an input.
 * @details It keeps asking until an input satisfying the condition given is passed.
 * @param aMessage Message before user input.
 * @param aConvert Conversion from the input string to the input type.
 * @param aCondition Condition that the input must pass.
 */
template <typename T>
T AskInput( std::string_view aMessage,
		const conversion_function<T>& aConvert = DEFAULT_CONVERSION<T>,
		const condition_function<T>& aCondition = DEFAULT_CONDITION<T> );

template <typename T> T DEFAULT_CONVERSION( const std::string& aInput )
{
	return aInput;
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
