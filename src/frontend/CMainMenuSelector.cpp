#include "frontend/CMainMenuSelector.h"

#include "CDataBase.h"

#include <iostream>
#include <fstream>

namespace ypp_sm::frontend
{

constexpr std::string_view CMainMenuSelector::GetIntro() const noexcept
{
	return "What do you want to do?";
}

constexpr std::vector<std::string_view> CMainMenuSelector::GetOptions() const noexcept
{
	return {
		"Quit",
		"List everything",
		"List recipes",
		"List prices",
		"Save JSON"
	};
}

std::vector<std::function<bool( CDataBase&, std::string_view )>> CMainMenuSelector::GetOperations() const noexcept
{
	return {
		[]( CDataBase&, std::string_view ){ return false; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetRecipes().GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetPrices().GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view aJSONFileName )
		{
			std::ofstream f( aJSONFileName.data() );
			types::IJsonable::json JSON;
			aDataBase.ToJSON( JSON );
			f << JSON.dump( 1, '\t' ) << "\n";
			return true;
		},
	};
}

} // namespace ypp_sm::frontend
