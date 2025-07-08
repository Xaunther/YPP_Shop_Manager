#include "frontend/CInputArguments.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>

namespace ypp_sm::frontend
{

namespace
{

template <typename T> struct is_optional : std::false_type {};
template <typename T> struct is_optional<std::optional<T>> : std::true_type {};

template <typename T> std::enable_if_t<is_optional<T>::value, T>
GetArgument( const int& aArgsCount, const char** aArgs, const std::string_view aFlag );

template <typename T> std::enable_if_t<!is_optional<T>::value, T>
GetArgument( const int& aArgsCount, const char** aArgs, const std::string_view aFlag, const T& aDefaultValue = T{} );

void ShowHelp();

}

CInputArguments::CInputArguments( const int& aArgsCount, const char** aArgs ) :
	mJSONFileName( GetArgument( aArgsCount, aArgs, "-f", DEFAULT_JSON_FILE_NAME ) )
{
	const auto end = aArgs + aArgsCount;
	if( std::find( aArgs, end, std::string_view{ "-h" } ) != end )
	{
		ShowHelp();
		mRun = false;
	}
}

std::string_view CInputArguments::GetJSONFileName() const noexcept
{
	return mJSONFileName;
}

bool CInputArguments::WillRun() const noexcept
{
	return mRun;
}

namespace
{

template <typename T> std::enable_if_t<is_optional<T>::value, T> GetArgument( const int& aArgsCount, const char** aArgs, const std::string_view aFlag )
{
	const auto end = aArgs + aArgsCount;
	return ( std::find( aArgs, end, aFlag ) != end ) ? GetArgument<typename T::value_type>( aArgsCount, aArgs, aFlag ) : T();
}

template <typename T> std::enable_if_t<!is_optional<T>::value, T> GetArgument( const int& aArgsCount, const char** aArgs, const std::string_view aFlag, const T& aDefaultValue )
{
	const auto end = aArgs + aArgsCount;
	auto found = std::find( aArgs, end, aFlag );
	if( found != end && ++found != end )
	{
		std::stringstream ss;
		T result;
		ss << *found;
		ss >> result;
		return result;
	}
	return aDefaultValue;
}

void ShowHelp()
{
	std::cout << "Options\n";
	std::cout << "  -f <filename>            = Specifies the JSON file name (default: " << CInputArguments::DEFAULT_JSON_FILE_NAME << ").\n";
	std::cout << "  -h                       = Shows this help.\n";
}

}

} // namespace ypp_sm::frontend
