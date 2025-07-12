#include "frontend/CMainMenuSelector.h"

#include "CDataBase.h"

#include <iostream>
#include <fstream>

#include "frontend/InputUtils.h"

namespace ypp_sm::frontend
{

namespace
{

//! Creates a recipe from user input
CRecipe CreateRecipeFromInput();

/**
 * @brief Adds recipe from user input.
 * @param aDataBase Database to add the recipe to.
 */
bool AddRecipe( CDataBase& aDataBase, std::string_view );

/**
 * @brief Removes recipe from user input.
 * @param aDataBase Database to remove the recipe from.
 */
bool RemoveRecipe( CDataBase& aDataBase, std::string_view );

/**
 * @brief Modifies recipe from user input.
 * @param aDataBase Database to modify the recipe at.
 */
bool ModifyRecipe( CDataBase& aDataBase, std::string_view );

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

constexpr std::string CMainMenuSelector::GetIntro() const noexcept
{
	return "What do you want to do?";
}

constexpr std::vector<std::string> CMainMenuSelector::GetOptions() const noexcept
{
	return {
		"Quit",
		"List everything",
		"List recipes",
		"List prices",
		"Add recipe",
		"Remove recipe",
		"Modify recipe",
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
		AddRecipe,
		RemoveRecipe,
		ModifyRecipe,
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

CRecipe CreateRecipeFromInput()
{
	auto itemInput = AskInput<std::string>( "Item:" );
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

bool AddRecipe( CDataBase& aDataBase, std::string_view )
{
	auto setInput = AskInput<std::string>( "Set:" );
	aDataBase.AddRecipe( setInput, CreateRecipeFromInput() );
	return true;
}

bool RemoveRecipe( CDataBase& aDataBase, std::string_view )
{
	auto setInput = AskInput<std::string>( "Set:" );
	auto itemInput = AskInput<std::string>( "Item:" );
	aDataBase.RemoveRecipe( setInput, itemInput );
	return true;
}

bool ModifyRecipe( CDataBase& aDataBase, std::string_view )
{
	auto setInput = AskInput<std::string>( "Set:" );
	aDataBase.ModifyRecipe( setInput, CreateRecipeFromInput() );
	return true;
}

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
