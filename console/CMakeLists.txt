add_executable(QtWebAppConsole
    src/main.cpp
    src/global.cpp
    src/main.cpp
    src/requestmapper.cpp
    src/controller/dumpcontroller.cpp
    src/controller/fileuploadcontroller.cpp
    src/controller/formcontroller.cpp
    src/controller/sessioncontroller.cpp
    src/controller/templatecontroller.cpp)
target_compile_features(QtWebAppConsole PRIVATE cxx_auto_type)

target_link_libraries(QtWebAppConsole QtWebApp::QtWebApp)
