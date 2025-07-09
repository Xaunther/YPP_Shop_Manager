#include "IDescriptable.h"

namespace ypp_sm
{

std::string IDescriptable::GetDescription( unsigned int aIndentDepth, char aIndentChar ) const noexcept
{
	return Description( aIndentDepth, aIndentChar );
}

} // ypp_sm namespace
