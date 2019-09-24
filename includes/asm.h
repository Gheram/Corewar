/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:30:25 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/18 15:19:57 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# define LIST_ERRO		storage->listerror
# define DATA			storage->data
# define LINE			DATA.line
# define HEADER			storage->header
# define CMD			storage->list_cmd
# define COR			storage->cor_file
# define BODY			storage->cor_file.body
# define FD				storage->cor_file.fd
# define DONE			2

/*
**						ERROR ENUM
*/
typedef enum			e_error_flags
{
	MISSING_FILE = 1,
	NOT_POINT_S = 2,
	FAILED_TO_OPEN = 3,
	NO_NAME = 4,
	NO_COMMENT = 5,
	INVALIDE_LEN_NAME = 6,
	INVALIDE_LEN_COMMENT = 7,
	INVALIDE_HEADER = 8,
	INVALIDE_LABEL_NAME = 9,
	INVALIDE_INDEX_LABEL = 10,
	INVALIDE_DIRECT_LABEL = 11,
	INVALIDE_DIRECT_NUMBER = 12,
	INVALIDE_INDEX_NUMBER = 13,
	INVALIDE_PARAMETER = 14,
	INVALIDE_REGISTER_PARAMETER = 15,
	INVALIDE_REGISTER_NUMBER = 16,
	INVALIDE_NUMBER_ARGUMENTS = 17,
	INVALIDE_ARGUMENT_TYPES = 18,
	MAX_SIZE = 19,
	FAILED_TO_CREATE_FILE = 20,
	GNL_NOREAD = 21,
	SYNTAXE_ERROR = 22,
	MALLOC_ERROR = 23,
	LABEL_NOT_FOUND = 24
}						t_error_flags;

/*
**						STRUCTURES
*/
typedef struct			s_error
{
	int					num_line;
	size_t				index_error;
	char				*filename;
}						t_error;

typedef struct			s_cmd
{
	unsigned int		opt;
	int					nb;
	size_t				call_label;
	char				**arg;
	char				*label;
}						t_cmd;

typedef struct			s_list_cmd
{
	t_cmd				*content;
	size_t				content_size;
	struct s_list_cmd	*next;
}						t_list_cmd;

typedef struct			s_listerror
{
	t_error				*content;
	size_t				content_size;
	struct s_listerror	*next;
}						t_listerror;

typedef struct			s_label
{
	unsigned int		pos;
	unsigned int		index;
	char				*name;
	int					size;
}						t_label;

typedef struct			s_corfile
{
	t_label				*lab_cmd;
	t_label				*label;
	unsigned char		*body;
	char				*name;
	unsigned int		i;
	unsigned int		j;
	int					fd;
}						t_corfile;

typedef struct			s_data
{
	int					check_name;
	int					check_comment;
	int					file_fd;
	int					num_line;
	char				*filename;
	size_t				call_label;
	size_t				total_label;
	size_t				nb_cmd;
	char				*line;
}						t_data;

typedef struct			s_storage
{
	t_listerror			*listerror;
	t_list_cmd			*list_cmd;
	t_header			header;
	t_data				data;
	t_corfile			cor_file;
}						t_storage;

/*
** 						ERROR FONCTION
*/
int						invalide_filename(const char *file, t_storage *storage);
int						check_validity(const char *file, t_storage *storage);
void					ft_print_words_tables(char **tab);
int						create_error(t_storage *storage, int index_error);
int						read_header(t_storage *storage);
int						read_body(t_storage *storage);
int						open_file(const char *file, t_storage *storage);
/*
**						PARSE
*/
int						init_data(t_storage *storage);
int						jump_space_tab(char *line);
int						save_cmd(t_storage *storage, char *line,
						int j, t_cmd *cmd);
int						check_reg(t_storage *storage, char *line);
int						check_dir(t_storage *storage, char *line);
int						check_ind(t_storage *storage, char *line);
int						seperator_arg(t_storage *storage, t_cmd *cmd,
						char *line, int j);
int						check_is_value(char *line);
int						check_is_label(char *line);
int						count_arg(char *line);
int						check_is_label(char *line);
int						check_is_value(char *line);
int						check_cmd(t_storage *storage, char *line, t_cmd *cmd);
int						create_label(t_storage *storage, char *label);
int						save_name_comment(t_storage *storage, char *cmd, int i);
char					*check_label_line(t_storage *storage, char *line);
/*
** 						CREATE CORFILE
*/
int						create_corfile(t_storage *storage);
void					write_in_corfile(unsigned char *tab,
						size_t size, int fd);
int						find_arg(t_cmd *cmd, size_t i,
						t_storage *storage, int n);
void					calc_ocp(t_cmd *cmd, t_storage *storage);
int						find_cmd(char *arg, t_storage *storage);
void					set_zero(unsigned char *tab, size_t *size);
void					write_magic(unsigned int magic, int fd);
void					write_prog_name(char *name, int fd);
void					write_prog_size(unsigned int size, int fd);
void					write_comment(char *com, int fd);
int						replace_label(t_storage *storage);
void					index_lab(int dir_type,
						t_storage *storage, char *label);
void					mem_lab_pos(t_storage *storage, char *label);
/*
**						FREE
*/
void					clean_data(t_storage *storage);
void					clean(t_storage *storage);
void					clean_error(t_storage *storage);
void					free_corfile(t_storage *storage);
void					free_data(t_storage *storage);
/*
**						PRINT MESSAGE
*/
void					print_create_msg(t_storage *storage);
void					print_msg_error(t_storage *storage);

#endif
