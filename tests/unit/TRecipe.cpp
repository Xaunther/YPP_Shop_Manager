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
			recipe_item{ { "Iron" }, 5 },
			recipe_item{ { "Wood" }, 1 },
			recipe_item{ { "Basic labour" }, 3 },
		}, 0, 10 },
		CRecipe{ "Medium cannon balls",
		{
			recipe_item{ { "Iron" }, 8 },
			recipe_item{ { "Wood" }, 3 },
			recipe_item{ { "Basic labour" }, 3 },
			recipe_item{ { "Skilled labour" }, 2 },
		}, 0, 10, 100 },
		CRecipe{ "Large cannon balls",
		{
			recipe_item{ { "Iron" }, 12 },
			recipe_item{ { "Wood" }, 4 },
			recipe_item{ { "Basic labour" }, 2 },
			recipe_item{ { "Skilled labour" }, 5 },
		} },
		CRecipe{ "Foil",
		{
			recipe_item{ { "Iron" }, 1 },
			recipe_item{ { "Tan enamel" }, 1 },
			recipe_item{ { "White enamel" }, 1 },
			recipe_item{ { "Basic labour" }, 15 },
		}, 1 },
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Small cannon balls": {
				"Yield": 10,
				"Ingredients": [
					{
						"Ingredient": [ "Iron" ],
						"Count": 5
					},
					{
						"Ingredient": [ "Wood" ],
						"Count": 1
					},
					{
						"Ingredient": [ "Basic labour" ],
						"Count": 3
					}
				]
			}
		} )", "Small cannon balls", "Small cannon balls" ),
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Medium cannon balls": {
				"Yield": 10,
				"Price adjustment": 100,
				"Ingredients": [
					{
						"Ingredient": [ "Iron" ],
						"Count": 8
					},
					{
						"Ingredient": [ "Wood" ],
						"Count": 3
					},
					{
						"Ingredient": [ "Basic labour" ],
						"Count": 3
					},
					{
						"Ingredient": [ "Skilled labour" ],
						"Count": 2
					}
				]
			}
		} )", "Medium cannon balls", "Medium cannon balls" ),
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Large cannon balls": {
				"Ingredients": [
					{
						"Ingredient": [ "Iron" ],
						"Count": 12
					},
					{
						"Ingredient": [ "Wood" ],
						"Count": 4
					},
					{
						"Ingredient": [ "Basic labour" ],
						"Count": 2
					},
					{
						"Ingredient": [ "Skilled labour" ],
						"Count": 5
					}
				]
			}
		} )", "Large cannon balls", "Large cannon balls" ),
		ValueFromJSONKeyString<CRecipe>( R"( {
			"Foil": {
				"Doubloons": 1,
				"Ingredients": [
					{
						"Ingredient": [ "Iron" ],
						"Count": 1
					},
					{
						"Ingredient": [ "Tan enamel" ],
						"Count": 1
					},
					{
						"Ingredient": [ "White enamel" ],
						"Count": 1
					},
					{
						"Ingredient": [ "Basic labour" ],
						"Count": 15
					}
				]
			}
		} )", "Foil", "Foil" ),
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
		" Doubloons: 0\n"
		" Yield: 10\n"
		" Price adjustment: 0\n"
		" Ingredients:\n"
		"  5 of:\n"
		"   Iron\n"
		"  1 of:\n"
		"   Wood\n"
		"  3 of:\n"
		"   Basic labour\n",
		"{\n"
		"	\"Small cannon balls\": {\n"
		"		\"Yield\": 10,\n"
		"		\"Ingredients\": [\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Iron\"\n"
		"				],\n"
		"				\"Count\": 5\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Wood\"\n"
		"				],\n"
		"				\"Count\": 1\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Basic labour\"\n"
		"				],\n"
		"				\"Count\": 3\n"
		"			}\n"
		"		]\n"
		"	}\n"
		"}",
		"Medium cannon balls:\n"
		" Doubloons: 0\n"
		" Yield: 10\n"
		" Price adjustment: 100\n"
		" Ingredients:\n"
		"  8 of:\n"
		"   Iron\n"
		"  3 of:\n"
		"   Wood\n"
		"  3 of:\n"
		"   Basic labour\n"
		"  2 of:\n"
		"   Skilled labour\n",
		"{\n"
		"	\"Medium cannon balls\": {\n"
		"		\"Yield\": 10,\n"
		"		\"Price adjustment\": 100,\n"
		"		\"Ingredients\": [\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Iron\"\n"
		"				],\n"
		"				\"Count\": 8\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Wood\"\n"
		"				],\n"
		"				\"Count\": 3\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Basic labour\"\n"
		"				],\n"
		"				\"Count\": 3\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Skilled labour\"\n"
		"				],\n"
		"				\"Count\": 2\n"
		"			}\n"
		"		]\n"
		"	}\n"
		"}",
		"Large cannon balls:\n"
		" Doubloons: 0\n"
		" Yield: 1\n"
		" Price adjustment: 0\n"
		" Ingredients:\n"
		"  12 of:\n"
		"   Iron\n"
		"  4 of:\n"
		"   Wood\n"
		"  2 of:\n"
		"   Basic labour\n"
		"  5 of:\n"
		"   Skilled labour\n",
		"{\n"
		"	\"Large cannon balls\": {\n"
		"		\"Ingredients\": [\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Iron\"\n"
		"				],\n"
		"				\"Count\": 12\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Wood\"\n"
		"				],\n"
		"				\"Count\": 4\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Basic labour\"\n"
		"				],\n"
		"				\"Count\": 2\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Skilled labour\"\n"
		"				],\n"
		"				\"Count\": 5\n"
		"			}\n"
		"		]\n"
		"	}\n"
		"}",
		"Foil:\n"
		" Doubloons: 1\n"
		" Yield: 1\n"
		" Price adjustment: 0\n"
		" Ingredients:\n"
		"  1 of:\n"
		"   Iron\n"
		"  1 of:\n"
		"   Tan enamel\n"
		"  1 of:\n"
		"   White enamel\n"
		"  15 of:\n"
		"   Basic labour\n",
		"{\n"
		"	\"Foil\": {\n"
		"		\"Doubloons\": 1,\n"
		"		\"Ingredients\": [\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Iron\"\n"
		"				],\n"
		"				\"Count\": 1\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Tan enamel\"\n"
		"				],\n"
		"				\"Count\": 1\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"White enamel\"\n"
		"				],\n"
		"				\"Count\": 1\n"
		"			},\n"
		"			{\n"
		"				\"Ingredient\": [\n"
		"					\"Basic labour\"\n"
		"				],\n"
		"				\"Count\": 15\n"
		"			}\n"
		"		]\n"
		"	}\n"
		"}",
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
