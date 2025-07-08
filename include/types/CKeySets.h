#pragma once

#include "AKeyable.h"

#include <map>
#include <set>
#include <concepts>

/**
 * @brief Types defined for \ref CKeySets.
*/
namespace ypp_sm
{

class AKeyable;

namespace types::CKeySets
{

//! Concept for a type inheriting from AKeyable
template<typename T> concept is_keyable = std::derived_from<T, ypp_sm::AKeyable>;

//! Type for the sets classified by some key.
template <is_keyable T> using key_sets = std::map<AKeyable::key_type, std::set<T>>;

} // types::CKeySets namespace

} // ypp_sm namespace
