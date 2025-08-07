#include "ATest.h"

#include "CDataBase.h"
#include "CProductPrices.h"

using namespace ypp_sm;

INITIALIZE_TEST( TProductPrices )

namespace
{

using recipes = types::CDataBase::recipes;
using recipe_item = types::CRecipe::items::value_type;
using prices = types::CDataBase::prices;
using price_item = prices::value_type;

const CDataBase& EXAMPLE_DATABASE() noexcept
{
	static const auto dataBase = ValueFromJSONFile<CDataBase>( ( ATest::TESTS_PATH() / "unit/blackthorpe.json" ).string() );
	return dataBase;
}

} // anonymous namespace

void TProductPrices::TestExceptions()
{
}

std::vector<std::string> TProductPrices::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& productPrices : {
		CProductPrices{ EXAMPLE_DATABASE() },
	} )
	{
		result.emplace_back( productPrices.GetDescription() );
	}

	return result;
}

std::vector<std::string> TProductPrices::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Product prices:\n"
		" Apothecary:\n"
		"  Tan enamel:\n"
		"   Order price: 613\n"
		"   Unit cost: 85.7429\n"
		"  White enamel:\n"
		"   Order price: 18434\n"
		"   Unit cost: 2603.49\n"
		"  Yellow enamel:\n"
		"   Order price: 801\n"
		"   Unit cost: 112.714\n"
		" Distillery:\n"
		"  Grog:\n"
		"   Order price: 439\n"
		"   Unit cost: 39.21\n"
		" Iron Monger:\n"
		"  Foil (Tan enamel, Tan enamel):\n"
		"   Order price: 586\n"
		"   Unit cost: 4561.5\n"
		"  Foil (Tan enamel, White enamel):\n"
		"   Order price: 3464\n"
		"   Unit cost: 22185.7\n"
		"  Foil (Tan enamel, Yellow enamel):\n"
		"   Order price: 600\n"
		"   Unit cost: 4750.3\n"
		"  Foil (White enamel, Tan enamel):\n"
		"   Order price: 3464\n"
		"   Unit cost: 22185.7\n"
		"  Foil (White enamel, White enamel):\n"
		"   Order price: 6341\n"
		"   Unit cost: 39809.9\n"
		"  Foil (White enamel, Yellow enamel):\n"
		"   Order price: 3477\n"
		"   Unit cost: 22374.5\n"
		"  Foil (Yellow enamel, Tan enamel):\n"
		"   Order price: 600\n"
		"   Unit cost: 4750.3\n"
		"  Foil (Yellow enamel, White enamel):\n"
		"   Order price: 3477\n"
		"   Unit cost: 22374.5\n"
		"  Foil (Yellow enamel, Yellow enamel):\n"
		"   Order price: 613\n"
		"   Unit cost: 4939.1\n"
		"  Large cannon balls:\n"
		"   Order price: 573\n"
		"   Unit cost: 51.8\n"
		"  Medium cannon balls:\n"
		"   Order price: 384\n"
		"   Unit cost: 34.74\n"
		"  Small cannon balls:\n"
		"   Order price: 205\n"
		"   Unit cost: 17.67\n",
	};
	return result;
}

