#pragma once

#include <functional>
#include <string_view>
#include <vector>

namespace ypp_sm
{

class CDataBase;

namespace frontend
{

/**
 * @brief Interface class for a menu.
 */
class IMenuSelector
{
public:
	//! Virtual destructor.
	virtual ~IMenuSelector() = default;

public:
	/**
	 * @brief Runs the menu
	 * @param aDataBase Database to work with.
	 * @param aJSONFileName Name of the JSON file
	 */
	void operator()( CDataBase& aDataBase, std::string_view aJSONFileName );

private:
	//! Prints the menu.
	void PrintMenu();

	/**
	 * @brief Asks the user for a valid input.
	 * @return The chosen option index.
	 */
	//! Asks the user for a valid input.
	unsigned int HandleInput();

	//! Retrieves the introductory text.
	virtual constexpr std::string_view GetIntro() const noexcept = 0;

	//! Retrieves the posible options.
	virtual constexpr std::vector<std::string_view> GetOptions() const noexcept = 0;

	/**
	 * @brief Retrieves the posible operations.
	 * @details The operation returns whether the menu keeps going or not.
	 */
	virtual std::vector<std::function<bool( CDataBase&, std::string_view )>> GetOperations() const noexcept = 0;
};

} // namespace frontend

} // namespace ypp_sm
