#include "frontend/IMenuSelector.h"

#include <iostream>
#include <ranges>

#include "frontend/InputUtils.h"

namespace ypp_sm::frontend
{

void IMenuSelector::operator()( CDataBase& aDataBase, std::string_view aJSONFileName )
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
	} while( GetOperations()[ AskInput<unsigned int>( ">", DEFAULT_CONVERSION<unsigned int>, condition ) ]( aDataBase, aJSONFileName ) );
}

void IMenuSelector::PrintMenu()
{
	for( const auto& [ index, option ] : std::views::enumerate( GetOptions() ) )
		std::cout << index << ") " << option << ".\n";
}

} // namespace ypp_sm::frontend
