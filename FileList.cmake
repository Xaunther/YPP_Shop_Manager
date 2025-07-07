# Core external headers
SET(YPP_SM_CORE_EXTERNAL_HEADERS
	include/IJsonable.h
	include/JsonUtils.h
	include/traits/default.h
	include/traits/json.h
	include/types/IJsonable.h
)

# Core source files
SET(YPP_SM_CORE_SOURCE
	src/IJsonable.cpp
)

# External headers
SET(YPP_SM_EXTERNAL_HEADERS
	${YPP_SM_CORE_EXTERNAL_HEADERS}
)
