/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <eklompus@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 22:55:00 by eklompus          #+#    #+#             */
/*   Updated: 2021/08/25 22:55:00 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

int calc_int_length(int i)
{
	int length;

	length = 0;
	if (i == 0) {
		return (1);
	}
	if (i < 0) {
		length++;
	}
	while (i != 0) {
		length++;
		i /= 10;
	}
	return (length);
}

long	tv_diff_micro(struct timeval *start)
{
	struct timeval		end_time;

	gettimeofday(&end_time, NULL);
	return ((end_time.tv_sec - start->tv_sec) * 1000000
	+ (end_time.tv_usec - start->tv_usec));
}

float	tv_diff_millis(struct timeval *start)
{
	long	diff;

	diff = tv_diff_micro(start);
	return (((float)diff) / 1000);
}
