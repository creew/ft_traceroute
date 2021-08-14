/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_icmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 16:37:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 16:37:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

#include <errno.h>

void	prepare_socket(void)
{
	struct timeval	timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	g_ft_traceroute.sock = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (g_ft_traceroute.sock < 0)
		dlog("socket error: %d, errno: %s", g_ft_traceroute.sock, strerror(errno));
	if (setsockopt(g_ft_traceroute.sock, SOL_SOCKET, SO_RCVTIMEO,
				   &timeout, sizeof(timeout)) != 0)
	{
		err_fmt(CANNOT_SET_RCVTIMEO, "%s: can't set recv timeout: %s",
				g_ft_traceroute.exec_name, strerror(errno));
	}
	if (setsockopt(g_ft_traceroute.sock, SOL_IP, IP_TTL,
				   &g_ft_traceroute.ttl, sizeof(g_ft_traceroute.ttl)) != 0)
	{
		err_fmt(CANNOT_SET_TTL, "%s: can't set unicast time-to-live: %s",
				g_ft_traceroute.exec_name, strerror(errno));
	}
}