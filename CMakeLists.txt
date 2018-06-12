cmake_minimum_required(VERSION 3.10)
project(cpp_scrapper)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest/)

include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(cpp_scrapper main.cpp jsoncpp.cpp scrapper.cpp HtmlElement.cpp HtmlElement.h tests/HtmlElementTests.cpp HtmlParser.cpp HtmlParser.h)

target_link_libraries(cpp_scrapper gtest gtest_main)
target_link_libraries(cpp_scrapper gmock gmock_main)

find_package(CURL)
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(cpp_scrapper ${CURL_LIBRARIES})
endif()

