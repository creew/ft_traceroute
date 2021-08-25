/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:24:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 18:24:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static void reverse_dns(struct sockaddr_in *ip, socklen_t len)
{
	char	host[NI_MAXHOST];

	if (getnameinfo((struct sockaddr *)ip, len, host, NI_MAXHOST,
					NULL, 0, NI_NOFQDN) == 0)
	{
		printf(" %s (%s) ",host, inet_ntoa(ip->sin_addr));
	} else {
		printf(" %1$s (%1$s) ", inet_ntoa(((struct sockaddr_in *)ip)->sin_addr));
	}
}

static int recv_answer(const char *buf, struct timeval *start_time,
						int *host_printed) {
	ssize_t				n;
	struct sockaddr_in	recv_addr;
	fd_set				fdread;
	struct timeval		select_tv;

	select_tv.tv_sec = g_ft_traceroute.wait_probe_time;
	select_tv.tv_usec = 0;
	FD_ZERO(&fdread);
	FD_SET(g_ft_traceroute.recv_sock, &fdread);
	int select_result = select(FD_SETSIZE, &fdread, NULL, NULL, &select_tv);
	dlog("select_result: %d", select_result);

	if (select_result == 1) {
		socklen_t len = sizeof(recv_addr);
		n = recvfrom(g_ft_traceroute.recv_sock, (char *)buf, 1000,
					 0, (struct sockaddr *) &recv_addr, &len);
		dlog("recvfrom from: %s, %ld bytes ", inet_ntoa(recv_addr.sin_addr), n);
		struct icmphdr *icmp = (struct icmphdr *)(buf + sizeof(struct iphdr));
		if (icmp->type == ICMP_DEST_UNREACH && icmp->code == ICMP_PORT_UNREACH) {
			exit(0);
		}
		if (n < 0) {
			dlog("recvfrom error: %s, server: %s ", strerror(errno),
				 inet_ntoa(recv_addr.sin_addr));
		} else {
			if ((*host_printed) == 0) {
				reverse_dns(&recv_addr, len);
				*host_printed = 1;
			}
			printf(" %.3f ms ", tv_diff_millis(start_time));
		}
	} else {
		printf(" *");
	}
	return (0);
}

void send_request1()
{
	struct sockaddr_in	servaddr;
	size_t				size;
	int					max_length_hop;
	char				*buf;
	ssize_t				n;
	struct timeval		start_time;
	int					host_printed;
	int					i;

	prepare_socket();
	size = g_ft_traceroute.packet_size - sizeof(struct udphdr) - sizeof(struct iphdr);
	buf = ft_memalloc(1000);
	max_length_hop = calc_int_length(g_ft_traceroute.max_hops + 1);
	while (g_ft_traceroute.hop < g_ft_traceroute.max_hops)
	{
		g_ft_traceroute.ttl = g_ft_traceroute.hop + 1;
		set_ttl();
		ft_memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(g_ft_traceroute.port_number + g_ft_traceroute.hop);
		servaddr.sin_addr.s_addr = g_ft_traceroute.addr_info.sin_addr.s_addr;

		i = 0;
		host_printed = 0;
		while (i < g_ft_traceroute.number_of_queries) {
			if (i == 0) {
				printf("%*d ", max_length_hop, g_ft_traceroute.hop);
			}
			gettimeofday(&start_time, NULL);
			n = sendto(g_ft_traceroute.send_sock, buf, size,
					   0, (const struct sockaddr *) &servaddr,
					   	sizeof(servaddr));
			dlog("sent: %ld bytes", n);
			recv_answer(buf, &start_time, &host_printed);
			i++;
		}
		printf("\n");
		g_ft_traceroute.hop++;
	}
}
