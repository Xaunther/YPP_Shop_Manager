#include "frontend/CMainMenuSelector.h"

#include "CDataBase.h"

#include <iostream>
#include <fstream>

#include "frontend/InputUtils.h"

namespace ypp_sm::frontend
{

namespace
{

/**
 * @brief Adds price from user input.
 * @param aDataBase Database to add the price to.
 */
bool AddPrice( CDataBase& aDataBase, std::string_view );

/**
 * @brief Removes price from user input.
 * @param aDataBase Database to remove the price from.
 */
bool RemovePrice( CDataBase& aDataBase, std::string_view );

/**
 * @brief Modifies price from user input.
 * @param aDataBase Database to modify the price at.
 */
bool ModifyPrice( CDataBase& aDataBase, std::string_view );

} // anonymous namespace

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
		"Add price",
		"Remove price",
		"Modify price",
		"Save JSON"
	};
}

CMainMenuSelector::operations CMainMenuSelector::GetOperations() const noexcept
{
	return {
		[]( CDataBase&, std::string_view ){ return false; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetRecipes().GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetPrices().GetDescription(); return true; },
		AddPrice,
		RemovePrice,
		ModifyPrice,
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

namespace
{

bool AddPrice( CDataBase& aDataBase, std::string_view )
{
	auto setInput = AskInput<std::string>( "Set:" );
	auto itemInput = AskInput<std::string>( "Item:" );
	auto priceInput = AskInput<float>( "Price:" );
	aDataBase.AddPrice( setInput, itemInput, priceInput );
	return true;
}

bool RemovePrice( CDataBase& aDataBase, std::string_view )
{
	auto setInput = AskInput<std::string>( "Set:" );
	auto itemInput = AskInput<std::string>( "Item:" );
	aDataBase.RemovePrice( setInput, itemInput );
	return true;
}

bool ModifyPrice( CDataBase& aDataBase, std::string_view )
{
	auto setInput = AskInput<std::string>( "Set:" );
	auto itemInput = AskInput<std::string>( "Item:" );
	auto priceInput = AskInput<float>( "Price:" );
	aDataBase.ModifyPrice( setInput, itemInput, priceInput );
	return true;
}

} // anonymous namespace

} // namespace ypp_sm::frontend
