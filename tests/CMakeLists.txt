add_test(
        NAME valid_empty_object
        COMMAND cpp_json_parser
        "${CMAKE_CURRENT_SOURCE_DIR}/step1/valid.json"
)

add_test(
        NAME invalid_incomplete_object
        COMMAND cpp_json_parser
        "${CMAKE_CURRENT_SOURCE_DIR}/step1/invalid.json"
)

add_test(
        NAME invalid_chars_outside_braces
        COMMAND cpp_json_parser
        "${CMAKE_CURRENT_SOURCE_DIR}/step1/invalid2.json"
)

set_tests_properties(
        invalid_incomplete_object
        invalid_chars_outside_braces
        PROPERTIES WILL_FAIL TRUE
)