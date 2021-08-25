/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:43:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 17:43:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	parse_option_f(int argc, char **argv, char *arg, int *i)
{
	char *end;

	arg = parse_joined_option(argc, argv, arg, i);
	g_ft_traceroute.ttl = (int)ft_strtol(arg, &end, 10);
	if (*end != '\0')
		err_fmt(INVALID_FIRST_HOP, "\"%s\" bad value for first ttl", arg);
	if (g_ft_traceroute.ttl < 1)
		err_fmt(INVALID_FIRST_HOP,
				"first hop out of range");
	dlog("count of hops: %d", g_ft_traceroute.ttl);
	return (0);
}