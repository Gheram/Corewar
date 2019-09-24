/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 20:54:49 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/18 13:38:32 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int		check_doublon_l(t_storage *storage, char *label)
{
	t_list_cmd	*tmp;

	tmp = CMD;
	while (tmp)
	{
		if (tmp->content->label != NULL)
			if (ft_strcmp(tmp->content->label, label) == 0)
			{
				free(label);
				return (ERROR);
			}
		tmp = tmp->next;
	}
	DATA.total_label++;
	create_label(storage, label);
	return (1);
}

static int		check_label(t_storage *storage, char *line, t_cmd *cmd)
{
	int			i;
	char		*tmp;
	char		*label;

	i = 0;
	tmp = line;
	while (line[i] && line[i] != LABEL_CHAR && line[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
			return (create_error(storage, SYNTAXE_ERROR));
		i++;
	}
	label = ft_strndup(line, i);
	tmp = tmp + i + 1;
	tmp += jump_space_tab(tmp);
	if (check_doublon_l(storage, label) == ERROR)
		return (ERROR);
	if ((tmp = check_label_line(storage, tmp)) == NULL)
		return (0);
	if (ft_strcmp(tmp, "*") == 0)
		return (DONE);
	if (check_cmd(storage, tmp, cmd) == ERROR)
		return (ERROR);
	return (0);
}

int				check_cmd(t_storage *storage, char *line, t_cmd *cmd)
{
	int			j;
	size_t		len;
	char		*tmp;
	t_bool		enter;

	j = -1;
	enter = false;
	len = 0;
	while (line[len] != '\0' && line[len] != ' ' && line[len] != '\t')
		len++;
	while (++j < 16)
	{
		if (ft_strncmp(g_op_tab[j].name, line, len) == 0)
		{
			tmp = line + len;
			enter = true;
			if ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0')
				return (save_cmd(storage, line, j, cmd));
			else if ((*tmp != 'i' && j != 0) || *tmp == '\0')
				return (create_error(storage, SYNTAXE_ERROR));
		}
	}
	if (j == 16 && cmd->label != NULL && enter == false)
		return (create_error(storage, SYNTAXE_ERROR));
	return (0);
}

static int		parse_line(char *line, t_storage *storage)
{
	int			ret;
	t_cmd		cmd;

	ret = 0;
	ft_bzero(&cmd, sizeof(t_cmd));
	line += jump_space_tab(line);
	if (*line == '\n' || *line == COMMENT_CHAR || *line == '\0')
		return (ret);
	ret = check_cmd(storage, line, &cmd);
	if (ret == 1)
		return (ret);
	else if (ret == 0)
		ret = check_label(storage, line, &cmd);
	if (ret == DONE)
		return (DONE);
	return (ret);
}

int				read_body(t_storage *storage)
{
	int			ret;
	int			back;

	LINE = NULL;
	while ((ret = get_next_line(DATA.file_fd, &LINE)) > 0)
	{
		back = parse_line(LINE, storage);
		if (back == ERROR)
		{
			ft_strdel(&LINE);
			get_next_line(ERROR, &LINE);
			return (ERROR);
		}
		ft_strdel(&LINE);
		DATA.num_line++;
		if (back == DONE)
			break ;
	}
	if (ret < 0)
	{
		get_next_line(ERROR, &LINE);
		return (create_error(storage, GNL_NOREAD));
	}
	return (0);
}
