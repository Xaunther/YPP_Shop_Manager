#pragma once

#include <string>

/**
 * @brief Types defined for \ref AKeyable.
*/
namespace ypp_sm
{

class AKeyable;

namespace types::AKeyable
{

//! Type for the internal key type.
using key_type = std::string;

/**
 * @brief Define key comparison operators.
 */
struct SKeyCompare
{
	using is_transparent = void;
	/**
	 * @brief Define comparisons for the class.
	 * @{
	 */
	bool operator()( const ypp_sm::AKeyable& aLHS, const ypp_sm::AKeyable& aRHS ) const;
	bool operator()( const ypp_sm::AKeyable& aLHS, const key_type& aRHS ) const;
	bool operator()( const key_type& aLHS, const ypp_sm::AKeyable& aRHS ) const;
	/**
	 * @}
	 */
};

} // ypp_sm

} // types::AKeyable namespace
