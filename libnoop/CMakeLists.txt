
#Shared library
# Add a custom command that produces version.cpp, plus
# a dummy output that's not actually produced, in order
# to force version.cmake to always be re-run before the build
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
           ${CMAKE_CURRENT_BINARY_DIR}/_version.cpp
    COMMAND ${CMAKE_COMMAND} -P
            ${PROJECT_SOURCE_DIR}/cmake/version.cmake)

message(STATUS "bin2:${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "src:${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCES
    src/noop.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
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
target_link_libraries(libnoop PRIVATE fmt::fmt project_warnings project_options)
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


install(TARGETS libnoop noop
    EXPORT "${TARGETS_EXPORT_NAME}"
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/noop
)
