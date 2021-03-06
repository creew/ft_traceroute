/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 21:42:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/05/21 21:42:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include "parse_options.h"
#include <stdio.h>

static const t_arg_function g_arg_functions[] = {
	{'f', parse_option_f, "first ttl"},
	{'h', parse_option_h, "help"},
	{'I', parse_option_I, "use icmp"},
	{'m', parse_option_m, "max ttl"},
	{'p', parse_option_p, "port"},
	{'q', parse_option_q, "nprobes"},
	{'v', parse_option_v, "verbose"},
	{'w', parse_option_w, "wait time"}
};

char	*parse_joined_option(int argc, char *const *argv, char *arg, int *i)
{
	char	arg_symbol;

	arg_symbol = *arg++;
	if (*arg == 0)
	{
		if (*i < argc)
		{
			arg = argv[*i];
			*i = *i + 1;
		}
		else
			err_fmt_usage("%s: option requires an argument -- '%c'",
						  g_ft_traceroute.exec_name, arg_symbol);
	}
	else
	{
		while (ft_isspace(*arg))
			arg++;
	}
	return (arg);
}

static int	parse_options(int argc, char *argv[], char *arg, int *i)
{
	unsigned long	c;

	c = 0;
	while (c < sizeof(g_arg_functions) / sizeof(g_arg_functions[0]))
	{
		if (*arg == g_arg_functions[c].arg)
			return (g_arg_functions[c].parse_function(argc, argv, arg, i));
		c++;
	}
	if (*arg != 0)
	{
		dprintf(2, "ping: invalid option -- '%c'\n", *arg);
		print_usage(g_ft_traceroute.exec_name, 2);
	}
	return (0);
}

int	parse_argv(int argc, char *argv[])
{
	char	*arg;
	int		i;

	i = 1;
	while (i < argc)
	{
		arg = argv[i++];
		if (*arg == '-')
		{
			while (parse_options(argc, argv, ++arg, &i))
			{
			}
		}
		else
		{
			if (g_ft_traceroute.host == NULL)
				g_ft_traceroute.host = arg;
			else
				print_usage(g_ft_traceroute.exec_name, 2);
		}
	}
	return (OK);
}
