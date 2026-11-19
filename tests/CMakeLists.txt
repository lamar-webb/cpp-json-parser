# Valid empty JSON object should return 0
add_test(
        NAME valid_empty_object
        COMMAND cpp_json_parser
        "${CMAKE_CURRENT_SOURCE_DIR}/step1/valid.json"
)

# Invalid JSON or empty JSON file should return nonzero
add_test(
        NAME invalid_incomplete_object
        COMMAND cpp_json_parser
        "${CMAKE_CURRENT_SOURCE_DIR}/step1/invalid.json"
)

set_tests_properties(
        invalid_incomplete_object
        PROPERTIES WILL_FAIL TRUE
)