cmake_minimum_required(VERSION 3.10)
project(hadith-viewer C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(JSON-C REQUIRED json-c)

include_directories(${GTK3_INCLUDE_DIRS} ${JSON-C_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${JSON-C_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER} ${JSON-C_CFLAGS_OTHER})

add_executable(hadith-viewer src/main.c)
target_link_libraries(hadith-viewer ${GTK3_LIBRARIES} ${JSON-C_LIBRARIES})
