cmake_minimum_required (VERSION 3.20.3)
project (tree_traverser CXX)

# enable MSVC specific multi-processor compilation option

if (MSVC)
   set(CMAKE_CXX_STANDARD 23)
   # prevent MSVC/clang incompatible MP flag
   add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
   set(CXX_STANDARD_REQUIRED TRUE)
	add_compile_options(-Wall -Wextra -Werror -stdlib=libc++ -std=c++2b)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   set(CXX_STANDARD_REQUIRED TRUE)
	add_compile_options(-Wall -Wextra -Werror -std=c++2b)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
endif()

add_subdirectory (tree)
add_subdirectory (test)
