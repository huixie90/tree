#  +-------------+
#  |  TREE-TEST  |
#  +-------------+


# git clone Catch2, cmake & install to $INSTALL.
# set Catch2_DIR in this project to $INSTALL/lib/cmake/Catch2
find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE tree_test_src  ${CMAKE_SOURCE_DIR}   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(tree-test)
target_sources(tree-test PRIVATE ${tree_test_src})
target_link_libraries(tree-test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tree-test PUBLIC tree)
