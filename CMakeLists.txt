cmake_minimum_required(VERSION 3.10)
project(cpp_scrapper)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_scrapper main.cpp jsoncpp.cpp scrapper.cpp tv_show.h tv_show.cpp movie.cpp movie.h media.h)

find_package(CURL)
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(cpp_scrapper ${CURL_LIBRARIES})
endif()

