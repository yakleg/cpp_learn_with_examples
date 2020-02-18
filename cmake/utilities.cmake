# --------------------------- add_example function ---------------------------

function(add_example test_name test_file)
    get_filename_component(test_target_name "${test_file}" NAME_WE)

    add_executable("${test_target_name}" "")
    target_sources("${test_target_name}" PRIVATE "${test_file}")
    target_include_directories("${test_target_name}" PUBLIC ${INCLUDE_DIR})
    target_link_libraries("${test_target_name}" gtest gtest_main)
    set_property(TARGET "${test_target_name}" PROPERTY CXX_STANDARD 17)

    add_test(NAME ${test_name} COMMAND ${test_target_name})
endfunction(add_example)

# --------------------------- add_example function ---------------------------
