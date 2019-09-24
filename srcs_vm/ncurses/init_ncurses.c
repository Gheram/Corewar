/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbargues <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:07:55 by vbargues          #+#    #+#             */
/*   Updated: 2019/09/09 16:07:57 by vbargues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	print_champs_code(t_storage *storage, WINDOW *win)
{
	int		i;
	int		pos;
	size_t	j;

	i = -1;
	while (++i < NB_CHAMP)
	{
		pos = MEM_SIZE / NB_CHAMP * i;
		j = -1;
		while (++j < CHAMP[i].body_size)
		{
			wattron(win, COLOR_PAIR(CHAMP[i].id));
			mvwprintw(win, get_y(pos + j), get_x(pos + j), "%02x",
							CHAMP[i].body[j]);
			wattroff(win, COLOR_PAIR(CHAMP[i].id));
		}
	}
}

static void	print_champs(WINDOW *right_win, t_storage *storage)
{
	int		i;

	i = 0;
	while (++i <= storage->nb_champ)
	{
		mvwprintw(right_win, 19 + (i * 4), 3, "Player 1 : ");
		wattron(right_win, COLOR_PAIR(i));
		mvwprintw(right_win, 19 + (i * 4), 14, CHAMP[i - 1].head.prog_name);
		wattroff(right_win, COLOR_PAIR(i));
		mvwprintw(right_win, 20 + (i * 4), 3, "Last live : %d",
					DISPLAY.last_live[i - 1]);
		mvwprintw(right_win, 21 + (i * 4), 3, "Live in current period : %d",
					DISPLAY.live_current[i - 1]);
	}
}

static void	init_colors(void)
{
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_color(COLOR_MAGENTA, 600, 600, 600);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_MAGENTA);
	init_pair(8, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(9, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair(10, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(11, COLOR_BLACK, COLOR_MAGENTA);
}

static void	print_text(WINDOW *right_win, WINDOW *left_win)
{
	wattron(left_win, COLOR_PAIR(5));
	wborder(left_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(left_win, COLOR_PAIR(5));
	wattron(right_win, COLOR_PAIR(5));
	wborder(right_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(right_win, COLOR_PAIR(5));
	wattron(left_win, COLOR_PAIR(6));
	fill_win(left_win);
	mvwprintw(right_win, 3, 3, "** PAUSED ** ");
	mvwprintw(right_win, 6, 3, "Cycles/second limit : %d", MAX_FPS);
	mvwprintw(right_win, 8, 3, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	mvwprintw(right_win, 9, 3, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(right_win, 10, 3, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(right_win, 11, 3, "MAX_CHECKS : %d", MAX_CHECKS);
	mvwprintw(right_win, 14, 3, "Cycle : 0");
	mvwprintw(right_win, 16, 3, "Processes : 0");
	mvwprintw(right_win, 18, 3, "Live breakdown for current period :");
	mvwprintw(right_win, 19, 3,
			"[--------------------------------------------------]");
	mvwprintw(right_win, 20, 3, "Live breakdown for last period :");
	mvwprintw(right_win, 21, 3,
			"[--------------------------------------------------]");
}

void		init(t_storage *storage)
{
	WINDOW		*right_win;
	WINDOW		*left_win;
	char		c;

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	start_color();
	c = getch();
	left_win = newwin(66, 197, 0, 0);
	right_win = newwin(66, 58, 0, 196);
	init_colors();
	DISPLAY.left_win = left_win;
	DISPLAY.right_win = right_win;
	DISPLAY.max_fps = MAX_FPS;
	print_text(right_win, left_win);
	print_champs_code(storage, left_win);
	print_champs(right_win, storage);
	wrefresh(right_win);
	wrefresh(left_win);
	while (c != ' ')
		c = getch();
	mvwprintw(right_win, 3, 3, "** RUNNING ** ");
	wrefresh(right_win);
}
