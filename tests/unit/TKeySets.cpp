#include "ATest.h"

#include "CKeySets.h"
#include "CRecipe.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TRecipes )

void TRecipes::TestExceptions()
{
}

std::vector<std::string> TRecipes::ObtainedResults() noexcept
{
	std::vector<std::string> result;
	{
		using recipes = CKeySets<CRecipe>;
		using recipe_item = types::CRecipe::items::value_type;

		for( const auto& recipes : {
			recipes{ {
			{
				"Iron Monger",
				{
					CRecipe{
						"Small cannon balls",
						{
							recipe_item{ "Iron", 5 },
							recipe_item{ "Wood", 1 },
							recipe_item{ "Basic labour", 3 },
						}, 10
					},
					CRecipe{
						"Medium cannon balls",
						{
							recipe_item{ "Iron", 8 },
							recipe_item{ "Wood", 3 },
							recipe_item{ "Basic labour", 3 },
							recipe_item{ "Skilled labour", 2 },
						}, 10
					},
					CRecipe{
						"Large cannon balls",
						{
							recipe_item{ "Iron", 12 },
							recipe_item{ "Wood", 4 },
							recipe_item{ "Basic labour", 2 },
							recipe_item{ "Skilled labour", 5 },
						}, 10
					}
				}
			},
			{
				"Shipyard",
				{
					CRecipe{
						"Lifeboats",
						{
							recipe_item{ "Iron", 30 },
							recipe_item{ "Wood", 85 },
							recipe_item{ "Grog", 15 },
							recipe_item{ "Skilled labour", 50 },
							recipe_item{ "Basic labour", 5 },
						}, 10
					}
				}
			}
			} },
			ValueFromJSONKeyString<recipes>( R"( {
				"Recipes": {
					"Iron Monger": {
						"Large cannon balls": {
							"Yield": 10,
							"Ingredients": {
								"Basic labour": 2,
								"Iron": 12,
								"Skilled labour": 5,
								"Wood": 4
							}
						},
						"Medium cannon balls": {
							"Yield": 10,
							"Ingredients": {
								"Basic labour": 3,
								"Iron": 8,
								"Skilled labour": 2,
								"Wood": 3
							}
						},
						"Small cannon balls": {
							"Yield": 10,
							"Ingredients": {
								"Basic labour": 3,
								"Iron": 5,
								"Wood": 1
							}
						}
					},
					"Shipyard": {
						"Lifeboats": {
							"Yield": 10,
							"Ingredients": {
								"Basic labour": 5,
								"Grog": 15,
								"Iron": 30,
								"Skilled labour": 50,
								"Wood": 85
							}
						}
					}
				}
			} )", "Recipes" ),
		} )
		{
			ypp_sm::types::IJsonable::json outputJSON;
			AddToJSONKey( outputJSON, recipes, "Recipes" );
			result.push_back( outputJSON.dump( 1, '\t' ) );
		}
	}

	{
		using price_item = CKeyItem<float>;
		using prices = CKeySets<price_item>;

		for( const auto& prices : {
			prices{ {
			{
				"Basic items",
				{
					price_item{ "Iron", 13 },
					price_item{ "Wood", 16.5 },
				}
			},
			{
				"Labour",
				{
					price_item{ "Skilled labour", 30 },
					price_item{ "Basic labour", 25 },
				}
			}
			} },
			ValueFromJSONKeyString<prices>( R"( {
				"Prices": {
					"Basic items": {
						"Iron": 13,
						"Wood": 16.5
					},
					"Labour": {
						"Basic labour": 25,
						"Skilled labour": 30
					}
				}
			} )", "Prices" ),
		} )
		{
			ypp_sm::types::IJsonable::json outputJSON;
			AddToJSONKey( outputJSON, prices, "Prices" );
			result.push_back( outputJSON.dump( 1, '\t' ) );
		}
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
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": {\n"
		"					\"Basic labour\": 2,\n"
		"					\"Iron\": 12,\n"
		"					\"Skilled labour\": 5,\n"
		"					\"Wood\": 4\n"
		"				}\n"
		"			},\n"
		"			\"Medium cannon balls\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": {\n"
		"					\"Basic labour\": 3,\n"
		"					\"Iron\": 8,\n"
		"					\"Skilled labour\": 2,\n"
		"					\"Wood\": 3\n"
		"				}\n"
		"			},\n"
		"			\"Small cannon balls\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": {\n"
		"					\"Basic labour\": 3,\n"
		"					\"Iron\": 5,\n"
		"					\"Wood\": 1\n"
		"				}\n"
		"			}\n"
		"		},\n"
		"		\"Shipyard\": {\n"
		"			\"Lifeboats\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": {\n"
		"					\"Basic labour\": 5,\n"
		"					\"Grog\": 15,\n"
		"					\"Iron\": 30,\n"
		"					\"Skilled labour\": 50,\n"
		"					\"Wood\": 85\n"
		"				}\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );

	{
		std::vector<std::string> pricesResult{
				"{\n"
				"	\"Prices\": {\n"
				"		\"Basic items\": {\n"
				"			\"Iron\": 13.0,\n"
				"			\"Wood\": 16.5\n"
				"		},\n"
				"		\"Labour\": {\n"
				"			\"Basic labour\": 25.0,\n"
				"			\"Skilled labour\": 30.0\n"
				"		}\n"
				"	}\n"
				"}"
			};
		result.reserve( result.size() + 2 * pricesResult.size() );
		result.insert( result.cend(), pricesResult.cbegin(), pricesResult.cend() );
		result.insert( result.cend(), pricesResult.cbegin(), pricesResult.cend() );
	}
	return result;
}
