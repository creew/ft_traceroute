/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 15:37:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 15:37:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "ft_traceroute.h"

void	prepare_socket(void)
{
	g_ft_traceroute.recv_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (g_ft_traceroute.recv_sock < 0 ) {
		err_fmt(ERROR_CREATING_SOCKET, "recv socket creation failed %s", strerror(errno));
	}
	if (g_ft_traceroute.is_icmp) {
		g_ft_traceroute.send_sock = g_ft_traceroute.recv_sock;
	} else {
		g_ft_traceroute.send_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (g_ft_traceroute.send_sock < 0 ) {
			err_fmt(ERROR_CREATING_SOCKET, "send socket creation failed %s", strerror(errno));
		}
	}
}

void	set_ttl() {
	if (setsockopt(g_ft_traceroute.send_sock, SOL_IP, IP_TTL,
				   &g_ft_traceroute.ttl, sizeof(g_ft_traceroute.ttl)) != 0)
	{
		err_fmt(CANNOT_SET_TTL, "%s: can't set unicast time-to-live: %s",
				g_ft_traceroute.exec_name, strerror(errno));
	}
}