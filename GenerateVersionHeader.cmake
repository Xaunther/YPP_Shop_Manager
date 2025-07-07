file( READ "${VERSION_FILE}" YPP_SM_VERSION )
configure_file(${SRC} ${DST} @ONLY)
