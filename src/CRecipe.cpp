#include "CRecipe.h"

#include "ExceptionUtils.h"

namespace ypp_sm
{

CRecipe::CRecipe( std::string_view aName, const items& aItems ) try :
	AKeyable( aName ),
	mItems( aItems )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a recipe." )

const CRecipe::items& CRecipe::GetItems() const noexcept
{
	return mItems;
}

} // ypp_sm namespace
