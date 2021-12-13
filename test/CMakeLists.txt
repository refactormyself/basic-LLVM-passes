
set(TEST_DEPENDENCIES
        AllOpsProfile
        ReplaceMultiply
   )

configure_file(lit.site.cfg.py.in lit.site.cfg.py @ONLY)

# create a `check` target to run the tests
add_custom_target(check
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/start-lit.py "${CMAKE_CURRENT_BINARY_DIR}" -v
        DEPENDS ${TEST_DEPENDENCIES}
        )