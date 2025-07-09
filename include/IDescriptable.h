#pragma once

#include <string>

namespace ypp_sm
{

/**
 * @brief Interface for a descriptable class.
 */
class IDescriptable
{
public:
	//! Virtual destructor.
	virtual ~IDescriptable() = default;

	/**
	 * @brief Creates the textual description of the class.
	 * @param aIndentDepth Depth of the indentation.
	 * @param aIndentString String to indent with.
	 */
	std::string GetDescription( unsigned int aIndentDepth = 0, const std::string_view aIndentString = " " ) const noexcept;

private:
	/**
	 * @copydoc IDescriptable::GetDescription
	 */
	virtual std::string Description( unsigned int aIndentDepth, const std::string_view aIndentString ) const noexcept = 0;
};

} // ypp_sm namespace
