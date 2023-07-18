
add_executable(sample_dijkstra src/main_dijkstra.cpp)

find_package(corgi-opengl CONFIG)

set_property(TARGET sample_dijkstra PROPERTY CXX_STANDARD 20)

target_link_libraries(sample_dijkstra PUBLIC ${CONAN_LIBS} corgi-algorithms corgi-opengl)

target_include_directories(sample_dijkstra PUBLIC ${CONAN_INCLUDE_DIRS})
