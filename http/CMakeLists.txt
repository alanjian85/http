set(HTTP_SRCS
    src/main.cc
    src/server.cc
    src/server.h)
add_executable(http ${HTTP_SRCS})

find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(http
    ${Boost_LIBRARIES}
    Threads::Threads
)