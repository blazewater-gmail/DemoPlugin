cmake_minimum_required(VERSION 3.16)

set(module_name "Extra")
set(plugin_name "ExtraPlugin")

project(${module_name} VERSION 0.1 LANGUAGES CXX)

set(plugin_output_dir "${CMAKE_BINARY_DIR}/plugins/${module_name}")

qt_standard_project_setup(REQUIRES 6.5)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## https://doc.qt.io/qt-6/cmake-variable-qt-qml-output-directory.html
# set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

# add all source files
file(GLOB_RECURSE SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/styles/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/styles/*.cpp"
)

# add all component qml files
file(GLOB_RECURSE QML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/qml/*.qml"
    )

# Exclude the specific file (ExStyle.qml)
list(FILTER QML_FILES EXCLUDE REGEX "ExStyle\\.qml$")
# add all style qml files
file(GLOB_RECURSE STYLE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/qml/ExStyle.qml"
    )

# set style files as singleton
set_source_files_properties(${STYLE_FILES} PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

assign_qml_alias(${QML_FILES} ${STYLE_FILES})

qt_add_library(${plugin_name} SHARED)
set_target_properties(${plugin_name} PROPERTIES 
    # set .dll output directory
    RUNTIME_OUTPUT_DIRECTORY "${plugin_output_dir}"
    # set .lib output directory
    ARCHIVE_OUTPUT_DIRECTORY "${plugin_output_dir}"
    # set postfixes for debug, release, relwithdebinfo
    DEBUG_POSTFIX "d"
    RELEASE_POSTFIX ""
    RELWITHDEBINFO_POSTFIX "rd"
    MINSIZEREL_POSTFIX "mr"
)

set(build_types Debug Release RelWithDebInfo MinSizeRel)
foreach(bt ${build_types})
    string(TOUPPER ${bt} bt_upper)
    set_target_properties(${plugin_name} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY_${bt_upper} "${plugin_output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY_${bt_upper} "${plugin_output_dir}"
    )
    get_target_property( postfix_${bt} ${plugin_name} "${bt_upper}_POSTFIX")
    # replace dll name in qmldir file using a custom CMake script when building different configurations (debug, release, relwithdebinfo)
    string(APPEND 
        _cmd_update_qmldir
        "$<$<CONFIG:${bt}>:"
            "${CMAKE_COMMAND};-DMODULE_NAME=${plugin_name};-DOUTPUT_DIR=${plugin_output_dir};-DSUFFIX=${postfix_${bt}};-P;${CMAKE_SOURCE_DIR}/cmake/update_qmldir.cmake"
        ">"
    )
endforeach()

add_custom_command(TARGET ${plugin_name} POST_BUILD
    COMMAND "${_cmd_update_qmldir}"
    COMMENT "-- [$<CONFIG>]: replace dll name in qmldir file using a custom CMake script"
    COMMAND_EXPAND_LISTS
)
qt_add_qml_module(${plugin_name}
    URI ${module_name}
    VERSION 1.0
    PLUGIN_TARGET "${plugin_name}"
    # following line iscompatible with qt 6.2, 
    # if qt version is greater than 6.2, default value is "/qt/qml/", this line can be removed
    RESOURCE_PREFIX "/qt/qml/"
    OUTPUT_DIRECTORY "${plugin_output_dir}"
    SOURCES     ${SRC_FILES}
    QML_FILES   ${QML_FILES} ${STYLE_FILES}
    # DEPENDENCIES QtQuick
)

assign_source_group(${SRC_FILES} ${QML_FILES} ${STYLE_FILES})

target_link_libraries(${plugin_name} PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
)

target_compile_definitions(${plugin_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_include_directories(${plugin_name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/styles")

install(
    DIRECTORY ${plugin_output_dir}/ 
    DESTINATION plugins/${module_name}
    PATTERN "resources" EXCLUDE
    )
