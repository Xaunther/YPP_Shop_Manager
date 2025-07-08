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
		CRecipe{ "Grog", {}, 0 };
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
	std::vector<std::string> result;

	for( const auto& recipe : {
		CRecipe{ "Small cannon balls",
		{
			CRecipeItem{ "Iron", 5 },
			CRecipeItem{ "Wood", 1 },
			CRecipeItem{ "Basic labour", 3 },
		}, 10 },
		CRecipe{ "Medium cannon balls",
		{
			CRecipeItem{ "Iron", 8 },
			CRecipeItem{ "Wood", 3 },
			CRecipeItem{ "Basic labour", 3 },
			CRecipeItem{ "Skilled labour", 2 },
		}, 10 },
		CRecipe{ "Large cannon balls",
		{
			CRecipeItem{ "Iron", 12 },
			CRecipeItem{ "Wood", 4 },
			CRecipeItem{ "Basic labour", 2 },
			CRecipeItem{ "Skilled labour", 5 },
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
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, recipe, recipe.GetKey() );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TRecipe::ExpectedResults() noexcept
{
	std::vector<std::string> result{
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
