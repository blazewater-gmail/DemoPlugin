cmake_minimum_required(VERSION 3.16)

message(STATUS "Common cmake include")
# Function to assign QML file aliases for Qt resources
# This function sets the QT_RESOURCE_ALIAS property for each QML file to its base name
# Useful for simplifying QML import paths in Qt projects
# Parameters:
#   ARGN: List of QML file paths to process

function(assign_qml_alias)
    foreach(_source IN ITEMS ${ARGN})
        if(${_source} MATCHES "\\.qml$")
            if (IS_ABSOLUTE "${_source}")
                set(_source_abs ${_source})
            else()
                file(REAL_PATH ${_source} _source_abs BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
            endif()
            get_filename_component(qml_file_name ${_source_abs} NAME)
            set_source_files_properties(${_source_abs} PROPERTIES QT_RESOURCE_ALIAS ${qml_file_name})
        endif()
    endforeach()
endfunction()

# Function to assign file aliases for Qt resources
# This function sets the QT_RESOURCE_ALIAS property for each file to its base name
# Useful for simplifying resource paths in Qt projects
# Parameters:
#   ARGN: List of file paths to process
function(assign_file_alias)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            set(_source_abs ${_source})
        else()
            file(REAL_PATH ${_source} _source_abs BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        endif()
        get_filename_component(qml_file_name ${_source_abs} NAME)
        set_source_files_properties(${_source_abs} PROPERTIES QT_RESOURCE_ALIAS ${qml_file_name})
    endforeach()
endfunction()

# Function to assign source files to groups in IDEs like Visual Studio
# This function organizes files into folders in the IDE's solution explorer
# It also handles both absolute and relative paths
# Parameters:
#   ARGN: List of source files to organize
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
            set(_source_abs ${_source})
        else()
            file(REAL_PATH ${_source} _source_abs BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        source_group("${_source_path}" FILES "${_source_abs}")
        # if(${_source_abs} MATCHES "\\.qml$")
        #     get_filename_component(qml_file_name ${_source_abs} NAME)
        #     set_source_files_properties(${_source_abs} PROPERTIES QT_RESOURCE_ALIAS ${qml_file_name})
        # endif()
    endforeach()
endfunction()
