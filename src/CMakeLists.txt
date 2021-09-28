set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Network WebKitWidgets NetworkAuth REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    httpclient.cpp
    oauthdialog.cpp
    mainwindow.cpp
    constants.h
    weibotimelineview.cpp
    weibotimelinemodel.cpp
    weibotimelinedelegate.cpp
    weibotimeline.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt5::Widgets
        Qt5::Network
        Qt5::WebKitWidgets
        Qt5::NetworkAuth
)
