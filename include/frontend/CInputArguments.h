#pragma once

#include <string>

namespace ypp_sm::frontend
{

/**
 * @brief Class to read the input arguments for the shop manager executable.
 */
class CInputArguments
{
public:
	/**
	 * @brief Constructor from executable arguments.
	 * @param aArgsCount Argument count.
	 * @param aArgs Passed arguments.
	 */
	explicit CInputArguments( const int& aArgsCount, const char** aArgs );

	//! Retrieves the \copybrief mJSONFileName
	std::string_view GetJSONFileName() const noexcept;

private:
	//! JSON file name.
	std::string mJSONFileName;
};

} // namespace ypp_sm::frontend
