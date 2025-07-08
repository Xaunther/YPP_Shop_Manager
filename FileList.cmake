# Core external headers
SET(YPP_SM_CORE_EXTERNAL_HEADERS
	include/AKeyable.h
	include/CKeyItem.h
	include/CKeySets.h
	include/CRecipe.h
	include/ExceptionUtils.h
	include/IJsonable.h
	include/JsonUtils.h
	include/NumberUtils.h
	include/traits/CRecipe.h
	include/traits/default.h
	include/traits/json.h
	include/types/CDataBase.h
	include/types/CKeySets.h
	include/types/CRecipe.h
	include/types/IJsonable.h
)

# Frontend external headers
SET(YPP_SM_FRONTEND_EXTERNAL_HEADERS
	include/frontend/CInputArguments.h
)

# Core source files
SET(YPP_SM_CORE_SOURCE
	src/AKeyable.cpp
	src/CRecipe.cpp
	src/IJsonable.cpp
)


# Frontend source files
SET(YPP_SM_FRONTEND_SOURCE
	src/frontend/CInputArguments.cpp
)

# External headers
SET(YPP_SM_EXTERNAL_HEADERS
	${YPP_SM_CORE_EXTERNAL_HEADERS}
	${YPP_SM_FRONTEND_EXTERNAL_HEADERS}
)
