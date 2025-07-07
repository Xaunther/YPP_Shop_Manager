#pragma once

#include "ExceptionUtils.h"

namespace ypp_sm
{

/**
 * @brief Checks non-negativeness of a number.
 * @param aNumber Number to check.
 * @param aNumberDescription Number description to add to the error message.
*/
const auto& CheckNonNegativeness( const auto& aNumber, const std::string_view aNumberDescription ) try
{
	if( aNumber < decltype( aNumber ){} )
		throw std::invalid_argument{ "The " + std::string( aNumberDescription.data() ) + " cannot be negative." };
	return aNumber;
}
YPP_SM_CATCH_AND_RETHROW_EXCEPTION( std::invalid_argument, "Error checking the " << aNumberDescription << "." )

} // ypp_sm namespace
