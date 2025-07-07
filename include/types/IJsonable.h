#pragma once

#include <nlohmann/json_fwd.hpp>

/**
 * @brief Types defined for \ref IJsonable.
*/
namespace ypp_sm::types::IJsonable
{

//! Type for the json object.
using json = nlohmann::ordered_json;

} // ypp_sm::types::IJsonable namespace
