#Reusing parts of: https://github.com/cpp-best-practices/cpp_starter_project/

cmake_minimum_required(VERSION 3.12)
project(noop CXX)
set(PROJECT_VERSION 0.1.0)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")


include(GNUInstallDirs)

if($ENV{CONDA_BUILD})
  set(CMAKE_INSTALL_LIBDIR "lib")
endif()

string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

#Link to add warnings
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Link to add settings
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)


message(STATUS "install: ${CMAKE_INSTALL_INCLUDEDIR}")

# Install fake the libraries
install(TARGETS project_options project_warnings
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# Add a custom command that produces version.cpp, plus
# a dummy output that's not actually produced, in order
# to force version.cmake to always be re-run before the build
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
           ${CMAKE_CURRENT_BINARY_DIR}/_version.cpp
    COMMAND ${CMAKE_COMMAND} -P
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake)


message(STATUS "bin:${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(libnoop)