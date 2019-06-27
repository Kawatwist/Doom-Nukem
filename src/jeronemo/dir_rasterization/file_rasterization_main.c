/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/27 13:41:04 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>


//ps n'essayer pas de comprendre
char	*ft_itoa_comma(float nbr)
{
	char	str[14] = {'0','1','2','3','4','5','6','7','8','9'};
	char	*string;
	int 	size;
	float	temp;
	char	*string2;
	float	temp2;


	size = 0;

	if (nbr == 0)
		return ("0");
	if (nbr < 0)
		nbr *= -1;
	temp = nbr;

	temp = (int)temp;
	while ((int)(temp) > 0)
	{
		temp /= 10;
		size++;
	}
	string = (char*)malloc(sizeof(char) * (size + 1));
	temp = (int)nbr;
	string[size] = '\0';
	size--;
	while ((int)temp > 1)
	{
		string[size] = str[ (int)(temp)% 10      ];
		temp = (temp / 10);
		size--;
	}
	temp = nbr;
	temp = temp - (int)temp;

	while ((temp - (int)temp) > 0)
	{
		temp *= 10;
	}
	temp2 = temp;
	size = 0;
	while ((int)(temp2) > 0)
	{
		temp2 /= 10;
		size++;
	}
	string2 = (char*)malloc(sizeof(char) * size + 1);
	string2[size] = '\0';
	size--;
	temp2 = nbr - (int)nbr;
	while ((temp2 - (int)temp2) > 0)
	{
		temp2 *= 10;
	}
	while ((int)temp2 > 1)
	{
		string2[size] = str[ (int)(temp2)%10 ];
		temp2 = (temp2 / 10);
		size--;
	}
	string = ft_strjoin(string, ",");
	string = ft_strjoin(string, string2);
	return (string);
}



float		ft_get_the_indice_vertex_x(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	x;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	x = vertex_lst->x;
	vertex_lst = keep;
	return (x);
}

float		ft_get_the_indice_vertex_y(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	y;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	y = vertex_lst->y;
	vertex_lst = keep;
	return (y);
}

float		ft_get_the_indice_vertex_z(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	z;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	z = vertex_lst->z;
	vertex_lst = keep;
	return (z);
}

t_vector3	substract_vector3_to_vector3(t_vector3 a,t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x - b.x, a.y - b.y, a.z - b.z);

	return (result);
}



t_vector3	add_vector3_to_vector3(t_vector3 a,t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x + b.x, a.y + b.y, a.z + b.z);

	return (result);
}




void	ft_order_triangle_vertice(t_myvec *v1, t_myvec *v2, t_myvec *v3);





