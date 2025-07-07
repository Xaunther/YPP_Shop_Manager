#include "CRecipeItem.h"

#include "ExceptionUtils.h"
#include "JsonUtils.h"

namespace ypp_sm
{

CRecipeItem::CRecipeItem( std::string_view aName, const count& aCount ) try :
	AKeyable( aName ),
	mCount( aCount )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe item." )

CRecipeItem::CRecipeItem( const json& aJSON, std::string_view aName ) try :
	CRecipeItem( aName, ValueFromJSON<count>( aJSON ) )
{
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error creating recipe item from JSON " << aJSON.dump() )

void CRecipeItem::JSON( json& aJSON ) const noexcept
{
	AddToJSON( aJSON, mCount );
}

const CRecipeItem::count& CRecipeItem::GetCount() const noexcept
{
	return mCount;
}

} // ypp_sm namespace
