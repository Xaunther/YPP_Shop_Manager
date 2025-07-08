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

	//! Default name for the JSON file.
	static constexpr std::string DEFAULT_JSON_FILE_NAME = "db.json";

	//! Retrieves the \copybrief mJSONFileName
	std::string_view GetJSONFileName() const noexcept;

private:
	//! JSON file name.
	std::string mJSONFileName;
	//! Whether the program is going to run or just quit.
	bool mRun = true;
};

} // namespace ypp_sm::frontend
