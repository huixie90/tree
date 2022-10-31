#  +--------+
#  |  TREE  |
#  +--------+
file(GLOB_RECURSE tree_hdr  RELATIVE ${CMAKE_SOURCE_DIR} tree/include/*.hpp)
add_library(tree INTERFACE) # header-only library
target_sources(tree INTERFACE ${tree_hdr})
target_include_directories(tree INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)
