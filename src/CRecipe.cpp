#include "CRecipe.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

CRecipe::CRecipe( std::string_view aName, const items& aItems ) try :
	AKeyable( aName ),
	mItems( aItems )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating a recipe." )

CRecipe::CRecipe( const json& aJSON, std::string_view aName ) try :
	AKeyable( aName )
{
	for( const auto& itemJSON : aJSON.items() )
		mItems.emplace( itemJSON.value(), itemJSON.key() );
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe from JSON " << aJSON.dump() <<"." )


const CRecipe::items& CRecipe::GetItems() const noexcept
{
	return mItems;
}

} // ypp_sm namespace
