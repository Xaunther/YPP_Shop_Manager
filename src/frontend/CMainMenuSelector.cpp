#include "frontend/CMainMenuSelector.h"

#include "CDataBase.h"

#include <iostream>
#include <fstream>

#include "frontend/CKeySetsMenuSelector.h"

namespace ypp_sm::frontend
{

template <> inline CRecipe AskInput( std::string_view aMessage,
		const conversion_function<CRecipe>&,
		const condition_function<CRecipe>& )
{
	auto itemInput = AskInput<std::string>( aMessage );
	auto yieldInput = AskInput<unsigned int>( "Yield:" );
	auto ingredientsCountInput = AskInput<unsigned int>( "Number of ingredients:" );
	types::CRecipe::items ingredientsInput;
	while( ingredientsInput.size() < ingredientsCountInput )
	{
		auto ingredientInput = AskInput<types::AKeyable::key_type>( "Ingredient " + std::to_string( ingredientsInput.size() + 1 ) + ":" );
		auto countInput = AskInput<types::CRecipe::count>( ingredientInput + " units:" );
		ingredientsInput.emplace( ingredientInput, countInput );
	}
	return CRecipe{ itemInput, ingredientsInput, yieldInput };
}

template <> inline CKeyItem<types::CDataBase::price> AskInput( std::string_view aMessage,
		const conversion_function<CKeyItem<types::CDataBase::price>>&,
		const condition_function<CKeyItem<types::CDataBase::price>>& )
{
	auto itemInput = AskInput<std::string>( aMessage );
	auto priceInput = AskInput<float>( "Price:" );
	return CKeyItem<types::CDataBase::price>{ itemInput, priceInput };
}

constexpr std::string CMainMenuSelector::GetIntro() const noexcept
{
	return "What do you want to do?";
}

constexpr std::vector<std::string> CMainMenuSelector::GetOptions() const noexcept
{
	return {
		"Quit",
		"List database",
		"Explore recipes",
		"Explore prices",
		"Save JSON"
	};
}

CMainMenuSelector::operations CMainMenuSelector::GetOperations() const noexcept
{
	return {
		[]( CDataBase&, std::string_view ){ return false; },
		[]( CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ CKeySetsMenuSelector<CRecipe>{}( aDataBase.Recipes() ); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ CKeySetsMenuSelector<CKeyItem<types::CDataBase::price>>{}( aDataBase.Prices() ); return true; },
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
