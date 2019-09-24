/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:04:13 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/16 13:50:37 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_arg(char *line)
{
	int		nb_arg;
	int		i;

	nb_arg = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR)
			break ;
		if (line[i] == SEPARATOR_CHAR)
			nb_arg++;
		i++;
	}
	return (nb_arg);
}

static int	len_arg(t_cmd *cmd, int i, char *line)
{
	int		len;
	int		multi;

	len = 0;
	(i == 1) ? multi = 0X1 : i;
	(i == 2) ? multi = 0X100 : i;
	(i == 3) ? multi = 0X10000 : i;
	(*line == 'r') ? cmd->opt += 1 * multi : *line;
	if (*line == '%')
		cmd->opt += 2 * multi;
	if (*line == '-')
	{
		len++;
		line = line + 1;
	}
	if (ft_isdigit(*line) == 1)
		cmd->opt += 3 * multi;
	if (*line == ':')
		cmd->opt += 3 * multi;
	while (*line != ',' && *line != '\t' && *line != ' ' && *line != '\0')
	{
		len++;
		line++;
	}
	return (len);
}

int			seperator_arg(t_storage *storage, t_cmd *cmd, char *line, int j)
{
	int		i;
	int		len;

	i = 1;
	while (i <= g_op_tab[j].nb_arg)
	{
		len = 0;
		if ((len = len_arg(cmd, i, line)) == ERROR)
			return (create_error(storage, MALLOC_ERROR));
		if ((cmd->arg[i] = ft_strndup(line, len)) == NULL)
			return (create_error(storage, MALLOC_ERROR));
		if (ft_strchr(cmd->arg[i], ':') != NULL)
		{
			DATA.call_label++;
			cmd->opt += i * 0X1000000;
		}
		line = line + len;
		line = line + jump_space_tab(line);
		if (*line == ',')
			line++;
		line = line + jump_space_tab(line);
		i++;
	}
	return (0);
}

int			check_is_label(char *line)
{
	int		i;
	int		ret;

	i = 0;
	if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
		return (ERROR);
	i++;
	ret = 1;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i += jump_space_tab(line + i);
		if (line[i] == SEPARATOR_CHAR ||
			line[i] == COMMENT_CHAR || line[i] == '\0')
			break ;
		if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
			return (ERROR);
		i++;
		ret++;
	}
	return (ret);
}

int			check_is_value(char *line)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i += jump_space_tab(line + i);
		if (line[i] == SEPARATOR_CHAR ||
			line[i] == COMMENT_CHAR || line[i] == '\0')
			break ;
		if (ft_isdigit(line[i]) == 0)
			return (ERROR);
		i++;
		ret++;
	}
	return (ret);
}
