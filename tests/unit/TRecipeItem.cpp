#include "ATest.h"

#include "CRecipeItem.h"
#include "JsonUtils.h"

#include <set>

using namespace ypp_sm;

INITIALIZE_TEST( TRecipeItem )

void TRecipeItem::TestExceptions()
{
}

std::vector<std::string> TRecipeItem::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& recipeItem : std::set{
		CRecipeItem{ "White paint", 3 },
		CRecipeItem{ "White paint", 4 },
		CRecipeItem{ "Red paint", 1 },
		CRecipeItem{ "Wood", 23 },
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"White paint": 2
		} )", "White paint", "White paint" ),
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Yellow paint": 2
		} )", "Yellow paint", "Yellow paint" ),
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Black paint": 1
		} )", "Black paint", "Black paint" ),
		} )
	{
		result.emplace_back( std::string{ recipeItem.GetKey() } + ":" );
		result.emplace_back( " Quantity: " + std::to_string( recipeItem.GetCount() ) );
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, recipeItem, recipeItem.GetKey() );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TRecipeItem::ExpectedResults() noexcept
{
	return {
		"Black paint:",
		" Quantity: 1",
		"{\n"
		"	\"Black paint\": 1\n"
		"}",
		"Red paint:",
		" Quantity: 1",
		"{\n"
		"	\"Red paint\": 1\n"
		"}",
		"White paint:",
		" Quantity: 3",
		"{\n"
		"	\"White paint\": 3\n"
		"}",
		"Wood:",
		" Quantity: 23",
		"{\n"
		"	\"Wood\": 23\n"
		"}",
		"Yellow paint:",
		" Quantity: 2",
		"{\n"
		"	\"Yellow paint\": 2\n"
		"}",
	};
}
