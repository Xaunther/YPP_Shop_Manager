#include "ATest.h"

#include "CKeyItem.h"
#include "JsonUtils.h"

#include <set>

using namespace ypp_sm;

INITIALIZE_TEST( TKeyItem )

void TKeyItem::TestExceptions()
{
}

std::vector<std::string> TKeyItem::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& recipeItem : std::set{
		CKeyItem<unsigned int>{ "White paint", 3 },
		CKeyItem<unsigned int>{ "White paint", 4 },
		CKeyItem<unsigned int>{ "Red paint", 1 },
		CKeyItem<unsigned int>{ "Wood", 23 },
		ValueFromJSONKeyString<CKeyItem<unsigned int>>( R"( {
			"White paint": 2
		} )", "White paint", "White paint" ),
		ValueFromJSONKeyString<CKeyItem<unsigned int>>( R"( {
			"Yellow paint": 2
		} )", "Yellow paint", "Yellow paint" ),
		ValueFromJSONKeyString<CKeyItem<unsigned int>>( R"( {
			"Black paint": 1
		} )", "Black paint", "Black paint" ),
		} )
	{
		result.emplace_back( std::string{ recipeItem.GetKey() } + ":" );
		result.emplace_back( " Quantity: " + std::to_string( recipeItem.GetValue() ) );
		result.emplace_back( recipeItem.GetDescription() );
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, recipeItem, recipeItem.GetKey() );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TKeyItem::ExpectedResults() noexcept
{
	return {
		"Black paint:",
		" Quantity: 1",
		"Black paint: 1\n",
		"{\n"
		"	\"Black paint\": 1\n"
		"}",
		"Red paint:",
		" Quantity: 1",
		"Red paint: 1\n",
		"{\n"
		"	\"Red paint\": 1\n"
		"}",
		"White paint:",
		" Quantity: 3",
		"White paint: 3\n",
		"{\n"
		"	\"White paint\": 3\n"
		"}",
		"Wood:",
		" Quantity: 23",
		"Wood: 23\n",
		"{\n"
		"	\"Wood\": 23\n"
		"}",
		"Yellow paint:",
		" Quantity: 2",
		"Yellow paint: 2\n",
		"{\n"
		"	\"Yellow paint\": 2\n"
		"}",
	};
}
