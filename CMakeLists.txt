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



############################ FUNCTIONS ########################################
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
###############################################################################



############################ LIBRARIES ########################################
# my_cpp
file(GLOB_RECURSE LIB_CPP_SOURCES "libs/my_cpp/src/*.cpp")
add_library(my_cpp ${LIB_CPP_SOURCES})
target_include_directories(my_cpp PUBLIC
    ${CMAKE_SOURCE_DIR}/libs/my_cpp/include
)
target_compile_options(my_cpp PUBLIC -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function)

# my_c
file(GLOB_RECURSE LIB_C_SOURCES "libs/my_c/src/*.c")
file(GLOB_RECURSE LIB_ASM_SOURCES "libs/my_c/src/*.s")
set(ASM_OBJECTS "")
foreach(ASM_FILE ${LIB_ASM_SOURCES})
    get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
    set(ASM_OBJ "${CMAKE_BINARY_DIR}/${ASM_NAME}.o")
    add_custom_command(
        OUTPUT ${ASM_OBJ}
        COMMAND nasm -f elf64 -fPIE -o ${ASM_OBJ} ${ASM_FILE}
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
target_compile_options(my_c PUBLIC -fPIE -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function)
###############################################################################



############################ AI ###############################################
set(AI "zappy_ai")
file(GLOB_RECURSE AI_SOURCES "ai/src/*.cpp")
add_executable(${AI} ${AI_SOURCES})
target_include_directories(${AI} PUBLIC
    ${CMAKE_SOURCE_DIR}/ai/include
)
target_link_libraries(${AI} PUBLIC my_cpp)
target_compile_options(${AI} PRIVATE -fPIE -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function)
###############################################################################



############################ GUI ##############################################
option(USE_LOCAL_RAYLIB "Force using local raylib instead of system package" OFF)

set(GUI "zappy_gui")
file(GLOB_RECURSE GUI_SOURCES "gui/src/*.cpp")
add_executable(${GUI} ${GUI_SOURCES})
target_include_directories(${GUI} PUBLIC
    ${CMAKE_SOURCE_DIR}/gui/include
    ${CMAKE_SOURCE_DIR}/gui/include/commands
    ${CMAKE_SOURCE_DIR}/gui/include/core
    ${CMAKE_SOURCE_DIR}/gui/include/graphical
)

if(USE_LOCAL_RAYLIB)
    message(STATUS "Forced to use local raylib")
    set(raylib_FOUND FALSE)
else()
    find_package(raylib QUIET)
endif()

if(raylib_FOUND)
    message(STATUS "Using system raylib package")
    target_link_libraries(${GUI} PUBLIC my_cpp raylib)
else()
    message(STATUS "Using local raylib from bonus/libs/raylib")

    if(EXISTS "${CMAKE_SOURCE_DIR}/bonus/libs/raylib/CMakeLists.txt")
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
        add_subdirectory(bonus/libs/raylib)
        target_link_libraries(${GUI} PUBLIC my_cpp raylib)
    else()
        message(FATAL_ERROR "Local raylib not found in bonus/libs/raylib/!")
    endif()
endif()

target_compile_options(${GUI} PRIVATE -fPIE -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-missing-field-initializers)
###############################################################################



############################ SERVER ###########################################
set(SERVER "zappy_server")
file(GLOB_RECURSE SERVER_SOURCES "server/src/*.c")
add_executable(${SERVER} ${SERVER_SOURCES})
target_include_directories(${SERVER} PUBLIC
    ${CMAKE_SOURCE_DIR}/server/include
)
target_link_libraries(${SERVER} PUBLIC my_c m)
target_compile_options(${SERVER} PRIVATE -fPIE -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function)
###############################################################################



############################ TESTS ############################################
function(create_unit_tests_target)
    find_package(PkgConfig QUIET)
    if(NOT PkgConfig_FOUND)
        message(FATAL_ERROR "PkgConfig not found - required for Criterion detection")
    endif()
    pkg_check_modules(CRITERION REQUIRED criterion)

    file(GLOB_RECURSE AI_LIB_SOURCES "ai/src/*.cpp")
    list(FILTER AI_LIB_SOURCES EXCLUDE REGEX ".*[Mm]ain\\.cpp$")
    if(AI_LIB_SOURCES)
        add_library(ai_lib ${AI_LIB_SOURCES})
        target_include_directories(ai_lib PUBLIC
                ${CMAKE_SOURCE_DIR}/ai/include
        )
        target_link_libraries(ai_lib PUBLIC my_cpp)
        target_compile_options(ai_lib PRIVATE -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function --coverage)
    endif()

    file(GLOB_RECURSE SERVER_LIB_SOURCES "server/src/*.c")
    list(FILTER SERVER_LIB_SOURCES EXCLUDE REGEX ".*[Mm]ain\\.c$")
    if(SERVER_LIB_SOURCES)
        add_library(server_lib ${SERVER_LIB_SOURCES})
        target_include_directories(server_lib PUBLIC
                ${CMAKE_SOURCE_DIR}/server/include
        )
        target_link_libraries(server_lib PUBLIC my_c m)
        target_compile_options(server_lib PRIVATE -Wall -Wextra -Werror -Wno-unused-result -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function --coverage)
    endif()

    file(GLOB_RECURSE TEST_SOURCES "tests/*.c")
    file(GLOB_RECURSE AI_TEST_SOURCES "tests/ai/*.cpp")
    file(GLOB_RECURSE SERVER_TEST_SOURCES "tests/server/*.c")

    set(ALL_TEST_SOURCES ${TEST_SOURCES} ${AI_TEST_SOURCES} ${SERVER_TEST_SOURCES})
    if(NOT ALL_TEST_SOURCES)
        message(FATAL_ERROR "No test sources found in tests/ai/ or tests/server/")
    endif()

    add_executable(unit_tests ${ALL_TEST_SOURCES})
    target_include_directories(unit_tests PRIVATE
            ${CMAKE_SOURCE_DIR}/tests
            ${CMAKE_SOURCE_DIR}/tests/ai
            ${CMAKE_SOURCE_DIR}/tests/server
    )
    set(TEST_LIBRARIES ${CRITERION_LIBRARIES} gcov)

    if(AI_LIB_SOURCES)
        target_include_directories(unit_tests PRIVATE
                ${CMAKE_SOURCE_DIR}/ai/include
        )
        list(APPEND TEST_LIBRARIES ai_lib)
    endif()
    if(SERVER_LIB_SOURCES)
        target_include_directories(unit_tests PRIVATE
                ${CMAKE_SOURCE_DIR}/server/include
        )
        list(APPEND TEST_LIBRARIES server_lib m)
    endif()

    target_link_libraries(unit_tests PRIVATE ${TEST_LIBRARIES})
    target_compile_options(unit_tests PRIVATE ${CRITERION_CFLAGS} --coverage)
    target_link_directories(unit_tests PRIVATE ${CRITERION_LIBRARY_DIRS})

    message(STATUS "Unit tests executable configured successfully")
endfunction()

create_unit_tests_target()

add_custom_target(tests_run
    DEPENDS unit_tests
    COMMENT "Running unit tests and generating coverage report"
    COMMAND ${CMAKE_COMMAND} -E echo "Running unit tests..."
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unit_tests --verbose
    COMMAND ${CMAKE_COMMAND} -E echo "Generating coverage report with gcovr..."
    COMMAND mkdir -p docs/tests
    COMMAND gcovr --branch --html --html-details docs/tests/test.html
    COMMAND gcovr
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
)
###############################################################################



############################ DEBUG MODE #######################################
OPTION(DEBUG_MODE "Option to build in debugging mode" OFF)

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
    COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unit_tests
    COMMENT "Cleaning all build files"
)
###############################################################################



############################ DOCUMENTATION ####################################
OPTION(DOC_ONLY "Build documentation only, skip all executables and libraries" OFF)

if(DOC_ONLY)
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
    
    return()
endif()
###############################################################################
