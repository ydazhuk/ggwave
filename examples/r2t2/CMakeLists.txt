add_executable(r2t2 main.cpp)

target_include_directories(r2t2 PRIVATE
    ..
    ${SDL2_INCLUDE_DIRS}
    )

target_link_libraries(r2t2 PRIVATE
    ggwave
    ggwave-common
    ${CMAKE_THREAD_LIBS_INIT}
    )
