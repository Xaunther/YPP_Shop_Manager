#include "ATest.h"

#include "CPrices.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TPrices )

void TPrices::TestExceptions()
{
}

std::vector<std::string> TPrices::ObtainedResults() noexcept
{
	using price_item = types::CPrices::prices::value_type;
	std::vector<std::string> result;

	for( const auto& prices : {
		CPrices{ {
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
		ValueFromJSONKeyString<CPrices>( R"( {
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
		} )" ),
	} )
	{
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSONKey( outputJSON, prices );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPrices::ExpectedResults() noexcept
{
	std::vector<std::string> result{
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
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
