cmake_minimum_required(VERSION 3.16)

project(DemoMain VERSION 0.1 LANGUAGES CXX)

set(target_name demo)
set(uri_name demo)

set(dev_base_dir "D:/develop")
set(qt_version "6.7.2" CACHE STRING "Qt Version")
set(qt_base_dir "${dev_base_dir}/qt/${qt_version}/msvc2019_64")

set(QT6_DIR ${qt_base_dir})
set(CMAKE_PREFIX_PATH "")
list(APPEND CMAKE_PREFIX_PATH "${qt_base_dir}")

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick Qml)

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
endif()

qt_standard_project_setup(REQUIRES 6.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE CMAKE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake")
file(GLOB_RECURSE HDR_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    )
file(GLOB_RECURSE SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE FONTS_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/resources/fonts/*")

add_subdirectory(modules/Extra)

qt_add_executable(${target_name}
    ${HDR_FILES}
    ${SRC_FILES}
    ${CMAKE_FILES} # just for display cmake file in vs ide;
    ${FONTS_FILES}
)

file(GLOB_RECURSE QML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/resources/qml/*.qml")

assign_qml_alias(${QML_FILES})

qt_add_qml_module(${target_name}
    URI ${uri_name}
    VERSION 1.0
    # following line is compatible with qt 6.2, 
    # if qt version is greater than 6.2, default value is "/qt/qml/", this line can be removed
    RESOURCE_PREFIX "/qt/qml/" 
    # NO_RESOURCE_TARGET_PATH
    QML_FILES ${QML_FILES}
)

#[[
# add module's qml files as resources
# else cannot using "qrc:/" to access modules'qml(embedded in plugin dll) files in main app
file(GLOB_RECURSE QML_FILES_MODULE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/Extra/resources/qml/*.qml")
assign_qml_alias(${QML_FILES_MODULE})
qt_target_qml_sources(${target_name}
    PREFIX "/qt/qml/Extra/resources/qml/"
    QML_FILES   ${QML_FILES_MODULE}
)
# add all image files(icons, etc)
file(GLOB_RECURSE IMAGE_FILES_MODULE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/Extra/resources/icons/*.png")
assign_file_alias(${IMAGE_FILES_MODULE})
qt_target_qml_sources(${target_name}
    PREFIX "/qt/qml/Extra/resources/icons/"
    RESOURCES ${IMAGE_FILES_MODULE}
)
assign_source_group(${QML_FILES_MODULE} ${IMAGE_FILES_MODULE})
]]

assign_source_group(${CMAKE_FILES} ${SRC_FILES} ${HDR_FILES} ${QML_FILES} ${FONTS_FILES})

set_target_properties(${target_name} PROPERTIES
    WIN32_EXECUTABLE TRUE
    VS_DEBUGGER_ENVIRONMENT "PATH=${qt_base_dir}/bin;%PATH%"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)

target_link_options(${target_name} PRIVATE
    $<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>
    $<$<NOT:$<CONFIG:Debug>>:/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${target_name})

target_include_directories(${target_name}
    PUBLIC include
)

# if no dependency or adding link library to target_link_libraries, ExtraPlugin will not be built when building ${target_name}
add_dependencies(${target_name} ExtraPlugin) 

target_link_libraries(${target_name}
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS ${target_name}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

message(STATUS "Generating deploy script for ${target_name} (Qt ${qt_version})")
if (${qt_version} VERSION_GREATER_EQUAL 6.7.2)
    set(var_name OUTPUT_SCRIPT)
else()
    set(var_name FILENAME_VARIABLE)
endif()
qt_generate_deploy_qml_app_script(
    TARGET ${target_name}
    ${var_name} deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)

install(SCRIPT ${deploy_script})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/fonts/ DESTINATION resources/fonts)
