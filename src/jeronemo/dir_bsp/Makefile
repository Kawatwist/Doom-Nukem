# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/26 15:30:53 by jchardin          #+#    #+#              #
#    Updated: 2019/06/04 15:51:35 by jchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC += file_main_bsp.c
SRC += file_parser_polygons.c
SRC += file_process_polygon.c
SRC += file_test_function.c
SRC += file_maths.c
SRC += file_build_bsp_tree.c
SRC += file_select_spliter.c
SRC += file_classify_polygon.c
SRC += file_affichage_bsp.c
SRC += file_split_polygon.c


all:
	gcc $(SRC) ./libft/libft.a   -fsanitize=address -g

