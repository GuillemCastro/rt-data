cmake_minimum_required(VERSION 3.1)
project(rtdata)

# The version number.
set (rtdata_VERSION_MAJOR 0)
set (rtdata_VERSION_MINOR 1)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wimplicit-fallthrough=0")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -Wimplicit-fallthrough=0")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(libs/nlohmann_json)
add_subdirectory(libs/SQLiteCpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
find_package(CppUnit REQUIRED)

find_package(Threads REQUIRED)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 

find_package(GPSD REQUIRED)

find_package(g3logger)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

include_directories(src)

include_directories(libs/SQLiteCpp/include)

file(GLOB SRC_FILES  src/*.cpp src/concurrent/*.cpp src/time/*.cpp src/serialization/*.cpp src/utils/*.cpp src/io/*.cpp src/sensors/*.cpp src/control/*.cpp)

add_library( rtdata STATIC ${SRC_FILES} )

target_link_libraries(rtdata
    cppunit
    Threads::Threads
    nlohmann_json::nlohmann_json
    SQLiteCpp
    sqlite3
    gps
    curl
    dl
)

install (TARGETS rtdata DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/rtdata FILES_MATCHING PATTERN "*.h")

option(WITH_LOGGING "Support logging" ON)
IF(g3logger_FOUND AND WITH_LOGGING)
    message(STATUS "Adding logging support")
    target_link_libraries(rtdata g3logger)
    add_definitions(-DWITH_G3LOG)
ELSE()
    message(WARNING "Logging disabled!" )
ENDIF()

option(BUILD_TESTS "Build the tests" ON)
IF(BUILD_TESTS)
    IF(NOT(MSVC OR MINGW))
        include_directories(${CPPUNIT_INCLUDE_DIR})
        include_directories(test)
        include_directories(libs/SQLiteCpp/include)
        file(GLOB TEST_FILES test/*.cpp)
        add_executable(rtdata_test ${TEST_FILES})
        target_link_libraries(rtdata_test
            cppunit
            Threads::Threads
            nlohmann_json::nlohmann_json
            SQLiteCpp
            sqlite3
            dl
            rtdata
            pthread
        )
        IF(g3logger_FOUND AND WITH_LOGGING)
            target_link_libraries(rtdata_test g3logger)
        ENDIF()
    ENDIF()
ENDIF()

option(BUILD_INTEGRATION_TESTS "Build the integration tests" OFF)
IF(BUILD_INTEGRATION_TESTS)
    include_directories(test/integration)
    include_directories(libs/SQLiteCpp/include)
    file(GLOB INTEGRATION_TEST_FILES test/integration/*.cpp)
    foreach( testsourcefile ${INTEGRATION_TEST_FILES} )
        string( REPLACE ".cpp" "" testname ${testsourcefile} )
        get_filename_component(test_executable ${testname} NAME)
        add_executable( ${test_executable} ${testsourcefile} )
        target_link_libraries(${test_executable}
            cppunit
            Threads::Threads
            nlohmann_json::nlohmann_json
            SQLiteCpp
            sqlite3
            dl
            rtdata
        )
    endforeach( testsourcefile ${APP_SOURCES} )
ENDIF()

option(BUILD_DOCS "Build documentation" OFF)
find_package(Doxygen)
if (DOXYGEN_FOUND AND BUILD_DOCS)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
endif (DOXYGEN_FOUND AND BUILD_DOCS)

option(EXECUTE_TESTS "Execute the tests" OFF)
if (EXECUTE_TESTS)
    add_custom_target(
        tests
        ALL
        COMMAND rtdata_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Executing tests" VERBATIM
    )
ENDIF()

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${rtdata_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${rtdata_VERSION_MINOR}")
set (CPACK_PACKAGE_CONTACT "guillem.castro@cosmicresearch.org")
include (CPack)