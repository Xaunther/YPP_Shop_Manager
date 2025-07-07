#include "ATest.h"

#include "AKeyable.h"

#include <set>

using namespace ypp_sm;

INITIALIZE_TEST( TAKeyable )

void TAKeyable::TestExceptions()
{
}

std::vector<std::string> TAKeyable::ObtainedResults() noexcept
{
	std::vector<std::string> result;

	class CKeyable : public AKeyable{ using AKeyable::AKeyable; };
	for( const auto& keyable : std::set{
		CKeyable{ "White paint" },
		CKeyable{ "White paint" },
		CKeyable{ "Red paint" },
		CKeyable{ "Wood" },
		} )
	{
		result.emplace_back( keyable.GetKey() );
	}

	return result;
}

std::vector<std::string> TAKeyable::ExpectedResults() noexcept
{
	return {
		"Red paint",
		"White paint",
		"Wood",
	};
}
