/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:10 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 14:50:49 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>

unsigned int	ft_atoihex(const char *str)
{
	static const char *const	base = "0123456789abcdef";
	int							num;
	const char					*dgt;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	num = 0;
	dgt = ft_strchr(base, ft_tolower(*str));
	while (dgt)
	{
		num = num * 16 + dgt - base;
		str++;
		dgt = ft_strchr(base, ft_tolower(*str));
	}
	return (num);
}

//returns -1 on failure (like an overflow or a non numeric input)
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
