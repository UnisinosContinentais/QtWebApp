cmake_minimum_required(VERSION 3.5)
project(QtWebApp VERSION 1.0.0 LANGUAGES CXX)

add_definitions(-DMAKE_QTWEBAPP_LIB)

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
find_package(Qt5 COMPONENTS Core Network CONFIG REQUIRED )
find_package(OpenMP)

##############################################
# Create target and set properties

qt5_wrap_cpp(QtWebApp_MOC_SRCS
    include/httpserver/httpconnectionhandler.h
    include/httpserver/httpconnectionhandlerpool.h
    include/httpserver/httplistener.h
    include/httpserver/httprequesthandler.h
    include/httpserver/httpsessionstore.h
    include/httpserver/staticfilecontroller.h
    include/logging/filelogger.h
    include/logging/logger.h
    include/templateengine/templatecache.h
    include/templateengine/templateloader.h
)

add_library(QtWebApp
    src/httpserver/httpconnectionhandler.cpp
    src/httpserver/httpconnectionhandlerpool.cpp
    src/httpserver/httpcookie.cpp
    src/httpserver/httplistener.cpp
    src/httpserver/httprequest.cpp
    src/httpserver/httprequesthandler.cpp
    src/httpserver/httpresponse.cpp
    src/httpserver/httpsession.cpp
    src/httpserver/httpsessionstore.cpp
    src/httpserver/staticfilecontroller.cpp
    src/logging/dualfilelogger.cpp
    src/logging/filelogger.cpp
    src/logging/logger.cpp
    src/logging/logmessage.cpp
    src/qtservice/qtservice.cpp
    src/qtservice/qtservice.pri
#    src/qtservice/qtservice_unix.cpp
    src/qtservice/qtservice_win.cpp
#    src/qtservice/qtunixserversocket.cpp
#    src/qtservice/qtunixsocket.cpp
    src/templateengine/template.cpp
    src/templateengine/templatecache.cpp
    src/templateengine/templateloader.cpp

    ${QtWebApp_MOC_SRCS}
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(QtWebApp::QtWebApp ALIAS QtWebApp)

#Set target properties
target_include_directories(QtWebApp
    PUBLIC
       $<INSTALL_INTERFACE:include>
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(QtWebApp PRIVATE cxx_auto_type)
target_compile_options(QtWebApp PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

target_link_libraries(QtWebApp
    PUBLIC Qt5::Core
    PUBLIC Qt5::Network
    PUBLIC OpenMP::OpenMP_CXX
)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/QtWebApp)

install(TARGETS QtWebApp
    EXPORT QtWebApp-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name QtWebApp and not QtWebApp
set_target_properties(QtWebApp PROPERTIES EXPORT_NAME QtWebApp)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT QtWebApp-targets
  FILE
    QtWebAppTargets.cmake
  NAMESPACE
    QtWebApp::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/QtWebAppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
# configure_file(
#     ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#     ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#     COPYONLY)

export(EXPORT QtWebApp-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/QtWebAppTargets.cmake NAMESPACE QtWebApp::)

add_subdirectory(console)
