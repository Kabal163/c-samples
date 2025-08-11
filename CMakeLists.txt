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

add_executable(fancy_str fancy_str.c ${SHARED_SRCS})
target_compile_definitions(fancy_str PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(fancy_str PRIVATE -fsanitize=address -g)
target_link_options(fancy_str PRIVATE -fsanitize=address)

add_executable(mussad mussad.c ${SHARED_SRCS})
target_compile_definitions(mussad PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(mussad PRIVATE -fsanitize=address -g)
target_link_options(mussad PRIVATE -fsanitize=address)

add_executable(hv_count hv_count.c ${SHARED_SRCS})
target_compile_definitions(hv_count PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(hv_count PRIVATE -fsanitize=address -g)
target_link_options(hv_count PRIVATE -fsanitize=address)

add_executable(mos_count mos_count.c ${SHARED_SRCS})
target_compile_definitions(mos_count PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_options(mos_count PRIVATE -fsanitize=address -g)
target_link_options(mos_count PRIVATE -fsanitize=address)

add_executable(fruits_into_baskets fruits_into_baskets.c)
target_compile_definitions(fruits_into_baskets PRIVATE $<$<CONFIG:Debug>:DEBUG>)
#target_compile_options(fruits_into_baskets PRIVATE -fsanitize=address -g)
#target_link_options(fruits_into_baskets PRIVATE -fsanitize=address)

add_executable(9999 9999.c)
target_compile_definitions(9999 PRIVATE $<$<CONFIG:Debug>:DEBUG>)
