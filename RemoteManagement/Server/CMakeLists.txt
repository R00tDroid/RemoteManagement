file(GLOB_RECURSE SourceFiles
    ${CMAKE_CURRENT_LIST_DIR}/Source/*.*
)

file(GLOB_RECURSE ResourceFiles
    ${CMAKE_CURRENT_LIST_DIR}/Resources/*.*
)

cmrc_add_resource_library(ServerResources ALIAS Server::rc ${ResourceFiles})

add_executable(Server
    ${SourceFiles}
)

target_link_libraries(Server
    Server::rc
)
