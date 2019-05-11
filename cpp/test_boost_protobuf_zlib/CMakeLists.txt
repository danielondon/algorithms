find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Boost 1.51 REQUIRED)

protobuf_generate_cpp(protobuff_srcs protobuff_hdrs
  tripcommon.proto)

SET(TARGET test_boost_protobuf_zlib)
ADD_EXECUTABLE (${TARGET} ${TARGET}.cpp ${protobuff_srcs} ${protobuff_hdrs})

#if(Protobuf_FOUND)
#  include_directories(${PROTOBUF_INCLUDE_DIR})
#  target_link_libraries(${TARGET} ${PROTOBUF_LIBRARY})
#endif()

if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries(${TARGET} ${ZLIB_LIBRARIES})
endif( ZLIB_FOUND )