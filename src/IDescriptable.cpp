#include "IDescriptable.h"

namespace ypp_sm
{

std::string IDescriptable::GetDescription( unsigned int aIndentDepth, const std::string_view aIndentString ) const noexcept
{
	return Description( aIndentDepth, aIndentString );
}

} // ypp_sm namespace
