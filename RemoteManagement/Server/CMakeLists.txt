file(GLOB_RECURSE SourceFiles
    ${CMAKE_CURRENT_LIST_DIR}/Source/*.*
)

file(GLOB_RECURSE ResourceFiles
    ${CMAKE_CURRENT_LIST_DIR}/Resources/*.*
)

cmrc_add_resource_library(ServerResources ALIAS Server::rc ${ResourceFiles})

CPMAddPackage("gh:Stiffstream/restinio#v.0.6.17")
CPMAddPackage("gh:chriskohlhoff/asio#asio-1-24-0")
CPMAddPackage("gh:fmtlib/fmt#9.1.0")
CPMAddPackage(NAME httpparser
    GITHUB_REPOSITORY nodejs/http-parser
    VERSION 2.9.4
)

add_library(http_parser STATIC
    ${httpparser_SOURCE_DIR}/http_parser.c
)

if (MSVC)
    target_compile_options(http_parser PUBLIC /WX- /W1)
else()
    target_compile_options(http_parser PUBLIC -w)
endif()

add_executable(Server
    ${SourceFiles}
)

target_compile_features(Server PRIVATE cxx_std_17)

target_include_directories(Server PUBLIC
    ${restinio_SOURCE_DIR}/dev
    ${asio_SOURCE_DIR}/asio/include
    ${httpparser_SOURCE_DIR}
)

target_link_libraries(Server
    Server::rc
    fmt
    http_parser
)

if (UNIX)
    find_package(Threads)
    target_link_libraries(Server ${CMAKE_THREAD_LIBS_INIT})
endif()
