#include "ATest.h"

#include "CDataBase.h"
#include "JsonUtils.h"

#include <filesystem>

using namespace ypp_sm;

INITIALIZE_TEST( TDataBase )

namespace
{

const CDataBase& EXAMPLE_DATABASE() noexcept
{
	static const auto dataBase = ValueFromJSONFile<CDataBase>( ( ATest::TESTS_PATH() / "unit/blackthorpe.json" ).string() );
	return dataBase;
}

} // anonymous namespace

void TDataBase::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		ValueFromJSONString<CDataBase>( R"( {} )" );
	}, "key 'Doubloon price' not found" );
}

std::vector<std::string> TDataBase::ObtainedResults() noexcept
{
	using recipes = types::CDataBase::recipes;
	using prices = types::CDataBase::prices;
	std::vector<std::string> result;

	for( auto database : {
		CDataBase{ recipes{}, prices{}, 2000 },
		CDataBase{ EXAMPLE_DATABASE().GetRecipes(), EXAMPLE_DATABASE().GetPrices(), EXAMPLE_DATABASE().GetDoubloonPrice() },
		ValueFromJSONString<CDataBase>( R"( {
			"Doubloon price": 2000
		} )" ),
		EXAMPLE_DATABASE(),
	} )
	{
		result.emplace_back( database.GetDescription() );
		ypp_sm::types::IJsonable::json outputJSON;
		AddToJSON( outputJSON, database );
		result.push_back( outputJSON.dump( 1, '\t' ) );
		database.SetDoubloonPrice( database.GetDoubloonPrice() + 100 );
		result.push_back( std::to_string( database.GetDoubloonPrice() ) );
	}

	return result;
}

std::vector<std::string> TDataBase::ExpectedResults() noexcept
{
	ypp_sm::types::IJsonable::json outputJSON;
	AddToJSON( outputJSON, EXAMPLE_DATABASE() );
	std::vector<std::string> result{
		"Doubloon price: 2000\n",
		"{\n"
		"	\"Doubloon price\": 2000\n"
		"}",
		"2100",
		EXAMPLE_DATABASE().GetDescription(),
		outputJSON.dump( 1, '\t' ),
		"3100",
	};
	result.reserve( 2 * result.size() );
	result.insert( result.cend(), result.cbegin(), result.cend() );
	return result;
}
