# Core external headers
SET(YPP_SM_CORE_EXTERNAL_HEADERS
	include/AKeyable.h
	include/CRecipeItem.h
	include/ExceptionUtils.h
	include/IJsonable.h
	include/JsonUtils.h
	include/NumberUtils.h
	include/traits/default.h
	include/traits/json.h
	include/types/CRecipes.h
	include/types/CRecipeItem.h
	include/types/IJsonable.h
)

# Core source files
SET(YPP_SM_CORE_SOURCE
	src/AKeyable.cpp
	src/CRecipeItem.cpp
	src/IJsonable.cpp
)

# External headers
SET(YPP_SM_EXTERNAL_HEADERS
	${YPP_SM_CORE_EXTERNAL_HEADERS}
)
