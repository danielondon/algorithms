SET(TARGET graphs)
ADD_EXECUTABLE (${TARGET} ${TARGET}.cpp)
target_link_libraries(${TARGET} gtest_main)
