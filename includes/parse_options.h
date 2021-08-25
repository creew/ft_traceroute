/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:51:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 17:51:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_TRACEROUTE_PARSE_OPTIONS_H
# define FT_TRACEROUTE_PARSE_OPTIONS_H

int	parse_option_f(int argc, char **argv, char *arg, int *i);
int	parse_option_h(int argc, char **argv, char *arg, int *i);
int	parse_option_I(int argc, char **argv, char *arg, int *i);
int	parse_option_m(int argc, char **argv, char *arg, int *i);
int	parse_option_p(int argc, char **argv, char *arg, int *i);
int	parse_option_q(int argc, char **argv, char *arg, int *i);
int	parse_option_v(int argc, char **argv, char *arg, int *i);
int	parse_option_w(int argc, char **argv, char *arg, int *i);

#endif
