/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_fd.c		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:06:40 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/27 17:06:47 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

//ps n'essayer pas de comprendre
void	ftoa_fd(float nbr, int fd)
{
	char	str[14] = {'0','1','2','3','4','5','6','7','8','9'};
	char	*string;
	int 	size;
	float	temp;
	char	*string2;
	float	temp2;


	size = 0;

	if (nbr == 0)
		ft_putstr_fd("0", fd);
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
		string[size] = str[ (int)(temp)% 10];
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
	if (size == 0)
		string[0] = '-';
	string = ft_strjoin(string, ",");
	string = ft_strjoin(string, string2);
	ft_putstr_fd(string, fd);
}
