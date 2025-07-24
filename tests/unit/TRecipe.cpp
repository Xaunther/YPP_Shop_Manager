#include "ATest.h"

#include "CRecipe.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TRecipe )

void TRecipe::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CRecipe{ "Grog", {}, 0, 0 };
	}, "The recipe yield must be positive" );

	// Test JSON constructor
	CheckException( []()
	{
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Grog": {
				"Yield": 0
			}
		} )", "Grog", "Grog" );
	}, "The recipe yield must be positive" );
}

std::vector<std::string> TRecipe::ObtainedResults() noexcept
{
	using recipe_item = types::CRecipe::items::value_type;
	std::vector<std::string> result;

	for( const auto& recipe : {
		CRecipe{ "Small cannon balls",
		{
			recipe_item{ "Iron", 5 },
			recipe_item{ "Wood", 1 },
			recipe_item{ "Basic labour", 3 },
		}, 0, 10 },
		CRecipe{ "Medium cannon balls",
		{
			recipe_item{ "Iron", 8 },
			recipe_item{ "Wood", 3 },
			recipe_item{ "Basic labour", 3 },
			recipe_item{ "Skilled labour", 2 },
		}, 0, 10 },
		CRecipe{ "Large cannon balls",
		{
			recipe_item{ "Iron", 12 },
			recipe_item{ "Wood", 4 },
			recipe_item{ "Basic labour", 2 },
			recipe_item{ "Skilled labour", 5 },
		} },
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Small cannon balls": {
				"Yield": 10,
				"Ingredients": {
					"Basic labour": 3,
					"Iron": 5,
					"Wood": 1
				}
			}
		} )", "Small cannon balls", "Small cannon balls" ),
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Medium cannon balls": {
				"Yield": 10,
				"Ingredients": {
					"Basic labour": 3,
					"Iron": 8,
					"Skilled labour": 2,
					"Wood": 3
				}
			}
		} )", "Medium cannon balls", "Medium cannon balls" ),
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Large cannon balls": {
				"Ingredients": {
					"Basic labour": 2,
					"Iron": 12,
					"Skilled labour": 5,
					"Wood": 4
				}
			}
		} )", "Large cannon balls", "Large cannon balls" ),
	} )
	{
		result.emplace_back( recipe.GetDescription() );
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, recipe, recipe.GetKey() );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TRecipe::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Small cannon balls:\n"
		" Yield: 10\n"
		" Ingredients:\n"
		"  Basic labour: 3\n"
		"  Iron: 5\n"
		"  Wood: 1\n",
		"{\n"
		"	\"Small cannon balls\": {\n"
		"		\"Yield\": 10,\n"
		"		\"Ingredients\": {\n"
		"			\"Basic labour\": 3,\n"
		"			\"Iron\": 5,\n"
		"			\"Wood\": 1\n"
		"		}\n"
		"	}\n"
		"}",
		"Medium cannon balls:\n"
		" Yield: 10\n"
		" Ingredients:\n"
		"  Basic labour: 3\n"
		"  Iron: 8\n"
		"  Skilled labour: 2\n"
		"  Wood: 3\n",
		"{\n"
		"	\"Medium cannon balls\": {\n"
		"		\"Yield\": 10,\n"
		"		\"Ingredients\": {\n"
		"			\"Basic labour\": 3,\n"
		"			\"Iron\": 8,\n"
		"			\"Skilled labour\": 2,\n"
		"			\"Wood\": 3\n"
		"		}\n"
		"	}\n"
		"}",
		"Large cannon balls:\n"
		" Yield: 1\n"
		" Ingredients:\n"
		"  Basic labour: 2\n"
		"  Iron: 12\n"
		"  Skilled labour: 5\n"
		"  Wood: 4\n",
		"{\n"
		"	\"Large cannon balls\": {\n"
		"		\"Ingredients\": {\n"
		"			\"Basic labour\": 2,\n"
		"			\"Iron\": 12,\n"
		"			\"Skilled labour\": 5,\n"
		"			\"Wood\": 4\n"
		"		}\n"
		"	}\n"
		"}",
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
