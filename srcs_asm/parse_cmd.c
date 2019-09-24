/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:44:48 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/16 13:59:25 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		check_multi_args(t_storage *storage, char *line, int j, int k)
{
	int			ret;

	if (g_op_tab[j].bnry_args[k] == (T_REG + T_DIR))
	{
		ret = check_reg(storage, line);
		(ret == 0) ? ret = check_dir(storage, line) : ret;
	}
	if (g_op_tab[j].bnry_args[k] == (T_REG + T_IND))
	{
		ret = check_reg(storage, line);
		(ret == 0) ? ret = check_ind(storage, line) : ret;
	}
	if (g_op_tab[j].bnry_args[k] == (T_IND + T_DIR))
	{
		ret = check_ind(storage, line);
		(ret == 0) ? ret = check_dir(storage, line) : ret;
	}
	if (g_op_tab[j].bnry_args[k] == (T_REG + T_DIR + T_IND))
	{
		ret = check_reg(storage, line);
		(ret == 0) ? ret = check_dir(storage, line) : ret;
		(ret == 0) ? ret = check_ind(storage, line) : ret;
	}
	return (ret);
}

static int		found_bnry_args(t_storage *storage, char *line, int j, int k)
{
	int			ret;

	if (g_op_tab[j].bnry_args[k] == T_REG)
		ret = check_reg(storage, line);
	else if (g_op_tab[j].bnry_args[k] == T_DIR)
		ret = check_dir(storage, line);
	else if (g_op_tab[j].bnry_args[k] == T_IND)
		ret = check_ind(storage, line);
	else
		ret = check_multi_args(storage, line, j, k);
	return (ret);
}

static int		check_bnry_args(t_storage *storage, char *line, int j)
{
	int			k;
	int			ret;

	k = -1;
	ret = 0;
	while (++k < 3)
	{
		(*line == SEPARATOR_CHAR) ? line++ : line;
		(*line == ' ' || *line == '\t') ? line += jump_space_tab(line) : line;
		if (g_op_tab[j].bnry_args[k] != 0)
		{
			ret = found_bnry_args(storage, line, j, k);
			if (ret == ERROR)
				return (ERROR);
			line += ret;
			line += jump_space_tab(line);
		}
		else
		{
			line += jump_space_tab(line);
			if (*line != COMMENT_CHAR && *line != '\0')
				return (create_error(storage, SYNTAXE_ERROR));
		}
	}
	return (0);
}

int				create_cmd(t_storage *storage, char *line, int j, t_cmd *cmd)
{
	t_list_cmd	*new_cmd;

	if (!(cmd->arg = (char**)malloc(sizeof(char*) * (g_op_tab[j].nb_arg + 2))))
		return (create_error(storage, MALLOC_ERROR));
	cmd->arg[0] = g_op_tab[j].name;
	if (seperator_arg(storage, cmd, line, j) == ERROR)
		return (ERROR);
	cmd->nb = g_op_tab[j].nb_arg;
	new_cmd = (t_list_cmd*)ft_lstnew(cmd, sizeof(t_cmd));
	ft_lstpush_back((t_list**)&CMD, (t_list*)new_cmd);
	if (CMD == NULL)
		return (ERROR);
	return (0);
}

int				save_cmd(t_storage *storage, char *line, int j, t_cmd *cmd)
{
	int			i;
	char		*tmp;

	i = 0;
	line = line + ft_strlen(g_op_tab[j].name);
	if (*line != ' ' && *line != '\t' && *line == '\0')
		return (create_error(storage, SYNTAXE_ERROR));
	line = line + jump_space_tab(line);
	tmp = line;
	if (g_op_tab[j].nb_arg != count_arg(line))
		return (create_error(storage, INVALIDE_NUMBER_ARGUMENTS));
	if (check_bnry_args(storage, line, j) == ERROR)
		return (ERROR);
	if (create_cmd(storage, tmp, j, cmd) == ERROR)
		return (ERROR);
	DATA.nb_cmd++;
	return (1);
}
