#include "CRecipes.h"

#include "ExceptionUtils.h"

namespace ypp_sm
{

CRecipes::CRecipes( const shop_recipes& aShopRecipes ) try :
	mShopRecipes( aShopRecipes )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating the recipes." )

const CRecipes::shop_recipes& CRecipes::GetShopRecipes() const noexcept
{
	return mShopRecipes;
}

} // ypp_sm namespace
