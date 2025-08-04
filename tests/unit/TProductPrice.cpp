#include "ATest.h"

#include "CDataBase.h"
#include "CProductPrice.h"

using namespace ypp_sm;

INITIALIZE_TEST( TProductPrice )

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
					recipe_item{ { "Wood" }, 1 },
					recipe_item{ { "Iron", "Market Iron" }, 5 },
					recipe_item{ { "Basic" }, 3 },
				}, 0, 10 },
				CRecipe{ "Foil",
				{
					recipe_item{ { "Iron" }, 1 },
					recipe_item{ { "White enamel", "Tan enamel", "Yellow enamel" }, 1 },
					recipe_item{ { "White enamel", "Tan enamel", "Yellow enamel" }, 1 },
					recipe_item{ { "Basic" }, 15 },
				}, 0, 10 },
			}
		},
		{
			"Distillery",
			{
				CRecipe{ "Grog",
				{
					recipe_item{ { "Sugar cane" }, 10 },
					recipe_item{ { "Wood" }, 5 },
					recipe_item{ { "Iron" }, 1 },
					recipe_item{ { "Basic" }, 2 },
					recipe_item{ { "Skilled" }, 2 },
				}, 0, 10 },
			}
		},
		{
			"Shipwrightery",
			{
				CRecipe{ "Lifeboats",
				{
					recipe_item{ { "Wood" }, 85 },
					recipe_item{ { "Iron" }, 30 },
					recipe_item{ { "Grog" }, 15 },
					recipe_item{ { "Basic" }, 50 },
					recipe_item{ { "Skilled" }, 5 },
				}, 0, 10 },
			}
		},
		{
			"Apothecary",
			{
				CRecipe{ "White enamel",
				{
					recipe_item{ { "Iron" }, 4 },
					recipe_item{ { "Yarrow" }, 6 },
					recipe_item{ { "Basic" }, 2 },
				}, 0, 7 },
				CRecipe{ "Tan enamel",
				{
					recipe_item{ { "Iron" }, 4 },
					recipe_item{ { "Old man's beard" }, 6 },
					recipe_item{ { "Iris root" }, 6 },
					recipe_item{ { "Basic" }, 1 },
					recipe_item{ { "Skilled" }, 1 },
				}, 0, 7 },
				CRecipe{ "Yellow enamel",
				{
					recipe_item{ { "Iron" }, 4 },
					recipe_item{ { "Weld" }, 6 },
					recipe_item{ { "Basic" }, 2 },
				}, 0, 7 },
			}
		}
		} },
		prices{ prices::key_sets{
		{
			"Herbs",
			{
				price_item{ "Yarrow", 2800, 2800, 252.2 },
				price_item{ "Old man's beard", 11, 11, 0.9 },
				price_item{ "Iris root", 63, 63, 4.9 },
				price_item{ "Weld", 106, 106, 7.1 },
			},
		},
		{
			"Enamel",
			{
				price_item{ "White enamel", 2700, 2700, 274.3 },
				price_item{ "Tan enamel", 89, 89, 7.9 },
				price_item{ "Yellow enamel", 100, 100, 10.1 },
			},
		},
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
				price_item{ "Market Iron", 11, 11, 3.0 },
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

void TProductPrice::TestExceptions()
{
	// Test member constructor
	CheckException( []()
	{
		CProductPrice{ CRecipe{ "Deez balls", { recipe_item{ { "A" }, 3 } } }, EXAMPLE_DATABASE() };
	}, "A price table not found." );
}

std::vector<std::string> TProductPrice::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	for( const auto& productPrice : {
		CProductPrice{ *EXAMPLE_DATABASE().GetRecipes().GetKeySets().at( "Shipwrightery" ).find( "Lifeboats" ),
				EXAMPLE_DATABASE() },
		CProductPrice{ *EXAMPLE_DATABASE().GetRecipes().GetKeySets().at( "Iron Monger" ).find( "Small cannon balls" ),
				EXAMPLE_DATABASE() },
		CProductPrice{ *EXAMPLE_DATABASE().GetRecipes().GetKeySets().at( "Iron Monger" ).find( "Foil" ),
				EXAMPLE_DATABASE() },
	} )
	{
		result.emplace_back( productPrice.GetDescription() );
	}

	return result;
}

std::vector<std::string> TProductPrice::ExpectedResults() noexcept
{
	std::vector<std::string> result{
		"Lifeboats:\n"
		" Order price: 4158\n"
		" Unit cost: 371\n",
		"Small cannon balls (Iron):\n"
		" Order price: 196\n"
		" Unit cost: 19.61\n"
		"Small cannon balls (Market Iron):\n"
		" Order price: 156\n"
		" Unit cost: 15.61\n",
		"Foil (Tan enamel, Tan enamel):\n"
		" Order price: 560\n"
		" Unit cost: 161.46\n"
		"Foil (Tan enamel, White enamel):\n"
		" Order price: 3438\n"
		" Unit cost: 1943.8\n"
		"Foil (Tan enamel, Yellow enamel):\n"
		" Order price: 574\n"
		" Unit cost: 180.34\n"
		"Foil (White enamel, Tan enamel):\n"
		" Order price: 3438\n"
		" Unit cost: 1943.8\n"
		"Foil (White enamel, White enamel):\n"
		" Order price: 6315\n"
		" Unit cost: 3726.14\n"
		"Foil (White enamel, Yellow enamel):\n"
		" Order price: 3451\n"
		" Unit cost: 1962.68\n"
		"Foil (Yellow enamel, Tan enamel):\n"
		" Order price: 574\n"
		" Unit cost: 180.34\n"
		"Foil (Yellow enamel, White enamel):\n"
		" Order price: 3451\n"
		" Unit cost: 1962.68\n"
		"Foil (Yellow enamel, Yellow enamel):\n"
		" Order price: 587\n"
		" Unit cost: 199.22\n",
	};
	return result;
}

