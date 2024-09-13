
message(STATUS "checking file existed: ${OUTPUT_DIR}/${MODULE_NAME}${SUFFIX}.dll")
file(GLOB dll_file "${OUTPUT_DIR}/${MODULE_NAME}${SUFFIX}.dll")

# Check if dll files were found
if(dll_file)
    message(STATUS "${dll_file} Found")
else()
    message(STATUS "${dll_file} Not Found")
    return()
endif()

file(READ ${OUTPUT_DIR}/qmldir file_contents)

set(modified_file_contents "")
set(old "optional plugin ${MODULE_NAME}m?r?d?\n")
set(replaced_with "optional plugin ${MODULE_NAME}${SUFFIX}\n")
string(REGEX MATCH ${old} _out ${file_contents})
message(STATUS "result of match ${old}: ${_out}")

if ("${_out}" STREQUAL "")
    string(APPEND file_contents ${replaced_with})
    set(modified_file_contents ${file_contents})
else()
    string(REGEX REPLACE "${old}"
        "${replaced_with}"
        modified_file_contents
        "${file_contents}")
endif()

file(WRITE ${OUTPUT_DIR}/qmldir "${modified_file_contents}")

