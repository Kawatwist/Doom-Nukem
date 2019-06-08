/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_maths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:37:01 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 10:29:16 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h> 

float		ft_dot_product(t_myvec v1, t_myvec v2)
{
	float		result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (result);
}

t_myvec		ft_cross_product(t_myvec v1, t_myvec v2)
{
	t_myvec		result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}

t_myvec		ft_calculate_normal_of_points(t_myvec vertex1, t_myvec vertex2, t_myvec vertex3)
{
	t_myvec		result;
	t_myvec		v1;
	t_myvec		v2;

	v1.x = vertex2.x - vertex1.x;
	v1.y = vertex2.y - vertex1.y;
	v1.z = vertex2.z - vertex1.z;
	v2.x = vertex3.x - vertex1.x;
	v2.y = vertex3.y - vertex1.y;
	v2.z = vertex3.z - vertex1.z;
	result = ft_cross_product(v1, v2);
	return (result);
}

t_myvec		ft_vector_from_two_points(t_myvec v2, t_myvec v1)
{
	t_myvec			result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}

int		ft_abs(int number)
{
	//prevoir le int min
	if (number < 0)
		number *= -1;
	return (number);
}




float		ft_atoi_comma(const char *str)
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
