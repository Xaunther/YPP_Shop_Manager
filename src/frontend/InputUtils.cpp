#include "frontend/InputUtils.h"

namespace ypp_sm::frontend
{

template <> unsigned int DEFAULT_CONVERSION( const std::string& aInput )
{
	return std::stoul( aInput );
}

template <> float DEFAULT_CONVERSION( const std::string& aInput )
{
	return std::stof( aInput );
}

} //namespace ypp_sm::frontend

