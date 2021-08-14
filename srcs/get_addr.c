/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_addr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 16:20:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/14 16:20:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_addr.h"
#include "libft.h"

int	get_addr(char *addr, t_addr_info *addr_info)
{
	struct addrinfo	*parsed_ai;
	struct addrinfo	hints;
	int				res;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	res = getaddrinfo(addr, NULL, &hints, &parsed_ai);
	if (res == 0)
	{
		ft_memcpy(&addr_info->ai_addr, parsed_ai->ai_addr,
				  sizeof(struct sockaddr));
		addr_info->ai_addrlen = parsed_ai->ai_addrlen;
		addr_info->sin_addr
		= ((struct sockaddr_in *)&addr_info->ai_addr)->sin_addr;
		freeaddrinfo(parsed_ai);
	}
	return (res);
}