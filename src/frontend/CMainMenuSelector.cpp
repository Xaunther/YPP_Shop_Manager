#include "frontend/CMainMenuSelector.h"

#include "CDataBase.h"

#include <iostream>
#include <fstream>

namespace ypp_sm::frontend
{

namespace
{

template <is_jsonable T> bool Dump( const T& aObject, std::ostream& aStream )
{
	types::IJsonable::json JSON;
	aObject.ToJSON( JSON );
	aStream << JSON.dump( 1, '\t' ) << "\n";
	return true;
}

}

constexpr std::string_view CMainMenuSelector::GetIntro() const noexcept
{
	return "What do you want to do?";
}

constexpr std::vector<std::string_view> CMainMenuSelector::GetOptions() const noexcept
{
	return {
		"Quit",
		"List recipes",
		"List prices",
		"Save JSON"
	};
}

std::vector<std::function<bool( CDataBase&, std::string_view )>> CMainMenuSelector::GetOperations() const noexcept
{
	return {
		[]( CDataBase&, std::string_view ){ return false; },
		[]( CDataBase& aDataBase, std::string_view ){ return Dump( aDataBase.GetRecipes(), std::cout ); },
		[]( CDataBase& aDataBase, std::string_view ){ return Dump( aDataBase.GetPrices(), std::cout ); },
		[]( CDataBase& aDataBase, std::string_view aJSONFileName )
		{
			std::ofstream f( aJSONFileName.data() );
			return Dump( aDataBase, f );
		},
	};
}

} // namespace ypp_sm::frontend
