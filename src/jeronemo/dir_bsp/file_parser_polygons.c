/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser_polygons.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:54:18 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/06 10:46:20 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_bsp.h"

t_myvec			*ft_get_and_create_vertex_node(char *line, int *j)
{
	int			k;
	char		nbr[1000];
	t_myvec		*s_vertex;

	s_vertex = (t_myvec*)malloc(sizeof(t_myvec));
		k = 0;
	while(ft_isdigit(line[*j]) || line[*j] == '-' || line[*j] == '.' )
	{
		nbr[k] = line[*j];
		*j = *j + 1;
		k++;
	}
	nbr[k] = '\0';
	//printf("le nombre =%s\n", nbr);
	s_vertex->x = ft_atoi(nbr);
	//printf(" =%f\n", ft_atoi(nbr));

		k = 0;
		while (line[*j] == ' ')
			*j = *j + 1;
	while(ft_isdigit(line[*j]) || line[*j] == '-' || line[*j] == '.' )
	{
		nbr[k] = line[*j];
		*j = *j + 1;
		k++;
	}
	nbr[k] = '\0';
	s_vertex->y = ft_atoi(nbr);
	//printf(" =%f\n", ft_atoi(nbr));

		k = 0;
		while (line[*j] == ' ')
			*j = *j + 1;
	while(ft_isdigit(line[*j]) || line[*j] == '-' || line[*j] == '.' )
	{
		nbr[k] = line[*j];
		*j = *j + 1;
		k++;
	}
	nbr[k] = '\0';
	s_vertex->z = ft_atoi(nbr);
	//printf(" =%f\n", ft_atoi(nbr));
	//printf("\n\n");
	return (s_vertex);
}

void			ft_add_vertex(t_myvec **vertex_lst, t_myvec *vertex_node)
{
	t_myvec *keep;

	keep = *vertex_lst;
	if (*vertex_lst == NULL)
	{
		vertex_node->next = NULL;
		*vertex_lst = vertex_node;
	}
	else
	{
		while ((*vertex_lst)->next != NULL)
			*vertex_lst = (*vertex_lst)->next;
		vertex_node->next = NULL;
		(*vertex_lst)->next = vertex_node;
		*vertex_lst = keep;
	}
}

void			ft_go_to_first_vertex(char *line, int *j)
{
	while(line[*j] != ':' )
		*j = *j + 1;
	*j = *j + 1;
}

t_mypolygon	*ft_create_polygon_node(t_myvec *vertex_lst)
{
	t_mypolygon	*polygon_node;

	polygon_node = (t_mypolygon*)malloc(sizeof(t_mypolygon));
	polygon_node->vertex_lst = vertex_lst;
	return(polygon_node);
}

void	ft_add_polygon(t_mypolygon **polygon_lst, t_mypolygon *polygon_node)
{
	if (*polygon_lst == NULL)
	{
		polygon_node->next = NULL;
		*polygon_lst = polygon_node;
	}
	else
	{
		polygon_node->next = *polygon_lst;
		*polygon_lst = polygon_node;
	}
}

t_mypolygon		*ft_read_the_polygon_file(void)
{
	int				fd;
	char			*line;
	t_myvec			*vertex_node;
	t_myvec			*vertex_lst;
	t_mypolygon		*polygon_node;
	t_mypolygon		*polygon_lst;
	int				j;

	line = NULL;
	polygon_lst = NULL;
	fd = open("./file_wall_bsp", O_RDWR);
	while(get_next_line(fd, &line))
	{
		vertex_lst = NULL;
		j = 0;
		ft_go_to_first_vertex(line, &j);
		//printf("the first =%c\n", line[j]);
		while(line[j] != ':' && line[j] != '\0')
		{
			vertex_node = ft_get_and_create_vertex_node(line, &j);
			ft_add_vertex(&vertex_lst, vertex_node);
			if (line[j] != ':')
			{
				while(line[j] == ' ' || line[j] == ';')
					j++;
			}
		}
		polygon_node = ft_create_polygon_node(vertex_lst);
		ft_add_polygon(&polygon_lst, polygon_node);
	}
	return (polygon_lst);
}
