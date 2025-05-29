############################ CONFIGURATION ####################################
cmake_minimum_required(VERSION 3.10)
project("zappy" VERSION 1.0 LANGUAGES ASM C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
###############################################################################



############################ LIBRARIES ########################################
# my_cpp
file(GLOB_RECURSE LIB_CPP_SOURCES "libs/my_cpp/src/*.cpp")
add_library(my_cpp ${LIB_CPP_SOURCES})
target_include_directories(my_cpp PUBLIC
        ${CMAKE_SOURCE_DIR}/libs/my_cpp/include
)

# my_c
file(GLOB_RECURSE LIB_C_SOURCES "libs/my_c/src/*.c")
file(GLOB_RECURSE LIB_ASM_SOURCES "libs/my_c/src/*.s")
set(ASM_OBJECTS "")
foreach(ASM_FILE ${LIB_ASM_SOURCES})
    get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
    set(ASM_OBJ "${CMAKE_BINARY_DIR}/${ASM_NAME}.o")
    add_custom_command(
        OUTPUT ${ASM_OBJ}
        COMMAND nasm -f elf64 -o ${ASM_OBJ} ${ASM_FILE}
        DEPENDS ${ASM_FILE}
        COMMENT "Assembling ${ASM_FILE} with NASM"
        VERBATIM
    )
    list(APPEND ASM_OBJECTS ${ASM_OBJ})
endforeach()
add_custom_target(my_c_asm_objs ALL DEPENDS ${ASM_OBJECTS})
add_library(my_c ${LIB_C_SOURCES} ${ASM_OBJECTS})
add_dependencies(my_c my_c_asm_objs)
target_include_directories(my_c PUBLIC
        ${CMAKE_SOURCE_DIR}/libs/my_c/include
)
###############################################################################



############################ AI ###############################################
set(AI "zappy_ai")
file(GLOB_RECURSE AI_SOURCES "ai/src/*.cpp")
add_executable(${AI} ${AI_SOURCES})
target_include_directories(${AI} PRIVATE
    ${CMAKE_SOURCE_DIR}/ai/include
)
target_link_libraries(${AI} PUBLIC my_cpp)
target_compile_options(${AI} PRIVATE -Wall -Wextra -Werror)
###############################################################################



############################ GUI ##############################################
set(GUI "zappy_gui")
file(GLOB_RECURSE GUI_SOURCES "gui/src/*.cpp")
add_executable(${GUI} ${GUI_SOURCES})
target_include_directories(${GUI} PRIVATE
    ${CMAKE_SOURCE_DIR}/gui/include
)
target_link_libraries(${GUI} PUBLIC my_cpp)
target_compile_options(${GUI} PRIVATE -Wall -Wextra -Werror)
###############################################################################



############################ SERVER ###########################################
set(SERVER "zappy_server")
file(GLOB_RECURSE SERVER_SOURCES "server/src/*.c")
add_executable(${SERVER} ${SERVER_SOURCES})
target_include_directories(${SERVER} PRIVATE
    ${CMAKE_SOURCE_DIR}/server/include
)
target_link_libraries(${SERVER} PUBLIC my_c)
target_compile_options(${SERVER} PRIVATE -Wall -Wextra -Werror -Wno-unused-result)
###############################################################################



############################ DEBUG MODE #######################################
OPTION(DEBUG_MODE "Option to build in debugging mode" OFF)

function(get_all_targets out_var)
    set(targets)
    get_all_targets_recursive(targets "${CMAKE_CURRENT_SOURCE_DIR}")
    set(${out_var} ${targets} PARENT_SCOPE)
endfunction()

function(get_all_targets_recursive targets_var dir)
    get_property(subdirectories DIRECTORY "${dir}" PROPERTY SUBDIRECTORIES)
    foreach(subdir IN LISTS subdirectories)
        get_all_targets_recursive("${targets_var}" "${subdir}")
    endforeach()

    get_property(current_targets DIRECTORY "${dir}" PROPERTY BUILDSYSTEM_TARGETS)
    set(${targets_var} ${${targets_var}} ${current_targets} PARENT_SCOPE)
endfunction()

get_all_targets(ALL_TARGETS)

if (DEBUG_MODE)
    message(STATUS "Debug mode enabled")
    foreach(target ${ALL_TARGETS})
        get_target_property(target_type ${target} TYPE)
        if(target_type STREQUAL "EXECUTABLE" OR
        target_type STREQUAL "STATIC_LIBRARY" OR
        target_type STREQUAL "SHARED_LIBRARY")
            target_compile_definitions(${target} PRIVATE -DDEBUG_MODE)
            target_compile_options(${target} PRIVATE -g3 -O3)
        endif()
    endforeach()
else()
    message(STATUS "Debug mode disabled")
    foreach(target ${ALL_TARGETS})
        get_target_property(target_type ${target} TYPE)
        if(target_type STREQUAL "EXECUTABLE" OR
        target_type STREQUAL "STATIC_LIBRARY" OR
        target_type STREQUAL "SHARED_LIBRARY")
            target_compile_options(${target} PRIVATE -O3)
        endif()
    endforeach()
endif()
###############################################################################



############################ CLEAN ALL ########################################
add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zappy_gui
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zappy_ai
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zappy_server
        COMMENT "Cleaning all build files"
)
###############################################################################



############################ DOCUMENTATION ####################################
find_package(Doxygen QUIET)

if(DOXYGEN_FOUND)
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating documentation with Doxygen"
    )
else()
    add_custom_target(doc
            COMMAND ${CMAKE_COMMAND} -E echo "Doxygen not found, documentation will not be generated"
    )
endif()
###############################################################################
