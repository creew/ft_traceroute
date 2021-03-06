/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:43:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 17:43:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	parse_option_m(int argc, char **argv, char *arg, int *i)
{
	char *end;

	arg = parse_joined_option(argc, argv, arg, i);
	g_ft_traceroute.max_hops = (int)ft_strtol(arg, &end, 10);
	if (*end != '\0')
		err_fmt(INVALID_MAX_HOPS, "\"%s\" bad value for max ttl", arg);
	if (g_ft_traceroute.max_hops < 1)
		err_fmt(INVALID_MAX_HOPS,
				"first hop out of range");
	dlog("max hops: %d", g_ft_traceroute.max_hops);
	return (0);
}