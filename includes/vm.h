/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 13:31:51 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 21:39:56 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "../libft/libft.h"
# include "../includes/op.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ncurses.h>

/*
**							STRUCT DEFINE
*/
# define OPTION 			storage->option
# define FLAG 				storage->option.flag
# define CHAMP				storage->champ
# define MEM 				storage->memory.mem
# define PROPERTY 			storage->memory.property
# define PROCESS			storage->process_lst
# define DISPLAY			storage->display
# define CYCLE_INFO			storage->cycle_info
# define NB_CHAMP 			storage->nb_champ

/*
**							OPTION DEFINE
*/
# define DUMP				1
# define CHAMP_NUM			2
# define VERB				4
# define DSP				8
# define HELP				16
# define AFF				32

/*
**							ERROR DEFINE
*/
# define MALLOC 			1
# define FD 				2
# define CHAMP_SIZE 		3
# define MAGIC 				4
# define EXT 				5
# define TOO_MANY_PLAYERS	6
# define USAGE				7
# define NO_CHAMP			8

# define MAX_FPS 			50

/*
**							STRUCTURES
*/
typedef struct				s_format_args_norme
{
	int						param_size;
	int						arg[3];
	int						i;
	unsigned char			ocp;
	unsigned int			pos;
	int						exec;
}							t_format_args_norme;

typedef struct				s_option
{
	unsigned int			flag;
	unsigned int			nbr_cycles;
	int						number[MAX_PLAYERS];
	int						champ_index;
	int						verb_flag;
	int						*pos;
}							t_option;

typedef struct				s_champ
{
	t_header				head;
	unsigned char			body[CHAMP_MAX_SIZE];
	size_t					body_size;
	unsigned int			id;
	t_bool					live;
	t_bool					dead;
}							t_champ;

typedef struct				s_process
{
	int						registre[REG_NUMBER + 1];
	t_bool					carry;
	t_bool					live;
	int						wcycle;
	unsigned int			pos;
	unsigned char			opc;
	unsigned char			ocp;
	unsigned int			owner;
	unsigned int			id;
}							t_process;

typedef struct				s_cycle_data
{
	unsigned int			nb_live;
	int						die_time;
	int						last_die_time;
	int						wcheck;
}							t_cycle_data;

typedef struct				s_process_lst
{
	t_process				*content;
	size_t					content_size;
	struct s_process_lst	*next;
}							t_process_lst;

typedef struct				s_writer_list
{
	struct s_writer_list	*next;
	unsigned char			content[4];
	unsigned int			writer;
	unsigned int			where;
}							t_writer_list;

typedef struct				s_mem
{
	unsigned char			mem[MEM_SIZE];
	unsigned char			property[MEM_SIZE];
}							t_mem;

typedef struct				s_display
{
	WINDOW					*left_win;
	WINDOW					*right_win;
	unsigned int			last_live[4];
	unsigned int			live_current[4];
	unsigned int			live_past[4];
	unsigned int			cycle;
	unsigned int			process;
	unsigned int			max_fps;
}							t_display;

typedef struct				s_storage
{
	t_option				option;
	t_champ					*champ;
	t_mem					memory;
	t_process_lst			*process_lst;
	t_cycle_data			cycle_info;
	t_display				display;
	int						nb_champ;
	int						last_live;
}							t_storage;

/*
**							PARSING
*/
void						get_champs(int ac, char **av, t_storage *storage);
int							get_champ_info(char *name, t_champ *champ, int id);
unsigned int				swap_int_bit(unsigned int n);
t_champ						*init_champ(t_champ *champ, size_t size);
void						get_options(t_storage *storage, int ac, char **av);
void						usage(t_bool h);
void						introduce_champ(t_storage *storage);
void						init_number(int *tab);
void						set_up_mem(t_storage *storage);
void						init_process(t_storage *storage);
/*
**							PROCESS MANAGER
*/
int							create_process(t_storage *storage,
							t_process process);
void						start(t_storage *storage);
void						del_process(t_process_lst **begin,
							t_process_lst **elem);
void						check_champ(t_storage *storage);
t_bool						is_opc(t_storage *storage, t_process *content);
void						update_die_time(t_storage *storage);
void						format_args(t_storage *storage, t_process *process);
void						write_in_ram(t_storage *storage, int pos,
							unsigned int content, unsigned int player_id);
unsigned int				read_in_ram(unsigned char ram[MEM_SIZE],
							int pos, int nb_oct);
/*
**							PROCESS
*/
void						live(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						ld(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						st(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						add(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						sub(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						and(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						or(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						xor(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						zjmp(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						ldi(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						sti(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						forc(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						lld(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						lldi(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						lfork(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
void						aff(int arg[3], t_process *process,
							t_storage *storage, unsigned char ocp);
/*
**							PRINT
*/
void						print_instr(int arg[3], unsigned char dest,
							unsigned char nb_arg, t_process *process);
void						print_mem(unsigned char *mem);
void						print_verb(unsigned int cycle);
void						print_result(t_storage *storage);
/*
**							NCURSE
*/
t_writer_list				*get_writers();
void						add_writer(unsigned char content[4],
							unsigned int writer, unsigned int where);
void						display(t_storage *storage);
int							get_x(unsigned int x);
int							get_y(unsigned int y);
void						init(t_storage *storage);
void						erase_process(t_storage *storage);
void						print_new_cycle(t_storage *storage);
void						fill_win(WINDOW *left_win);
void						print_news(WINDOW *win);
void						loop_writers(WINDOW *win, t_writer_list *writers);
void						print_pourcent(unsigned int lives[4],
							WINDOW *win, int y);
void						print_string(WINDOW *win, unsigned char str[4],
							unsigned int id, unsigned int where);
void						print_movement(int origin, int dest,
							t_storage *storage);
/*
**							ERROR
*/
void						ft_error(t_storage *storage, char *name,
							int val, int i);
void						malloc_error(void);
void						fd_error(char *name);
void						size_error(t_champ champ, char *name);
void						magic_error(t_champ champ, char *name);
void						ext_error(char *name);
void						too_many_players_error(int nb_players);
void						no_champ_error(void);
/*
**							FREE
*/
void						free_process(void *s, size_t n);
void						clean(t_storage *storage);

#endif
