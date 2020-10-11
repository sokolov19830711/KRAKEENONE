cmake_minimum_required(VERSION 3.0.0)

project(KRAKEENONE VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5SerialPort)

add_executable(${PROJECT_NAME} WIN32  "appIcon.rc"
								"PrimeboxWidgets/OnOffButton.cpp" "PrimeboxWidgets/ButtonGroup.cpp" "PrimeboxWidgets/SpinBox.cpp"
								"PrimeboxWidgets/SensorInicator.cpp" "PrimeboxWidgets/SwitchButtonsWidget.cpp"
								"main.cpp" "mainwidget.cpp" "serialportmanager.cpp" "frame.cpp" "mainframe.cpp" "functionsframe.cpp"
								"aboutframe.cpp" "temperatureframe.cpp" "dustframe.cpp" "breakinframe.cpp" "vibrationframe.cpp" 
								"positionframe.cpp" "moistureframe.cpp" "powerframe.cpp" "runninghoursframe.cpp" "ibuttonframe.cpp"
								"enterpasswordframe.cpp" )

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Network)
target_link_libraries(${PROJECT_NAME} Qt5::SerialPort)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SMTPEmail.lib)
