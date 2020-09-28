cmake_minimum_required(VERSION 3.5)
project(ContinentalFuzzy VERSION 1.0.0 LANGUAGES CXX)

add_definitions(-DMAKE_CONTINENTALFUZZY_LIB)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Load custom configuration file for CMake (if any).
if(EXISTS ${CMAKE_SOURCE_DIR}/CMakeLists.config)
    include(${CMAKE_SOURCE_DIR}/CMakeLists.config)
endif()

#Make sure that custom modules like FindRapidJSON are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Declare dependencies
find_package(Qt5Core CONFIG REQUIRED)

find_package(OpenMP)

##############################################
# Create target and set properties

add_library(ContinentalFuzzy
    src/Version.cpp
    src/service/fuzzy/FuzzyService.cpp
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(ContinentalFuzzy::ContinentalFuzzy ALIAS ContinentalFuzzy)

#Set target properties
target_include_directories(ContinentalFuzzy
    PUBLIC
       $<INSTALL_INTERFACE:include>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(ContinentalFuzzy PRIVATE cxx_auto_type)
target_compile_options(ContinentalFuzzy PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

target_link_libraries(ContinentalFuzzy
    PUBLIC Qt5::Core
    PUBLIC OpenMP::OpenMP_CXX
)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ContinentalFuzzy)

install(TARGETS ContinentalFuzzy
    EXPORT ContinentalFuzzy-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name ContinentalFuzzy and not ContinentalFuzzy
set_target_properties(ContinentalFuzzy PROPERTIES EXPORT_NAME ContinentalFuzzy)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT ContinentalFuzzy-targets
  FILE
    ContinentalFuzzyTargets.cmake
  NAMESPACE
    ContinentalFuzzy::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ContinentalFuzzyConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ContinentalFuzzyConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ContinentalFuzzyConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ContinentalFuzzyConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ContinentalFuzzyConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
# configure_file(
#     ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#     ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#     COPYONLY)

export(EXPORT ContinentalFuzzy-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/ContinentalFuzzyTargets.cmake NAMESPACE ContinentalFuzzy::)

add_subdirectory(test)
add_subdirectory(console)
