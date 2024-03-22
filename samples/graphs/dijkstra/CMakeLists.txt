project(sample_dijkstra)

set(deps_folder "C:/deps")
set(SDL_FOLDER "C:/deps/SDL2-2.28.1")

if(MSVC)
	add_library(SDL2 SHARED IMPORTED GLOBAL SYSTEM)

	SET_PROPERTY(TARGET SDL2 
		PROPERTY IMPORTED_LOCATION ${SDL_FOLDER}/lib/x64/SDL2.dll)
	SET_PROPERTY(TARGET SDL2 
		PROPERTY IMPORTED_IMPLIB  ${SDL_FOLDER}/lib/x64/SDL2.lib)
	SET_PROPERTY(TARGET SDL2 
		PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SDL_FOLDER}/include)

	add_library(SDL2main SHARED IMPORTED GLOBAL SYSTEM)

	SET_PROPERTY(TARGET SDL2main 
		PROPERTY IMPORTED_IMPLIB  ${SDL_FOLDER}/lib/x64/SDL2main.lib)
	SET_PROPERTY(TARGET SDL2main 
		PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${SDL_FOLDER}/include)


	add_library(glad STATIC IMPORTED GLOBAL)
	SET_PROPERTY(TARGET glad 
		PROPERTY IMPORTED_LOCATION ${deps_folder}/libs/glad.lib)
	SET_PROPERTY(TARGET glad PROPERTY IMPORTED_IMPLIB ${deps_folder}/libs/glad.lib)
	SET_PROPERTY(TARGET glad PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${deps_folder}/glad/include)


else()
find_package(SDL2)
endif()

find_package(corgi-opengl CONFIG)
find_package(corgi-math CONFIG)

add_executable(sample_dijkstra src/main_dijkstra.cpp)

set_property(TARGET sample_dijkstra PROPERTY CXX_STANDARD 20)

target_link_libraries(sample_dijkstra PUBLIC ${CONAN_LIBS} corgi-algorithms corgi-math corgi-opengl glad  SDL2 SDL2main)

target_include_directories(sample_dijkstra PUBLIC ${CONAN_INCLUDE_DIRS})
