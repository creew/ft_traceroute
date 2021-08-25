/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:43:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 17:43:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	parse_option_p(int argc, char **argv, char *arg, int *i)
{
	char *end;

	arg = parse_joined_option(argc, argv, arg, i);
	g_ft_traceroute.port_number = (int)ft_strtol(arg, &end, 10);
	if (*end != '\0')
		err_fmt(INVALID_PORT_NUMBER, "\"%s\" bad value for port", arg);
	if (g_ft_traceroute.port_number < 0)
		err_fmt(INVALID_PORT_NUMBER, "port must be > 0");
	if (g_ft_traceroute.port_number > 65535)
		err_fmt(INVALID_PORT_NUMBER, "port must be <= 65535");
	dlog("port number: %d", g_ft_traceroute.port_number);
	return (0);
}