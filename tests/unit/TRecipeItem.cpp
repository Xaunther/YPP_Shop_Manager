#include "ATest.h"

#include "CRecipeItem.h"
#include "JsonUtils.h"

#include <set>

using namespace ypp_sm;

INITIALIZE_TEST( TRecipeItem )

void TRecipeItem::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CRecipeItem{ "", 12, -1 };
	}, "The price of each item cannot be negative." );

	// Test JSON constructor
	CheckException( []()
	{
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Wood": {
				"Price": -1
			}
		} )", "Wood", "Wood" );
	}, "key 'Quantity' not found" );

	CheckException( []()
	{
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Wood": {
				"Quantity": 12
			}
		} )", "Wood", "Wood" );
	}, "key 'Price' not found" );

	CheckException( []()
	{
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Wood": {
				"Quantity": 12,
				"Price": -1
			}
		} )", "Wood", "Wood" );
	}, "The price of each item cannot be negative." );
}

std::vector<std::string> TRecipeItem::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& recipeItem : std::set{
		CRecipeItem{ "White paint", 3, 25 },
		CRecipeItem{ "White paint", 4, 25 },
		CRecipeItem{ "Red paint", 1, 12.6 },
		CRecipeItem{ "Wood", 23, 13 },
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"White paint": {
				"Quantity": 2,
				"Price": 155.6
			}
		} )", "White paint", "White paint" ),
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Yellow paint": {
				"Quantity": 2,
				"Price": 300
			}
		} )", "Yellow paint", "Yellow paint" ),
		ValueFromJSONKeyString<CRecipeItem>( R"( {
			"Black paint": {
				"Quantity": 1,
				"Price": 2500.67
			}
		} )", "Black paint", "Black paint" ),
		} )
	{
		result.emplace_back( std::string{ recipeItem.GetKey() } + ":" );
		result.emplace_back( " Quantity: " + std::to_string( recipeItem.GetCount() ) );
		result.emplace_back( " Price: " + std::to_string( recipeItem.GetPrice() ) );
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
		" Price: 2500.669922",
		"{\n"
		"	\"Black paint\": {\n"
		"		\"Quantity\": 1,\n"
		"		\"Price\": 2500.669921875\n"
		"	}\n"
		"}",
		"Red paint:",
		" Quantity: 1",
		" Price: 12.600000",
		"{\n"
		"	\"Red paint\": {\n"
		"		\"Quantity\": 1,\n"
		"		\"Price\": 12.600000381469727\n"
		"	}\n"
		"}",
		"White paint:",
		" Quantity: 3",
		" Price: 25.000000",
		"{\n"
		"	\"White paint\": {\n"
		"		\"Quantity\": 3,\n"
		"		\"Price\": 25.0\n"
		"	}\n"
		"}",
		"Wood:",
		" Quantity: 23",
		" Price: 13.000000",
		"{\n"
		"	\"Wood\": {\n"
		"		\"Quantity\": 23,\n"
		"		\"Price\": 13.0\n"
		"	}\n"
		"}",
		"Yellow paint:",
		" Quantity: 2",
		" Price: 300.000000",
		"{\n"
		"	\"Yellow paint\": {\n"
		"		\"Quantity\": 2,\n"
		"		\"Price\": 300.0\n"
		"	}\n"
		"}",
	};
}
