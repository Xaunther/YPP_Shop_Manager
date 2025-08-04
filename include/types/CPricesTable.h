#pragma once

#include <optional>

/**
 * @brief Types defined for \ref CPricesTable.
*/
namespace ypp_sm::types::CPricesTable
{

//! Type for a price.
using price = float;

//! Type for an optional price.
using optional_price = std::optional<price>;

//! Type for an integer price.
using int_price = unsigned int;

} // ypp_sm::types::CPricesTable namespace
