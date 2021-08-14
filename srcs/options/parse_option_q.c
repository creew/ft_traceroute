/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option_q.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:43:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 17:43:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	parse_option_q(int argc, char **argv, char *arg, int *i)
{
	arg = parse_joined_option(argc, argv, arg, i);
	g_ft_traceroute.number_of_queries = (int)ft_strtol(arg, NULL, 10);
	if (g_ft_traceroute.number_of_queries < 1 ||
	    g_ft_traceroute.number_of_queries > 10)
		err_fmt(INVALID_NUMBER_OF_QUERIES,
				"no more than 10 probes per hop");
	dlog("number of queries: %d", g_ft_traceroute.number_of_queries);
	return (0);
}