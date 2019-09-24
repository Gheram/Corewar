/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:07:58 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 16:08:00 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <time.h>

void		print_pourcent(unsigned int lives[4], WINDOW *win, int y)
{
	float	total;
	int		x;
	int		x_total;
	int		champ;
	float	pourcent;

	total = lives[0] + lives[1] + lives[2] + lives[3];
	champ = -1;
	x_total = 0;
	while (++champ < 4)
	{
		wattron(win, COLOR_PAIR(champ + 1));
		x = -1;
		pourcent = (int)((float)(lives[champ]) / total *
					(50.0 - (float)x_total));
		while (++x < pourcent)
			mvwprintw(win, y, 4 + x + x_total, "-");
		wattroff(win, COLOR_PAIR(champ + 1));
		x_total += x;
		total -= lives[champ];
	}
}

static void	print_players(WINDOW *right_win, t_storage *storage)
{
	int		i;

	i = 0;
	while (++i <= storage->nb_champ)
	{
		mvwprintw(right_win, 20 + (i * 4), 15, "%d", DISPLAY.last_live[i - 1]);
		mvwprintw(right_win, 21 + (i * 4), 28, "%d",
						DISPLAY.live_current[i - 1]);
	}
}

static void	print_process(t_storage *storage)
{
	t_process_lst	*lst;
	unsigned int	color;

	lst = storage->process_lst;
	while (lst)
	{
		color = 6 + PROPERTY[lst->content->pos];
		if (color == 6)
			color = 11;
		wattron(DISPLAY.left_win, COLOR_PAIR(color));
		mvwprintw(DISPLAY.left_win, get_y(lst->content->pos),
					get_x(lst->content->pos), "%02x", MEM[lst->content->pos]);
		wattroff(DISPLAY.left_win, COLOR_PAIR(color));
		lst = lst->next;
	}
}

static void	get_input(t_storage *storage, WINDOW *right_win, int input)
{
	while (input != ERR)
	{
		if (input == ' ')
		{
			mvwprintw(right_win, 3, 3, "** PAUSED ** ");
			wrefresh(right_win);
			while (getch() != ' ')
				;
			mvwprintw(right_win, 3, 3, "** RUNNING **");
			wrefresh(right_win);
		}
		if (input == 'q')
			DISPLAY.max_fps =
					((DISPLAY.max_fps > 10) ? DISPLAY.max_fps - 10 : 1);
		if (input == 'w')
			DISPLAY.max_fps =
					((DISPLAY.max_fps > 1) ? DISPLAY.max_fps - 1 : 1);
		if (input == 'e')
			DISPLAY.max_fps = DISPLAY.max_fps + 1;
		if (input == 'r')
			DISPLAY.max_fps = DISPLAY.max_fps + 10;
		mvwprintw(right_win, 6, 25, "%d   ", DISPLAY.max_fps);
		wrefresh(right_win);
		input = getch();
	}
}

void		display(t_storage *storage)
{
	WINDOW	*win;
	WINDOW	*right_win;

	win = DISPLAY.left_win;
	right_win = DISPLAY.right_win;
	get_input(storage, right_win, getch());
	print_players(right_win, storage);
	print_news(win);
	print_pourcent(DISPLAY.live_current, right_win, 19);
	mvwprintw(right_win, 14, 11, "%d", DISPLAY.cycle);
	mvwprintw(right_win, 16, 15, "%d   ", DISPLAY.process);
	mvwprintw(right_win, 8, 18, "%d   ", CYCLE_INFO.last_die_time);
	print_process(storage);
	wrefresh(win);
	wrefresh(right_win);
	usleep((1.0 / DISPLAY.max_fps) * (1000000));
}
