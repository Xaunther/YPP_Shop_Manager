#include "ATest.h"

#include "CKeyItem.h"
#include "CKeySets.h"
#include "CRecipe.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TRecipes )

using recipes = CKeySets<CRecipe>;
using recipe_item = types::CRecipe::items::value_type;

void TRecipes::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		recipes{ {
		{
			"Furnisher",
			{
				CRecipe{ "Small cannon balls", { recipe_item{ { "Basic labour" }, 3 }, }, 0, 10 },
				CRecipe{ "Large cannon balls", { recipe_item{ { "Basic labour" }, 3 }, }, 0, 10 },
			},
		},
		{
			"Iron Monger",
			{
				CRecipe{ "Small cannon balls", { recipe_item{ { "Basic labour" }, 3 }, }, 0, 10 },
				CRecipe{ "Large cannon balls", { recipe_item{ { "Basic labour" }, 3 }, }, 0, 10 },
			}
		},
	} };
	}, "The following items are repeated: Large cannon balls, Small cannon balls" );

	// Test JSON constructor
	CheckException( []()
	{
		ValueFromJSONKeyString<recipes>( R"( {
			"Recipes": {
				"Furnisher": {
					"Large cannon balls": {
						"Yield": 10,
						"Ingredients": [
							{
								"Ingredient": [ "Basic labour" ],
								"Count": 2
							}
						]
					},
					"Small cannon balls": {
						"Yield": 10,
						"Ingredients": [
							{
								"Ingredient": [ "Basic labour" ],
								"Count": 3
							}
						]
					}
				},
				"Iron Monger": {
					"Large cannon balls": {
						"Yield": 10,
						"Ingredients": [
							{
								"Ingredient": [ "Basic labour" ],
								"Count": 2
							}
						]
					},
					"Small cannon balls": {
						"Yield": 10,
						"Ingredients": [
							{
								"Ingredient": [ "Basic labour" ],
								"Count": 3
							}
						]
					}
				}
			}
		} )", "Recipes" );
	}, "The following items are repeated: Large cannon balls, Small cannon balls" );
}

