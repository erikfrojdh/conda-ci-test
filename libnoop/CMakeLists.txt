
#Shared library
set(SOURCES
    src/noop.cpp
)
set(PUBLICHEADERS
    include/noop/noop.h
)
add_library(libnoop SHARED ${SOURCES})
target_include_directories(libnoop PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
find_package(fmt REQUIRED)
target_link_libraries(libnoop PRIVATE fmt::fmt)
set_target_properties(libnoop PROPERTIES
    LIBRARY_OUTPUT_NAME noop
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${PUBLICHEADERS}"
)

#executable
add_executable(noop app/main.cpp)
target_link_libraries(noop PRIVATE libnoop)
set_target_properties(noop PROPERTIES
    RUNTIME_OUTPUT_NAME noop
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    PUBLIC_HEADER "${PUBLICHEADERS}"
)
