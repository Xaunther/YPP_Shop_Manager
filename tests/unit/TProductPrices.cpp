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
		"   Order price: 623\n"
		"   Unit cost: 89.1143\n"
		"  White enamel:\n"
		"   Order price: 18447\n"
		"   Unit cost: 2635.31\n"
		"  Yellow enamel:\n"
		"   Order price: 812\n"
		"   Unit cost: 116.086\n"
		" Distillery:\n"
		"  Grog:\n"
		"   Order price: 276\n"
		"   Unit cost: 27.65\n"
		" Iron Monger:\n"
		"  Foil (Tan enamel, Tan enamel):\n"
		"   Order price: 560\n"
		"   Unit cost: 161.46\n"
		"  Foil (Tan enamel, White enamel):\n"
		"   Order price: 3438\n"
		"   Unit cost: 1943.8\n"
		"  Foil (Tan enamel, Yellow enamel):\n"
		"   Order price: 574\n"
		"   Unit cost: 180.34\n"
		"  Foil (White enamel, Tan enamel):\n"
		"   Order price: 3438\n"
		"   Unit cost: 1943.8\n"
		"  Foil (White enamel, White enamel):\n"
		"   Order price: 6315\n"
		"   Unit cost: 3726.14\n"
		"  Foil (White enamel, Yellow enamel):\n"
		"   Order price: 3451\n"
		"   Unit cost: 1962.68\n"
		"  Foil (Yellow enamel, Tan enamel):\n"
		"   Order price: 574\n"
		"   Unit cost: 180.34\n"
		"  Foil (Yellow enamel, White enamel):\n"
		"   Order price: 3451\n"
		"   Unit cost: 1962.68\n"
		"  Foil (Yellow enamel, Yellow enamel):\n"
		"   Order price: 587\n"
		"   Unit cost: 199.22\n"
		"  Small cannon balls:\n"
		"   Order price: 196\n"
		"   Unit cost: 19.61\n"
		" Shipwrightery:\n"
		"  Lifeboats:\n"
		"   Order price: 4158\n"
		"   Unit cost: 371\n",
	};
	return result;
}

