cmake_minimum_required(VERSION 3.13)
project(msCLion C)

include_directories("libft/includes" "includes")

set (SOURCES ./srcs/flags.c
        ./srcs/make.c
        ./srcs/ft_errno.c
        ./srcs/check.c
        ./srcs/env_make.c
        ./srcs/parse.c
        ./srcs/print.c
        ./srcs/shell.c
        ./srcs/autocom.c
        ./builtins/cd/cd.c
        ./builtins/echo/echo.c
        ./builtins/env/env.c
        ./builtins/setenv/setenv.c
        ./builtins/unsetenv/unsetenv.c)

add_executable(main main.c ${SOURCES})

target_link_libraries(main ${CMAKE_SOURCE_DIR}/libft/libft.a)