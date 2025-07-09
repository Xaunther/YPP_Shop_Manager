#include "frontend/IMenuSelector.h"

#include <iostream>
#include <limits>
#include <ranges>

namespace ypp_sm::frontend
{

void IMenuSelector::operator()( CDataBase& aDataBase, std::string_view aJSONFileName )
{
	do
	{
		PrintMenu();
	} while( GetOperations()[ HandleInput() ]( aDataBase, aJSONFileName ) );
}

void IMenuSelector::PrintMenu()
{
	std::cout << GetIntro() << ":\n";
	for( const auto& [ index, option ] : std::views::enumerate( GetOptions() ) )
		std::cout << index << ") " << option << ".\n";
}

unsigned int IMenuSelector::HandleInput()
{
	unsigned int result = 0;
	while( true )
	{
		std::cout << "> ";
		std::cin >> result;
		if( std::cin.fail() || result > GetOptions().size() )
		{
			std::cin.clear();
			std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
			continue;
		}
		break;
	}
	return result;
}

} // namespace ypp_sm::frontend
