/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_itoa_coma.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:06:40 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/27 17:06:47 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

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
