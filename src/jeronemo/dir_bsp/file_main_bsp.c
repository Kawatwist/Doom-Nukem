/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_main_bsp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:34:03 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 10:27:44 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "file_bsp.h"

// int			main_function(void)
// {
// 	t_mywin		s_win;
// 	t_mynode	s_node;

// 	printf("hello chef Inca\n");
// 	s_win.polygon_lst = ft_read_the_polygon_file();
// 	ft_display_the_polygon_list(s_win.polygon_lst);
// 	ft_process_polygon(s_win.polygon_lst);
// 	ft_build_bsp_tree((&s_node), s_win.polygon_lst);
// 	ft_afficher_le_bsp(&s_node);
// 	//ft_display_polygon();
// 	return (1);
// }



int			main(int argc, char** argv)
{
	t_mywin		s_win;
	t_mynode	s_node;


printf("AAAAAAAAAAAAAAAAAAAAAAA l'adresse du first =%p\n", &s_node);
	if (argc != 2)
	{
		printf("usage : ./a.out file name\n");
		return (-1);
	}
	printf("hello chef Inca\n");
	ft_bzero(&s_node, sizeof(s_node));
	s_win.polygon_lst = ft_read_the_polygon_file(argv[1]);
	ft_display_the_polygon_list(s_win.polygon_lst);
	ft_process_polygon(s_win.polygon_lst);
	ft_build_bsp_tree((&s_node), s_win.polygon_lst);
	printf("AAAAAAAAAAAAAAAAAAAAAAAl'adresse du first =%p\n", &s_node);
	printf("first node isleaf%d|\n", s_node.is_leaf);
	printf("BBBBBBBBBBBBB second node isleaf%d|\n", s_node.front->is_leaf);
	printf("BBBBBBBBBBBBB thired node isleaf%d|\n", s_node.front->front->is_leaf);
	ft_afficher_le_bsp(&s_node);


	//ft_display_polygon();




	return (1);
}