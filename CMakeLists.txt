cmake_minimum_required(VERSION 3.16)
project(Metra2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml QuickControls2 Location Network)

# Add CURL and nlohmann_json
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

# Source files
# set(SOURCES
#     main.cpp
#     TrainFetcher.cpp
#     TrainModel.cpp
# )

# set(HEADERS
#     TrainFetcher.h
#     TrainModel.h
# )

# Add the executable
qt_add_executable(appMetra2
    main.cpp
)
# QML Module
qt_add_qml_module(appMetra2
    URI Metra2
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES trainmodel.h trainmodel.cpp
        SOURCES trainfetcher.h trainfetcher.cpp
)

# Link libraries
target_link_libraries(appMetra2
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Qml
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Location
    PRIVATE Qt6::Network
    PRIVATE CURL::libcurl
    PRIVATE nlohmann_json::nlohmann_json
)

include(GNUInstallDirs)
install(TARGETS appMetra2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
