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

	//! Pure virtual destructor
	virtual ~AKeyable() = 0;

	/**
	 * @brief Define comparison operators.
	 */
	auto operator<=>( const AKeyable& ) const = default;
	auto operator<=>( const key_type& aKey ) const{ return mKey <=> aKey; }

private:
	//! Key of the class.
	key_type mKey;
};

} // ypp_sm namespace
