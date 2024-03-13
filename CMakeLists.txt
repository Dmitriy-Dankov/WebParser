cmake_minimum_required(VERSION 3.16)

project(WebParser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appWebParser
    main.cpp
)

qt_add_qml_module(appWebParser
    URI WebParser
    VERSION 1.0
    QML_FILES main.qml
              My_Window.qml
              My_Button.qml
              My_Input.qml
              Scroll_TextEdit.qml
              Top_Block.qml
              Left_Block.qml
              Bottom_Block.qml
              Win_Image.qml
              Win_Text.qml
              Win_Block.qml
              Properties_Dialog.qml
              My_Message_Box.qml

    SOURCES   Parser.h Parser.cpp
              ToolsEditsOfText.h ToolsEditsOfText.cpp
              ServerRequest.h ServerRequest.cpp
              Download.h Download.cpp
              DataForVisualElements.h DataForVisualElements.cpp
              InfoMessages.h InfoMessages.cpp
              Dataset.h Dataset.cpp
              TextFilters.h TextFilters.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWebParser PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWebParser
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWebParser
    PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(TARGETS appWebParser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
