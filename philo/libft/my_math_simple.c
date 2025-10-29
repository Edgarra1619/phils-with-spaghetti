/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:49:31 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/30 17:50:44 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(const int a, const int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(const int a, const int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	abs(const int a)
{
	if (a < 0)
		return (-a);
	return (a);
}
