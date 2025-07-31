#pragma once

#include "IMenuSelector.h"

#include <concepts>
#include <set>
#include <string>

#include "CKeySets.h"
#include "CPricesTable.h"
#include "CRecipe.h"

#include "InputUtils.h"
#include "types/AKeyable.h"
#include "types/CDataBase.h"

namespace ypp_sm
{

class IDescriptable;

namespace frontend
{

/**
 * @brief Class to manage the key sets class menu options.
 */
template <typename T> requires std::derived_from<T, IDescriptable>
class CSetMenuSelector : public IMenuSelector<std::set<T,types::AKeyable::SKeyCompare>&, const CKeySets<T>&>
{
	using operations = IMenuSelector<std::set<T,types::AKeyable::SKeyCompare>&, const CKeySets<T>&>::operations;
	using set_type = std::set<T,types::AKeyable::SKeyCompare>;

	//! Retrieves the introductory text.
	constexpr std::string GetIntro() const noexcept override;

	//! @copydoc IMenuSelector::GetOptions
	constexpr std::vector<std::string> GetOptions() const noexcept override;

	//! Retrieves the posible operations.
	operations GetOperations() const noexcept override;

	//! Retrieve the string representing the element in singular.
	constexpr std::string GetSingularElementName() const noexcept;

	//! Retrieve the string representing the element in plural.
	constexpr std::string GetPluralElementName() const noexcept;
};

template <typename T> requires std::derived_from<T, IDescriptable>
constexpr std::string CSetMenuSelector<T>::GetSingularElementName() const noexcept
{
	return "element";
}

template <>
constexpr std::string CSetMenuSelector<CRecipe>::GetSingularElementName() const noexcept
{
	return "recipe";
}

template <>
constexpr std::string CSetMenuSelector<CPricesTable>::GetSingularElementName() const noexcept
{
	return "price";
}

template <typename T> requires std::derived_from<T, IDescriptable>
constexpr std::string CSetMenuSelector<T>::GetPluralElementName() const noexcept
{
	return GetSingularElementName() + "s";
}

template <typename T> requires std::derived_from<T, IDescriptable>
constexpr std::string CSetMenuSelector<T>::GetIntro() const noexcept
{
	return "Choose option";
}

template <typename T> requires std::derived_from<T, IDescriptable>
constexpr std::vector<std::string> CSetMenuSelector<T>::GetOptions() const noexcept
{
	return {
		"Back",
		"List " + GetPluralElementName(),
		"Add or modify " + GetSingularElementName(),
		"Remove " + GetSingularElementName(),
	};
}

template <typename T> requires std::derived_from<T, IDescriptable>
CSetMenuSelector<T>::operations CSetMenuSelector<T>::GetOperations() const noexcept
{
	return {
		[]( const set_type&, const CKeySets<T>& ){ return false; },
		[]( const set_type& aSet, const CKeySets<T>& ){ for( const auto& element : aSet ) std::cout << element.GetDescription(); return true; },
		[&]( set_type& aSet, const CKeySets<T>& aKeySets )
			{
				auto inputElement = AskInput<T>( "Item:" );
				if( aSet.extract( inputElement ) || !aKeySets.Contains( inputElement ) )
					aSet.emplace( std::move( inputElement ) );
				else
					std::cout << "\nItem " << inputElement.GetKey() << " was not added because it already exists in a different category.\n";
				return true;
			},
		[&]( set_type& aSet, const CKeySets<T>& )
			{
				const auto found = aSet.find( AskInput<types::AKeyable::key_type>( "Item:" ) );
				if( found != aSet.cend() )
					aSet.erase( found );
				return true;
			},
	};
}

} // namespace frontend

} // namespace ypp_sm

