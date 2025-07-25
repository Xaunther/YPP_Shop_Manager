#include "ATest.h"

#include "CDataBase.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TDataBase )

void TDataBase::TestExceptions()
{
}

std::vector<std::string> TDataBase::ObtainedResults() noexcept
{
	using recipes = types::CDataBase::recipes;
	using recipe_item = types::CRecipe::items::value_type;
	using prices = types::CDataBase::prices;
	using price_item = prices::value_type;
	std::vector<std::string> result;

	for( const auto& database : {
		CDataBase{ recipes{}, prices{} },
		CDataBase{ recipes{
			recipes::key_sets{
			{
				"Iron Monger",
				{
					CRecipe{ "Small cannon balls",
					{
						recipe_item{ "Wood", 3 },
						recipe_item{ "Iron", 5 }
					}, 0, 10 },
					CRecipe{ "Foil",
					{
						recipe_item{ "Black enamel", 1 },
						recipe_item{ "Tan enamel", 1 }
					}, 0, 1 }
				}
			},
			{
				"Shipwrightery",
				{
					CRecipe{ "Lifeboats",
					{
						recipe_item{ "Wood", 3 },
						recipe_item{ "Iron", 5 }
					}, 0, 10 },
				}
			} } },
			prices{ prices::key_sets{
			{
				"Basic commodities",
				{
					price_item{ "Wood", 11, 15, 2.1 },
					price_item{ "Iron", 19, 21, 3.0 }
				}
			}
		} } },
		ValueFromJSONString<CDataBase>( R"( {} )" ),
		ValueFromJSONString<CDataBase>( R"( {
			"Recipes": {
				"Iron Monger": {
					"Small cannon balls": {
						"Ingredients": {
							"Wood": 3,
							"Iron": 5
						},
						"Yield": 10
					},
					"Foil": {
						"Ingredients": {
							"Black enamel": 1,
							"Tan enamel": 1
						}
					}
				},
				"Shipwrightery": {
					"Lifeboats": {
						"Ingredients": {
							"Wood": 3,
							"Iron": 5
						},
						"Yield": 10
					}
				}
			},
			"Prices": {
				"Basic commodities": {
					"Wood": {
						"Cost": 11,
						"Use price": 15,
						"Tax": 2.1
					},
					"Iron": {
						"Cost": 19,
						"Use price": 21,
						"Tax": 3.0
					}
				}
			}
		} )" ),
	} )
	{
		result.emplace_back( database.GetDescription() );
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSON( outputJSON, database );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TDataBase::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"",
		"null",
		"Recipes:\n"
		" Iron Monger:\n"
		"  Foil:\n"
		"   Doubloons: 0\n"
		"   Yield: 1\n"
		"   Ingredients:\n"
		"    Black enamel: 1\n"
		"    Tan enamel: 1\n"
		"  Small cannon balls:\n"
		"   Doubloons: 0\n"
		"   Yield: 10\n"
		"   Ingredients:\n"
		"    Iron: 5\n"
		"    Wood: 3\n"
		" Shipwrightery:\n"
		"  Lifeboats:\n"
		"   Doubloons: 0\n"
		"   Yield: 10\n"
		"   Ingredients:\n"
		"    Iron: 5\n"
		"    Wood: 3\n"
		"Prices:\n"
		" Basic commodities:\n"
		"  Iron:\n"
		"   Cost: 19\n"
		"   Use price: 21\n"
		"   Tax: 3\n"
		"  Wood:\n"
		"   Cost: 11\n"
		"   Use price: 15\n"
		"   Tax: 2.1\n",
		"{\n"
		"	\"Recipes\": {\n"
		"		\"Iron Monger\": {\n"
		"			\"Foil\": {\n"
		"				\"Ingredients\": {\n"
		"					\"Black enamel\": 1,\n"
		"					\"Tan enamel\": 1\n"
		"				}\n"
		"			},\n"
		"			\"Small cannon balls\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": {\n"
		"					\"Iron\": 5,\n"
		"					\"Wood\": 3\n"
		"				}\n"
		"			}\n"
		"		},\n"
		"		\"Shipwrightery\": {\n"
		"			\"Lifeboats\": {\n"
		"				\"Yield\": 10,\n"
		"				\"Ingredients\": {\n"
		"					\"Iron\": 5,\n"
		"					\"Wood\": 3\n"
		"				}\n"
		"			}\n"
		"		}\n"
		"	},\n"
		"	\"Prices\": {\n"
		"		\"Basic commodities\": {\n"
		"			\"Iron\": {\n"
		"				\"Cost\": 19.0,\n"
		"				\"Use price\": 21,\n"
		"				\"Tax\": 3.0\n"
		"			},\n"
		"			\"Wood\": {\n"
		"				\"Cost\": 11.0,\n"
		"				\"Use price\": 15,\n"
		"				\"Tax\": 2.0999999046325684\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
