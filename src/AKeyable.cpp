#include "AKeyable.h"

namespace ypp_sm
{

AKeyable::AKeyable( std::string_view aKey ) :
	mKey( aKey )
{
}

AKeyable::~AKeyable() = default;

std::string_view AKeyable::GetKey() const noexcept
{
	return mKey;
}

bool types::AKeyable::SKeyCompare::operator()( const ypp_sm::AKeyable& aLHS, const ypp_sm::AKeyable& aRHS ) const
{
	return aLHS < aRHS;
}

bool types::AKeyable::SKeyCompare::operator()( const ypp_sm::AKeyable& aLHS, const key_type& aRHS ) const
{
	return aLHS < aRHS;
}

bool types::AKeyable::SKeyCompare::operator()( const key_type& aLHS, const ypp_sm::AKeyable& aRHS ) const
{
	return aLHS < aRHS;
}

} // ypp_sm namespace
