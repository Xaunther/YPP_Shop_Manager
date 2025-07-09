#pragma once

#include <functional>
#include <ranges>
#include <string_view>
#include <vector>

#include "InputUtils.h"

namespace ypp_sm
{

class CDataBase;

namespace frontend
{

/**
 * @brief Interface class for a menu.
 * @tparam Args Arguments for the operation.
 */
template< typename... Args >
class IMenuSelector
{
protected:
	using operation = std::function<bool( Args... )>;
	using operations = std::vector<operation>;

public:
	//! Virtual destructor.
	virtual ~IMenuSelector() = default;

public:
	/**
	 * @brief Runs the menu.
	 * @param aArgs Arguments required.
	 */
	void operator()( Args&&... aArgs ) const;

private:
	//! Prints the menu.
	void PrintMenu() const;

	//! Gets the operation to be done.
	operation GetOperation() const;

	//! Retrieves the introductory text.
	virtual constexpr std::string_view GetIntro() const noexcept = 0;

	//! Retrieves the posible options.
	virtual constexpr std::vector<std::string_view> GetOptions() const noexcept = 0;

	/**
	 * @brief Retrieves the posible operations.
	 * @details The operation returns whether the menu keeps going or not.
	 */
	virtual operations GetOperations() const noexcept = 0;
};

template< typename... Args >
void IMenuSelector<Args...>::operator()( Args&&... aArgs ) const
{
	const auto condition = [&]( const auto& aInput ) {
		try
		{
			return std::stoul( aInput ) < GetOptions().size();
		}
		catch( const std::invalid_argument& )
		{
			return false;
		}
	};
	do
	{
		PrintMenu();
	} while( GetOperations()[ AskInput<unsigned int>( ">", DEFAULT_CONVERSION<unsigned int>, condition ) ]
			( std::forward<decltype( aArgs )>( aArgs )... ) );
}

template< typename... Args >
void IMenuSelector<Args...>::PrintMenu() const
{
	for( const auto& [ index, option ] : std::views::enumerate( GetOptions() ) )
		std::cout << index << ") " << option << ".\n";
}

} // namespace frontend

} // namespace ypp_sm
