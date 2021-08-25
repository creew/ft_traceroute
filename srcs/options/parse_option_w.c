/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option_w.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:43:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 17:43:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	parse_option_w(int argc, char **argv, char *arg, int *i)
{
	char *end;

	arg = parse_joined_option(argc, argv, arg, i);
	g_ft_traceroute.wait_probe_time = (int)ft_strtol(arg, &end, 10);
	if (*end != '\0')
		err_fmt(INVALID_NUMBER_OF_QUERIES, "\"%s\" bad value for wait time", arg);
	if (g_ft_traceroute.wait_probe_time < 0)
		err_fmt(INVALID_WAIT_PROBE_TIME,
				"probes time wait out of range");
	dlog("number of seconds to wait probe: %d", g_ft_traceroute.wait_probe_time);
	return (0);
}