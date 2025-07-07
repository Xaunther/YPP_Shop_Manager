#include "IJsonable.h"

namespace ypp_sm
{

void IJsonable::ToJSON( json& aJSON ) const noexcept
{
	this->JSON( aJSON );
}

} // ypp_sm namespace
