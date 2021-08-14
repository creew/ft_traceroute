/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_addr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 16:28:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 16:28:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_ADDR_H
# define GET_ADDR_H

# include <netdb.h>

typedef struct s_addr_info {
	struct in_addr	sin_addr;
	socklen_t		ai_addrlen;
	struct sockaddr	ai_addr;
} t_addr_info;

int	get_addr(char *addr, t_addr_info *addr_info);

#endif
