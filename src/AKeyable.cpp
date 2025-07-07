#include "AKeyable.h"

namespace ypp_sm
{

AKeyable::AKeyable( std::string_view aKey ) :
	mKey( aKey )
{
}

std::string_view AKeyable::GetKey() const noexcept
{
	return mKey;
}

} // ypp_sm namespace
