/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notlibft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:52:39 by edgribei          #+#    #+#             */
/*   Updated: 2025/10/31 15:53:23 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb)
		if (SIZE_MAX / nmemb < size)
			return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, nmemb * size);
	return (ptr);
}

int	safe_atoi(const char *str, int *const ret)
{
	const char		sign = (-2 * (*str == '-')) + 1;
	unsigned int	res;

	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (-1);
	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		if (((unsigned int) INT_MAX + (sign == -1) - (*str - '0')) / 10 < res)
			return (-1);
		res = res * 10 + (*str - '0');
		str++;
	}
	*ret = res * sign;
	return (0);
}
