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
	static const CDataBase dataBase{ recipes{
		recipes::key_sets{
		{
			"Iron Monger",
			{
				CRecipe{ "Small cannon balls",
				{
					recipe_item{ "Wood", 1 },
					recipe_item{ "Iron", 5 },
					recipe_item{ "Basic", 3 },
				}, 0, 10 },
			}
		},
		{
			"Distillery",
			{
				CRecipe{ "Grog",
				{
					recipe_item{ "Sugar cane", 10 },
					recipe_item{ "Wood", 5 },
					recipe_item{ "Iron", 1 },
					recipe_item{ "Basic", 2 },
					recipe_item{ "Skilled", 2 },
				}, 0, 10 },
			}
		},
		{
			"Shipwrightery",
			{
				CRecipe{ "Lifeboats",
				{
					recipe_item{ "Wood", 85 },
					recipe_item{ "Iron", 30 },
					recipe_item{ "Grog", 15 },
					recipe_item{ "Basic", 50 },
					recipe_item{ "Skilled", 5 },
				}, 0, 10 },
			}
		} } },
		prices{ prices::key_sets{
		{
			"Ship supplies",
			{
				price_item{ "Grog", 44, 44, 4.3 },
			},
		},
		{
			"Basic commodities",
			{
				price_item{ "Wood", 15, 15, 2.1 },
				price_item{ "Iron", 19, 19, 3.0 },
				price_item{ "Sugar cane", 5, 5, 0.5 },
			},
		},
		{
			"Labour",
			{
				price_item{ "Basic", 20, 20, 3.0 },
				price_item{ "Skilled", 30, 30, 4.0 },
				price_item{ "Expert", 50, 50, 5.0 },
			},
		}
	} }, 3000 };
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
		" Distillery:\n"
		"  Grog:\n"
		"   Order price: 276\n"
		"   Unit cost: 27.65\n"
		" Iron Monger:\n"
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

