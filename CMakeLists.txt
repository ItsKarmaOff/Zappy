cmake_minimum_required(VERSION 3.10)

project("zappy" VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# For my standard library
file(GLOB STANDARD_LIB "utils/src/*.cpp")
add_library(my ${STANDARD_LIB})
target_include_directories(my PUBLIC
        ${CMAKE_SOURCE_DIR}/utils/include
)


############################ GUI #######################################
set(GUI "zappy_gui")
file(GLOB GUI_SOURCES "gui/src/*.cpp")
add_executable(${GUI} ${GUI_SOURCES})
target_include_directories(${GUI} PRIVATE
    ${CMAKE_SOURCE_DIR}/gui/include
)
target_link_libraries(${GUI} PUBLIC my)

########################################################################

############################ AI #######################################
set(AI "zappy_ai")
file(GLOB AI_SOURCES "ai/src/*.cpp")
add_executable(${AI} ${AI_SOURCES})
target_include_directories(${AI} PRIVATE
    ${CMAKE_SOURCE_DIR}/ai/include
)
target_link_libraries(${AI} PUBLIC my)

#######################################################################

############################ SERVER ####################################
set(SERVER "zappy_server")
file(GLOB SERVER_SOURCES "server/src/*.cpp")
add_executable(${SERVER} ${SERVER_SOURCES})
target_include_directories(${SERVER} PRIVATE
    ${CMAKE_SOURCE_DIR}/server/include
)
target_link_libraries(${SERVER} PUBLIC my)
#######################################################################


OPTION(DEBUG_MODE "Option to build in debugging mode" OFF)
if (DEBUG_MODE)
    message(STATUS "Debug mode enabled")
    foreach(target ${EXECUTABLE_NAME} my ${GUI} ${SERVER} ${AI})
        target_compile_definitions(${target} PRIVATE -DDEBUG_MODE)
        target_compile_options(${target} PRIVATE -g3)
    endforeach()
endif()

add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zappy_gui
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zappy_ai
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zappy_server
        COMMENT "Cleaning all build files"
)

find_package(Doxygen REQUIRED)
add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
)
