/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 15:39:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 15:39:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

t_ft_traceroute g_ft_traceroute;

void	alrm_handler(int sig)
{
	(void)sig;
}

void	int_handler(int sig)
{
	(void)sig;
	exit(0);
}

void init_traceroute(char *argv[])
{
	char *last_slash;

	last_slash = ft_strrchr(argv[0], '/');
	ft_memset(&g_ft_traceroute, 0, sizeof(t_ft_traceroute));
	if (last_slash == NULL)
		g_ft_traceroute.exec_name = argv[0];
	else
		g_ft_traceroute.exec_name = last_slash + 1;
	g_ft_traceroute.max_hops = 30;
	g_ft_traceroute.number_of_queries = 3;
	g_ft_traceroute.ttl = 1;
	g_ft_traceroute.wait_probe_time = 5;
}


void print_header()
{
	char addr[256];

	inet_ntop(AF_INET, &g_ft_traceroute.addr_info.sin_addr,
			  addr, sizeof(addr) - 1);
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
		   g_ft_traceroute.host, addr, g_ft_traceroute.max_hops, 60);
}

int main(int argc, char *argv[])
{
	init_traceroute(argv);
	parse_argv(argc, argv);
	if (g_ft_traceroute.host == NULL)
		print_usage(g_ft_traceroute.exec_name,2);
	if (get_addr(g_ft_traceroute.host, &g_ft_traceroute.addr_info) != 0)
		err_fmt(UNKNOWN_HOST, "%s: %s: Name or service not known\n",
				argv[0], g_ft_traceroute.host);
	if (signal(SIGALRM, alrm_handler) == SIG_ERR)
		err_fmt(CANNOT_SET_SIGNAL, "cannot set signal: %d", SIGALRM);
	if (signal(SIGINT, int_handler) == SIG_ERR)
		err_fmt(CANNOT_SET_SIGNAL, "cannot set signal: %d", SIGINT);
	print_header();
	send_request(g_ft_traceroute.ttl);
    return 0;
}
