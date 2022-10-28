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

# git clone Catch2, cmake & install to $INSTALL.
# set Catch2_DIR in this project to $INSTALL/lib/cmake/Catch2
find_package(Catch2 3 REQUIRED)

#  +--------+
#  |  TREE  |
#  +--------+
file(GLOB_RECURSE tree_hdr  RELATIVE ${CMAKE_SOURCE_DIR} tree/*.hpp)
add_library(tree INTERFACE) # header-only library
target_sources(tree INTERFACE ${tree_hdr})


#  +-------------+
#  |  TREE-TEST  |
#  +-------------+

file(GLOB_RECURSE tree_test_src RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  tree/test/*.cpp)
add_executable(tree-test)
target_sources(tree-test PRIVATE ${tree_test_src})
target_link_libraries(tree-test PRIVATE Catch2::Catch2WithMain)
target_include_directories(tree-test PRIVATE tree)
