cmake_minimum_required(VERSION 3.22)
project(minishell01 C)

#set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-lreadline -L /usr/local/opt/readline/lib/ -I /usr/local/opt/readline/include/")

include_directories(.)
include_directories(libft)

add_executable(token
        tokenize.c)

add_executable(minishell
        main.c
        minishell.h
        signal_handle.c
        tokenize.c
        env_handle.c
        tokenize.c
        make_tree.c
        tree_parser.c
        quote.c
        execute.c
        utils.c
        builtin_pwd.c
        builtin_env.c
        builtin_export.c
        builtin_cd.c
        builtin_echo.c
        test.c
        )
