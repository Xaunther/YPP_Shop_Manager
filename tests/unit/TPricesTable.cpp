#include "ATest.h"

#include "CPricesTable.h"
#include "JsonUtils.h"

using namespace ypp_sm;

INITIALIZE_TEST( TPricesTable )

void TPricesTable::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CPricesTable{ -1, 0, 0 };
	}, "The average cost cannot be negative" );
	CheckException( []()
	{
		CPricesTable{ 0, 0, -1 };
	}, "The tax cannot be negative" );

	// Test JSON constructor
	CheckException( []()
	{
		ValueFromJSONKeyString<CPricesTable>( R"( {
			"Grog": {
				"Use price": 0,
				"Tax": 0
			}
		} )", "Grog" );
	}, "key 'Cost' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPricesTable>( R"( {
			"Grog": {
				"Cost": 0,
				"Tax": 0
			}
		} )", "Grog" );
	}, "key 'Use price' not found" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPricesTable>( R"( {
			"Grog": {
				"Cost": -1,
				"Use price": 0,
				"Tax": 0
			}
		} )", "Grog" );
	}, "The average cost cannot be negative" );
	CheckException( []()
	{
		ValueFromJSONKeyString<CPricesTable>( R"( {
			"Grog": {
				"Cost": 0,
				"Use price": 0,
				"Tax": -1
			}
		} )", "Grog" );
	}, "The tax cannot be negative" );
}

std::vector<std::string> TPricesTable::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& pricesTable : {
		CPricesTable{ 11, 15, 2.1 },
		ValueFromJSONKeyString<CPricesTable>( R"( {
			"Wood": {
				"Cost": 11,
				"Use price": 15,
				"Tax": 2.1
			}
		} )", "Wood" ),
	} )
	{
		result.emplace_back( pricesTable.GetDescription() );
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSON( outputJSON, pricesTable );
		result.push_back( outputJSON.dump( 1, '\t' ) );
	}

	return result;
}

std::vector<std::string> TPricesTable::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Cost: 11\n"
		"Use price: 15\n"
		"Tax: 2.1\n",
		"{\n"
		"	\"Cost\": 11.0,\n"
		"	\"Use price\": 15,\n"
		"	\"Tax\": 2.0999999046325684\n"
		"}",
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}

