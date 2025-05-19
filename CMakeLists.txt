cmake_minimum_required(VERSION 3.16)

project(rclCreator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport Xml)

set(PROJECT_SOURCES
        main.cpp
        launchwindow.cpp
        launchwindow.h
        launchwindow.ui
        boot/property.h
        boot/property.cpp

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(rclCreator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        boot/property.h
        boot/property.cpp



        gui/resume/resumetabwidget.h gui/resume/resumetabwidget.cpp gui/resume/resumetabwidget.ui
        gui/resume/qualification/resumequalificationsection.h gui/resume/qualification/resumequalificationsection.cpp gui/resume/qualification/resumequalificationsection.ui
        gui/resume/qualification/resumequalificationsubsection.h gui/resume/qualification/resumequalificationsubsection.cpp gui/resume/qualification/resumequalificationsubsection.ui
        gui/resume/qualification/resumesubsectiondetail.h gui/resume/qualification/resumesubsectiondetail.cpp gui/resume/qualification/resumesubsectiondetail.ui
        gui/gui_utils.h
        gui/gui_utils.cpp
        gui/deletablewidget.h gui/deletablewidget.cpp
        gui/resume/header/resumeheaderpane.h gui/resume/header/resumeheaderpane.cpp gui/resume/header/resumeheaderpane.ui
        gui/resume/header/headertextelement.h gui/resume/header/headertextelement.cpp gui/resume/header/headertextelement.ui
        gui/shiftablewidget.h gui/shiftablewidget.cpp
        gui/resume/header/headerelement.h gui/resume/header/headerelement.cpp
        gui/resume/header/headerlinkelement.h gui/resume/header/headerlinkelement.cpp gui/resume/header/headerlinkelement.ui
        gui/resume/qualification/qualificationpane.h gui/resume/qualification/qualificationpane.cpp gui/resume/qualification/qualificationpane.ui
        gui/coverletter/coverlettertab.h gui/coverletter/coverlettertab.cpp gui/coverletter/coverlettertab.ui
        gui/resizeeventfilter.h gui/resizeeventfilter.cpp
        gui/coverletter/property/propertiespane.h gui/coverletter/property/propertiespane.cpp gui/coverletter/property/propertiespane.ui
        gui/coverletter/property/property.h gui/coverletter/property/property.cpp gui/coverletter/property/property.ui
        gui/coverletter/preamble/preamblepane.h gui/coverletter/preamble/preamblepane.cpp gui/coverletter/preamble/preamblepane.ui
        gui/coverletter/experience/experiencepane.h gui/coverletter/experience/experiencepane.cpp gui/coverletter/experience/experiencepane.ui
        gui/coverletter/experience/experience.h gui/coverletter/experience/experience.cpp gui/coverletter/experience/experience.ui
        gui/import/jobimportdialog.h gui/import/jobimportdialog.cpp gui/import/jobimportdialog.ui
        job/jobspecifications.h job/jobspecifications.cpp
        keyword/keyword.h keyword/keyword.cpp
        keyword/keywordmanager.h keyword/keywordmanager.cpp
        keyword/keywordlistener.h keyword/keywordlistener.cpp
        gui/keyword/keywordmanagergui.h gui/keyword/keywordmanagergui.cpp gui/keyword/keywordmanagergui.ui
        gui/keyword/keyworddisplay.h gui/keyword/keyworddisplay.cpp gui/keyword/keyworddisplay.ui
        keyword/keywordowner.h
        keyword/keywordowner.cpp
        gui/keyword/keywordassociationpopup.h gui/keyword/keywordassociationpopup.cpp gui/keyword/keywordassociationpopup.ui
        gui/keyword/keywordassociation.h gui/keyword/keywordassociation.cpp gui/keyword/keywordassociation.ui





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET rclCreator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(rclCreator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(rclCreator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(rclCreator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/resume
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/coverletter
)

message(STATUS "Include directories: ${CMAKE_INCLUDE_DIRECTORIES}")

target_link_libraries(rclCreator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Core Qt6::PrintSupport Qt6::Xml)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.rclCreator)
endif()
set_target_properties(rclCreator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS rclCreator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(rclCreator)
endif()
