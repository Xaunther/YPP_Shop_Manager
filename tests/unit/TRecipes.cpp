#include "ATest.h"

#include "CRecipeItem.h"
#include "CRecipes.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TRecipes )

void TRecipes::TestExceptions()
{
}

std::vector<std::string> TRecipes::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& recipes : {
		CRecipes{ {
		{
			"Iron Monger",
			{
				{
					"Small cannon balls",
					{
						CRecipeItem{ "Iron", 5 },
						CRecipeItem{ "Wood", 1 },
						CRecipeItem{ "Basic labour", 3 },
					},
				},
				{
					"Medium cannon balls",
					{
						CRecipeItem{ "Iron", 8 },
						CRecipeItem{ "Wood", 3 },
						CRecipeItem{ "Basic labour", 3 },
						CRecipeItem{ "Skilled labour", 2 },
					},
				},
				{
					"Large cannon balls",
					{
						CRecipeItem{ "Iron", 12 },
						CRecipeItem{ "Wood", 4 },
						CRecipeItem{ "Basic labour", 2 },
						CRecipeItem{ "Skilled labour", 5 },
					},
				}
			}
		},
		{
			"Shipyard",
			{
				{
					"Lifeboats",
					{
						CRecipeItem{ "Iron", 30 },
						CRecipeItem{ "Wood", 85 },
						CRecipeItem{ "Grog", 15 },
						CRecipeItem{ "Skilled labour", 50 },
						CRecipeItem{ "Basic labour", 5 },
					},
				}
			}
		}
		} },
		ValueFromJSONKeyString<CRecipes>( R"( {
			"Recipes": {
				"Iron Monger": {
					"Large cannon balls": {
						"Basic labour": 2,
						"Iron": 12,
						"Skilled labour": 5,
						"Wood": 4
					},
					"Medium cannon balls": {
						"Basic labour": 3,
						"Iron": 8,
						"Skilled labour": 2,
						"Wood": 3
					},
					"Small cannon balls": {
						"Basic labour": 3,
						"Iron": 5,
						"Wood": 1
					}
				},
				"Shipyard": {
					"Lifeboats": {
						"Basic labour": 5,
						"Grog": 15,
						"Iron": 30,
						"Skilled labour": 50,
						"Wood": 85
					}
				}
			}
		} )" ),
	} )
	{
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, recipes );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TRecipes::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"{\n"
		"	\"Recipes\": {\n"
		"		\"Iron Monger\": {\n"
		"			\"Large cannon balls\": {\n"
		"				\"Basic labour\": 2,\n"
		"				\"Iron\": 12,\n"
		"				\"Skilled labour\": 5,\n"
		"				\"Wood\": 4\n"
		"			},\n"
		"			\"Medium cannon balls\": {\n"
		"				\"Basic labour\": 3,\n"
		"				\"Iron\": 8,\n"
		"				\"Skilled labour\": 2,\n"
		"				\"Wood\": 3\n"
		"			},\n"
		"			\"Small cannon balls\": {\n"
		"				\"Basic labour\": 3,\n"
		"				\"Iron\": 5,\n"
		"				\"Wood\": 1\n"
		"			}\n"
		"		},\n"
		"		\"Shipyard\": {\n"
		"			\"Lifeboats\": {\n"
		"				\"Basic labour\": 5,\n"
		"				\"Grog\": 15,\n"
		"				\"Iron\": 30,\n"
		"				\"Skilled labour\": 50,\n"
		"				\"Wood\": 85\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
