cmake_minimum_required(VERSION 3.13)
project(ft_traceroute C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(libft)

include_directories(
        libft/includes
        includes)

add_executable(ft_traceroute
        srcs/parse_arg.c
        srcs/logger.c
        srcs/usage.c
        srcs/socket.c
        srcs/ft_traceroute.c
        srcs/get_addr.c
        srcs/options/parse_option_m.c
        srcs/options/parse_option_f.c
        srcs/options/parse_option_q.c
        srcs/options/parse_option_w.c
        srcs/options/parse_option_h.c
        srcs/options/parse_option_v.c
        srcs/options/parse_option_I.c
        srcs/options/parse_option_p.c
        srcs/send_request.c
        srcs/utils.c)
target_link_libraries(ft_traceroute ft)
