#pragma once

#include "types/AKeyable.h"

namespace ypp_sm
{

/**
 * @brief Abstract class for an object that may be used as key.
 */
class AKeyable
{
protected:
	using key_type = types::AKeyable::key_type;

public:
	/**
	 * @brief Member constructor.
	 * @param aKey \copybrief mKey
	 */
	AKeyable( std::string_view aKey );

	//! Retrieves the \copybrief mKey
	std::string_view GetKey() const noexcept;

private:
	//! Key of the class.
	key_type mKey;
};

} // ypp_sm namespace
