
set(TEST_DEPENDENCIES
        FileCheck
        AllOpsProfile
        ReplaceMultiply
   )


# create a `check` target to run the tests
#add_custom_target(check
#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/start-lit.py "${CMAKE_CURRENT_BINARY_DIR}" -v
#        DEPENDS ${TEST_DEPENDENCIES}
#        )

# We replace the above with an extended function - add_lit_testsuite(), this is why we `include(AddLLVM)`
# add_lit_testsuite() is aCMake function defined inside the file 'AddLLVM.cmake' located at $LLVM_DIR/lib/cmake/llvm
# it uses the 'add_custom_target()' to create 'check-*' targets for the lit test-suites found in the given directory
# **It is here that the variable $LLVM_EXTERNAL_LIT is used,  see 'get_llvm_lit_path()' in AddLLVM.cmake**
add_lit_testsuite(check-llvmpasses "Running lit 'regression' tests on my llvm passes"
        ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${TEST_DEPENDENCIES}
        )
set_target_properties(check-llvmpasses PROPERTIES FOLDER "Tests") # tell IDEs to put this target inside "/Tests"

configure_file(lit.site.cfg.py.in lit.site.cfg.py @ONLY)

# We replace the above with an extended function - configure_lit_site_cfg()
# configure_lit_site_cfg() is also defined inside AddLLVM.cmake.
# It takes its arguments in pairs: "site_in" and "site_out". e.g. MAIN_CONFIG should have been set to an input file
# normally that would be './lit.cfg.py' if it is empty as it is the function assumes normalcy. The next argument
# denote to target file to be generated from the MAIN_CONFIG
#configure_lit_site_cfg(
#        ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
#        ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
#        MAIN_CONFIG
#        ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
#)
#