std::vector<std::string> TRecipes::ObtainedResults() noexcept
{
	std::vector<std::string> result;
	{
		for( const auto& recipes : {
			recipes{ {
			{
				"Iron Monger",
				{
					CRecipe{
						"Small cannon balls",
						{
							recipe_item{ { "Iron" }, 5 },
							recipe_item{ { "Wood" }, 1 },
							recipe_item{ { "Basic labour" }, 3 },
						}, 0, 10
					},
					CRecipe{
						"Medium cannon balls",
						{
							recipe_item{ { "Iron" }, 8 },
							recipe_item{ { "Wood" }, 3 },
							recipe_item{ { "Basic labour" }, 3 },
							recipe_item{ { "Skilled labour" }, 2 },
						}, 0, 10
					},
					CRecipe{
						"Large cannon balls",
						{
							recipe_item{ { "Iron" }, 12 },
							recipe_item{ { "Wood" }, 4 },
							recipe_item{ { "Basic labour" }, 2 },
							recipe_item{ { "Skilled labour" }, 5 },
						}, 0, 10
					}
				}
			},
			{
				"Shipyard",
				{
					CRecipe{
						"Lifeboats",
						{
							recipe_item{ { "Iron" }, 30 },
							recipe_item{ { "Wood" }, 85 },
							recipe_item{ { "Grog" }, 15 },
							recipe_item{ { "Skilled labour" }, 50 },
							recipe_item{ { "Basic labour" }, 5 },
						}, 0, 10
					}
				}
			}
			} },
			ValueFromJSONKeyString<recipes>( R"( {
				"Recipes": {
					"Iron Monger": {
						"Large cannon balls": {
							"Yield": 10,
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
						},
						"Medium cannon balls": {
							"Yield": 10,
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
						},
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
					},
					"Shipyard": {
						"Lifeboats": {
							"Yield": 10,
							"Ingredients": [
								{
									"Ingredient": [ "Iron" ],
									"Count": 30
								},
								{
									"Ingredient": [ "Wood" ],
									"Count": 85
								},
								{
									"Ingredient": [ "Grog" ],
									"Count": 15
								},
								{
									"Ingredient": [ "Skilled labour" ],
									"Count": 50
								},
								{
									"Ingredient": [ "Basic labour" ],
									"Count": 5
								}
							]
						}
					}
				}
			} )", "Recipes" ),
		} )
		{
			result.emplace_back( recipes.GetDescription( 0, '\t' ) );
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
		"Iron Monger:\n"
		"	Large cannon balls:\n"
		"		Doubloons: 0\n"
		"		Yield: 10\n"
		"		Ingredients:\n"
		"			12 of:\n"
		"				Iron\n"
		"			4 of:\n"
		"				Wood\n"
		"			2 of:\n"
		"				Basic labour\n"
		"			5 of:\n"
		"				Skilled labour\n"
		"	Medium cannon balls:\n"
		"		Doubloons: 0\n"
		"		Yield: 10\n"
		"		Ingredients:\n"
		"			8 of:\n"
		"				Iron\n"
		"			3 of:\n"
		"				Wood\n"
		"			3 of:\n"
		"				Basic labour\n"
		"			2 of:\n"
		"				Skilled labour\n"
		"	Small cannon balls:\n"
		"		Doubloons: 0\n"
		"		Yield: 10\n"
		"		Ingredients:\n"
		"			5 of:\n"
		"				Iron\n"
		"			1 of:\n"
		"				Wood\n"
		"			3 of:\n"
		"				Basic labour\n"
		"Shipyard:\n"
		"	Lifeboats:\n"
		"		Doubloons: 0\n"
		"		Yield: 10\n"
		"		Ingredients:\n"
		"			30 of:\n"
		"				Iron\n"
		"			85 of:\n"
		"				Wood\n"
		"			15 of:\n"
		"				Grog\n"
		"			50 of:\n"
		"				Skilled labour\n"
		"			5 of:\n"
		"				Basic labour\n",
		"{\n"
		"	\"Recipes\": {\n"
		"		\"Iron Monger\": {\n"
		"			\"Large cannon balls\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": [\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Iron\"\n"
		"						],\n"
		"						\"Count\": 12\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Wood\"\n"
		"						],\n"
		"						\"Count\": 4\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Basic labour\"\n"
		"						],\n"
		"						\"Count\": 2\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Skilled labour\"\n"
		"						],\n"
		"						\"Count\": 5\n"
		"					}\n"
		"				]\n"
		"			},\n"
		"			\"Medium cannon balls\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": [\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Iron\"\n"
		"						],\n"
		"						\"Count\": 8\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Wood\"\n"
		"						],\n"
		"						\"Count\": 3\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Basic labour\"\n"
		"						],\n"
		"						\"Count\": 3\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Skilled labour\"\n"
		"						],\n"
		"						\"Count\": 2\n"
		"					}\n"
		"				]\n"
		"			},\n"
		"			\"Small cannon balls\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": [\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Iron\"\n"
		"						],\n"
		"						\"Count\": 5\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Wood\"\n"
		"						],\n"
		"						\"Count\": 1\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Basic labour\"\n"
		"						],\n"
		"						\"Count\": 3\n"
		"					}\n"
		"				]\n"
		"			}\n"
		"		},\n"
		"		\"Shipyard\": {\n"
		"			\"Lifeboats\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": [\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Iron\"\n"
		"						],\n"
		"						\"Count\": 30\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Wood\"\n"
		"						],\n"
		"						\"Count\": 85\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Grog\"\n"
		"						],\n"
		"						\"Count\": 15\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Skilled labour\"\n"
		"						],\n"
		"						\"Count\": 50\n"
		"					},\n"
		"					{\n"
		"						\"Ingredient\": [\n"
		"							\"Basic labour\"\n"
		"						],\n"
		"						\"Count\": 5\n"
		"					}\n"
		"				]\n"
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
