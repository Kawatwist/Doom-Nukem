/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.co>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 08:09:21 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/02 11:07:41 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

float		ft_atoi(const char *str)
{
	int			i;
	float		nb;
	float		nega;
	int			point;
	float			j;

	i = 0;
	nega = 1;
	nb = 0;
	point = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
		nega = -1;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' &&  str[i] != '.')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	//printf("le nombre avant point =%f\n", nb);
	j = 10;
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			nb = nb + (str[i] - '0') / j;
	//printf("le nombre apres point =%f\n", (str[i] - '0') / j);

			i++;
			j *= 10;
		}
	}
	return (nb * nega);
}
