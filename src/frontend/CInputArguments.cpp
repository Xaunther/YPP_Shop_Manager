#include "frontend/CInputArguments.h"

namespace ypp_sm::frontend
{

CInputArguments::CInputArguments( const int&, const char** )
{
}

std::string_view CInputArguments::GetJSONFileName() const noexcept
{
	return mJSONFileName;
}

} // namespace ypp_sm::frontend
