#include "frontend/CMainMenuSelector.h"

#include "CDataBase.h"
#include "CProductPrices.h"

#include <iostream>
#include <fstream>

#include "frontend/CKeySetsMenuSelector.h"

namespace ypp_sm::frontend
{

template <> inline CRecipe AskInput( std::string_view aMessage )
{
	auto itemInput = AskInput<std::string>( aMessage );
	auto yieldInput = AskInput<unsigned int>( "Yield:" );
	auto doubloonInput = AskInput<unsigned int>( "Doubloons:" );
	auto ingredientsCountInput = AskInput<unsigned int>( "Number of ingredients:" );
	types::CRecipe::items ingredientsInput;
	while( ingredientsInput.size() < ingredientsCountInput )
	{
		auto ingredientInput = AskInput<types::AKeyable::key_type>( "Ingredient " + std::to_string( ingredientsInput.size() + 1 ) + ":" );
		auto countInput = AskInput<types::CRecipe::count>( ingredientInput + " units:" );
		ingredientsInput.emplace( ingredientInput, countInput );
	}
	return CRecipe{ itemInput, ingredientsInput, doubloonInput, yieldInput };
}

template <> inline CPricesTable AskInput( std::string_view aMessage )
{
	auto itemInput = AskInput<std::string>( aMessage );
	auto costInput = AskInput<types::CPricesTable::price>( "Cost:" );
	auto usePriceInput = AskInput<types::CPricesTable::int_price>( "Use price:" );
	auto taxInput = AskInput<types::CPricesTable::price>( "Tax:" );
	return CPricesTable{ itemInput, costInput, usePriceInput, taxInput };
}

constexpr std::string CMainMenuSelector::GetIntro() const noexcept
{
	return "What do you want to do?";
}

constexpr std::vector<std::string> CMainMenuSelector::GetOptions() const noexcept
{
	return {
		"Quit",
		"Calculate costs",
		"Calculate costs for a category",
		"List database",
		"Explore recipes",
		"Explore prices",
		"Modify doubloon price",
		"Save JSON"
	};
}

CMainMenuSelector::operations CMainMenuSelector::GetOperations() const noexcept
{
	return {
		[]( const CDataBase&, std::string_view ){ return false; },
		[]( const CDataBase& aDataBase, std::string_view )
		{
			try
			{
				std::cout << CProductPrices{ aDataBase }.GetDescription();
			}
			catch( const std::invalid_argument& )
			{
			}
			return true;
		},
		[]( const CDataBase& aDataBase, std::string_view )
		{
			try
			{
				std::cout << CProductPrices{ aDataBase, AskInput<types::AKeyable::key_type>( "Category:" ) }.GetDescription();
			}
			catch( const std::invalid_argument& )
			{
			}
			return true;
		},
		[]( const CDataBase& aDataBase, std::string_view ){ std::cout << aDataBase.GetDescription(); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ CKeySetsMenuSelector<CRecipe>{}( aDataBase.Recipes() ); return true; },
		[]( CDataBase& aDataBase, std::string_view ){ CKeySetsMenuSelector<CPricesTable>{}( aDataBase.Prices() ); return true; },
		[]( CDataBase& aDataBase, std::string_view )
		{
			aDataBase.SetDoubloonPrice( AskInput<types::CPricesTable::int_price>(
					std::string{ json_traits<CDataBase>::DOUBLOON_PRICE_KEY } + ":" ) );
			return true;
		},
		[]( const CDataBase& aDataBase, std::string_view aJSONFileName )
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
