#pragma once

#include "IMenuSelector.h"
#include "CKeySets.h"

#include "InputUtils.h"
#include "frontend/CSetMenuSelector.h"

namespace ypp_sm::frontend
{

/**
 * @brief Class to manage the key sets class menu options.
 */
template <typename T>
class CKeySetsMenuSelector : public IMenuSelector<CKeySets<T>&>
{
	using operations = IMenuSelector<CKeySets<T>&>::operations;

	//! Retrieves the introductory text.
	constexpr std::string GetIntro() const noexcept override;

	//! Retrieves the posible options.
	constexpr std::vector<std::string> GetOptions() const noexcept override;

	//! Retrieves the posible operations.
	operations GetOperations() const noexcept override;
};

template <typename T>
constexpr std::string CKeySetsMenuSelector<T>::GetIntro() const noexcept
{
	return "Choose option";
}

template <typename T>
constexpr std::vector<std::string> CKeySetsMenuSelector<T>::GetOptions() const noexcept
{
	return {
		"Back",
		"List categories",
		"Add category",
		"Remove category",
		"Modify category",
	};
}

template <typename T>
CKeySetsMenuSelector<T>::operations CKeySetsMenuSelector<T>::GetOperations() const noexcept
{
	return {
		[]( const CKeySets<T>& ){ return false; },
		[]( const CKeySets<T>& aKeySets ){ std::cout << aKeySets.GetDescription(); return true; },
		[]( CKeySets<T>& aKeySets ){ aKeySets.KeySets()[ AskInput<std::string>( "Category:" ) ]; return true; },
		[]( CKeySets<T>& aKeySets ){ aKeySets.KeySets().erase( AskInput<std::string>( "Category:" ) ); return true; },
		[]( CKeySets<T>& aKeySets )
			{
				const auto found = aKeySets.KeySets().find( AskInput<std::string>( "Category:" ) );
				if( found != aKeySets.KeySets().end() )
					CSetMenuSelector<T>{}( (*found).second );
				return true;
			},
	};
}

} // namespace ypp_sm::frontend

