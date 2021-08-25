/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 15:31:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 15:31:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

#include "libft.h"

#include <unistd.h>
#include <netdb.h>

#include "get_addr.h"

typedef struct s_ft_traceroute {
    char		is_icmp;
	char		is_debug;
    int			send_sock;
	int			recv_sock;
	char 		*exec_name;
	char		*host;
	int 		hop;
	int 		ttl;
	int			max_hops;
	int			number_of_queries;
	int			wait_probe_time;
	int			port_number;
	int			packet_size;
	t_addr_info	addr_info;
} t_ft_traceroute;

typedef struct s_arg_function{
	char arg;
	int (*parse_function)(int argc, char *argv[], char *arg, int *i);
	char *desc;
} t_arg_function;

extern t_ft_traceroute g_ft_traceroute;

enum e_errors
	{
	RUN_UNDER_NOT_ROOT,
	ERROR_CREATING_SOCKET,
	CANNOT_SET_SIGNAL,
	CANNOT_SET_TTL,
	CANNOT_SET_IP_RECVERR,
	CANNOT_SET_RCVTIMEO,
	UNKNOWN_HOST,
	INVALID_FIRST_HOP,
	INVALID_MAX_HOPS,
	INVALID_NUMBER_OF_QUERIES,
	INVALID_WAIT_PROBE_TIME,
	INVALID_PORT_NUMBER,
	INVALID_TTL,
	INVALID_INTERVAL,
	OPTION_REQUIRED,
	INVALID_SIZE_OF_PACKETS,
	NO_MEMORY,
	ICMP_ERR,
	OK = 0
	};

void	dlog(char *fmt, ...);
int		parse_argv(int argc, char *argv[]);
char	*parse_joined_option(int argc, char *const *argv, char *arg, int *i);
void	print_usage(char *arg, int code);
void	err_fmt(int code, char *fmt, ...);
void	err_fmt_usage(char *fmt, ...);
void	send_request1();
void	prepare_socket(void);
void	set_ttl();
int		calc_int_length(int i);
long	tv_diff_micro(struct timeval *start);
float	tv_diff_millis(struct timeval *start);
#endif
