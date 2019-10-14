/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:56:40 by llejeune          #+#    #+#             */
/*   Updated: 2019/09/12 16:56:42 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <editor.h>

static t_point  *find_before(t_elem *elem, t_point *tofind)
{
    t_point *curr;
    
    curr = elem->point;
    while (curr != NULL && curr != tofind && curr->next != tofind)
        curr = curr->next;
    return (curr == tofind ? NULL : curr);
}

static int  store_reverse_vertice(t_elem *elem, int fd)
{
    int     nb_ver;
    t_point *curr;
    
    nb_ver = 0;
    curr = elem->point;
    while (curr->next != NULL)
        curr = curr->next;
    while (curr != elem->point)
    {
        ft_putstr_fd("v ", fd);
        ft_ftoafd(curr->x, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd(' ', fd);
        ft_ftoafd(curr->y, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd(' ', fd);
        ft_ftoafd(curr->z, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd('\n', fd);
        nb_ver += 1;
        curr = find_before(elem, curr);
    }
    return (nb_ver);
}

static int  store_vertice(t_elem *elem, int fd)
{
    int     nb_ver;
    t_point *curr;
    
    nb_ver = 0;
    curr = elem->point;
    while (curr != NULL)
    {
        ft_putstr_fd("v ", fd);
        ft_ftoafd(curr->x, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd(' ', fd);
        ft_ftoafd(curr->y, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd(' ', fd);
        ft_ftoafd(curr->z, fd); // NEED TO CHECK THIS FUNCTION
        ft_putchar_fd('\n', fd);
        nb_ver += 1;
        curr = curr->next;
    }
    return (nb_ver);
}

static void create_face(Uint32 nb1, Uint32 nb2, Uint32 nb3, int fd)
{
    Uint32 i;
    
    i = 0;
    while (i < nb1 - 1) // ATTENTION SI NB1 != NB2
    {
        ft_putstr_fd("f ", fd);
        ft_putnbr_fd(i + nb3, fd);
        ft_putstr_fd(" / ", fd);
        ft_putnbr_fd(i + 1 + nb3, fd);
        ft_putstr_fd(" / ", fd);
        ft_putnbr_fd(nb2 - i + nb3, fd);
        ft_putstr_fd(" / ", fd);
        ft_putnbr_fd(nb2 - (i + 1) + nb3, fd);
        ft_putchar_fd('\n', fd);
        i++;
    }
}

static void fill_file(t_win *wn, t_edit *edit, int fd)
{
    t_elem  *curr_elem;
    Uint32  nb;
    Uint32  nb_ver1;
    Uint32  nb_ver2;
    Uint32  nb_ver3;
    
    (void)wn;
    curr_elem = edit->elem;
    nb = 1;
    nb_ver3 = 1;
    while (curr_elem != NULL && curr_elem->next != NULL && curr_elem->point != NULL)
    {
        ft_putstr_fd("o Polygon.", fd);
        ft_putnbr_fd(nb, fd);
        ft_putchar_fd('\n', fd);
        nb_ver1 = store_vertice(curr_elem, fd);
        nb_ver2 = store_reverse_vertice(curr_elem->next, fd);
        create_face(nb_ver1, nb_ver2, nb_ver3, fd);
        ft_putstr_fd("s off\n", fd);
        if (curr_elem->next->next == NULL || curr_elem->next->next->next == NULL)
            break;
        curr_elem = curr_elem->next->next;
        nb_ver3 += nb_ver1 + nb_ver2;
        nb++;
    }
    ft_putstr_fd("# ", fd); // DONT NEED THIS BUT COULD BE USEFUL
    ft_putnbr_fd(nb, fd);
    ft_putstr_fd(" elements", fd);
}

static void create_obj(t_win *wn, t_edit *edit, char *name)
{
   int fd;

   (void)wn;
   (void)edit;
   fd = 0;
//    if (!access(name, F_OK))
//    {
       if ((fd = creat(name, O_WRONLY | S_IRWXU| S_IROTH)) != -1)
        {
           ft_putstr("File's has been create\n");
           ft_putstr_fd(name, fd);
           ft_putchar_fd('\n', fd);
           fill_file(wn, edit, fd);
           ft_putstr("File's filled\n");
        }
       else
           ft_putstr("File's creation failed\n");
//    }
//    else
//        ft_putstr("File name already used\n"); // POP UP OVERWRITE
}

void        save_panel(t_win *wn, t_edit *edit)
{
   static char *map_name = NULL;
   SDL_Rect    position;
   SDL_Rect     mouse;
   
   position = define_rect(((t_edit *)wn->edit)->tab->bg.x + ((t_edit*)wn->edit)->tab->bg.w - 100, ((t_edit*)wn->edit)->tab->bg.y + 200, 50, ((t_edit*)wn->edit)->tab->bg.h);	
   
    printf("mapname AVANT= %s\n", map_name);
    map_name = text_box(wn, map_name);
   mouse.x = wn->input->x;
    mouse.y = wn->input->y;
    printf("mapname = %s\n", map_name);
   if (edit->elem != NULL && map_name != NULL && boxhitbox(wn->rend, &mouse, &position, 1) && mouse_pressed(wn, SDL_BUTTON_LEFT))
   {
       map_name = ft_strjoinfree(map_name, ".obj", 1);
       create_obj(wn, edit, map_name);
       printf("Map save will be called %s\n", map_name);
   }
}