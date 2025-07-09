#pragma once

#include "IMenuSelector.h"

namespace ypp_sm::frontend
{

/**
 * @brief Class to read manage the main menu options.
 */
class CMainMenuSelector : public IMenuSelector
{
	//! Retrieves the introductory text.
	constexpr std::string_view GetIntro() const noexcept override;

	//! Retrieves the posible options.
	constexpr std::vector<std::string_view> GetOptions() const noexcept override;

	//! Retrieves the posible operations.
	std::vector<std::function<bool( CDataBase&, std::string_view )>> GetOperations() const noexcept override;
};

} // namespace ypp_sm::frontend
