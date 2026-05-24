cmake_minimum_required(VERSION 3.16)

project(dlg-filelister LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dlg-filelister main.cpp
    filelister.h)

include(GNUInstallDirs)
install(TARGETS dlg-filelister
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
