cmake_minimum_required(VERSION 3.25)
project(mybench C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SHARED_SRCS lib_time.c)

add_executable(lat_syscall lat_syscall.c ${SHARED_SRCS})
target_compile_definitions(lat_syscall PRIVATE $<$<CONFIG:Debug>:DEBUG>)

add_executable(lat_ctxswtch lat_ctxswtch.c ${SHARED_SRCS})
target_compile_definitions(lat_ctxswtch PRIVATE $<$<CONFIG:Debug>:DEBUG>)

add_executable(sqrt sqrt.c ${SHARED_SRCS})
target_compile_definitions(sqrt PRIVATE $<$<CONFIG:Debug>:DEBUG>)