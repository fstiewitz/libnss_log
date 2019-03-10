cmake_minimum_required(VERSION 3.10)
project(libnss_log C)

set(CMAKE_C_STANDARD 90)

add_library(nss_log SHARED library.c)
target_compile_options(nss_log PRIVATE -Wall -Wextra -pedantic)
set_target_properties(nss_log PROPERTIES SOVERSION 2)

install(TARGETS nss_log
        LIBRARY DESTINATION lib)
install(TARGETS nss_log DESTINATION /lib)
