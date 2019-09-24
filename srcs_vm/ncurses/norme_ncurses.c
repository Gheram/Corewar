/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme_ncurses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:08:04 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 16:08:09 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	print_string(WINDOW *win, unsigned char str[4], unsigned int id,
					unsigned int where)
{
	int	i;

	i = -1;
	wattron(win, COLOR_PAIR(id));
	while (++i < 4)
		mvwprintw(win, get_y(where + i), get_x(where + i), "%02x", str[i]);
	wattroff(win, COLOR_PAIR(id));
}

void	loop_writers(WINDOW *win, t_writer_list *writers)
{
	if (writers->next)
		loop_writers(win, writers->next);
	print_string(win, writers->content, writers->writer, writers->where);
	free(writers);
}

void	print_news(WINDOW *win)
{
	t_writer_list	*new_writers;

	new_writers = get_writers();
	if (new_writers)
		loop_writers(win, new_writers);
}

void	print_new_cycle(t_storage *storage)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		DISPLAY.live_past[i] = DISPLAY.live_current[i];
		DISPLAY.live_current[i] = 0;
	}
	mvwprintw(DISPLAY.right_win, 19, 3,
			"[--------------------------------------------------]");
	print_pourcent(DISPLAY.live_past, DISPLAY.right_win, 21);
}

void	erase_process(t_storage *storage)
{
	t_process_lst	*lst;
	unsigned int	color;

	lst = storage->process_lst;
	while (lst)
	{
		color = PROPERTY[lst->content->pos];
		if (color == 0)
			color = 6;
		wattron(DISPLAY.left_win, COLOR_PAIR(color));
		mvwprintw(DISPLAY.left_win, get_y(lst->content->pos),
				get_x(lst->content->pos), "%02x", MEM[lst->content->pos]);
		wattroff(DISPLAY.left_win, COLOR_PAIR(color));
		lst = lst->next;
	}
}
