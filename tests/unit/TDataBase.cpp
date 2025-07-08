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
					}, 10 },
					CRecipe{ "Foil",
					{
						recipe_item{ "Black enamel", 1 },
						recipe_item{ "Tan enamel", 1 }
					}, 1 }
				}
			},
			{
				"Shipwrightery",
				{
					CRecipe{ "Lifeboats",
					{
						recipe_item{ "Wood", 3 },
						recipe_item{ "Iron", 5 }
					}, 10 },
				}
			} } },
			prices{ prices::key_sets{
			{
				"Basic commodities",
				{
					price_item{ "Wood", 11 },
					price_item{ "Iron", 19 }
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
					"Wood": 11,
					"Iron": 19
				}
			}
		} )" ),
	} )
	{
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSON( outputJSON, database );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TDataBase::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"null",
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
		"			\"Iron\": 19.0,\n"
		"			\"Wood\": 11.0\n"
		"		}\n"
		"	}\n"
		"}"
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
