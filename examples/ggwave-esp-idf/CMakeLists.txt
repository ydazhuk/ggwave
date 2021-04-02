# set(TARGET ggwave-esp-idf)

# add_executable(${TARGET} main.cpp)

# target_include_directories(${TARGET} PRIVATE
    
#     )

# target_link_libraries(${TARGET} PRIVATE
#     ggwave
#     ${CMAKE_THREAD_LIBS_INIT}
#     )
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ggwave)