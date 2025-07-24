#pragma once

#include "IDescriptable.h"
#include "IJsonable.h"

namespace ypp_sm
{

/**
 * @brief Class for a table of different prices for an item.
 */
class CPricesTable : public IJsonable, public IDescriptable
{
};

} // namespace ypp_sm
