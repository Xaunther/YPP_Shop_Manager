#include "CRecipes.h"

namespace ypp_sm
{

const CRecipes::shop_recipes& CRecipes::GetShopRecipes() const noexcept
{
	return mShopRecipes;
}

} // ypp_sm namespace
