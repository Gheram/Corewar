/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 20:52:07 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 20:45:32 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_end_line(t_storage *storage, int i)
{
	i++;
	i += jump_space_tab(DATA.line + i);
	if (DATA.line[i] != COMMENT_CHAR && DATA.line[i] != '\0')
		return (create_error(storage, INVALIDE_HEADER));
	return (0);
}

static int	save_name(t_storage *storage, int i)
{
	int		k;

	k = 0;
	while (1)
	{
		if (k > PROG_NAME_LENGTH)
			return (create_error(storage, INVALIDE_LEN_NAME));
		if (DATA.line[i] == '\0')
		{
			ft_strdel(&DATA.line);
			if (get_next_line(DATA.file_fd, &DATA.line) <= 0)
				return (create_error(storage, GNL_NOREAD));
			DATA.num_line++;
			HEADER.prog_name[k++] = '\n';
			i = 0;
		}
		else if (DATA.line[i] == '"')
			break ;
		else
			HEADER.prog_name[k++] = DATA.line[i++];
	}
	HEADER.prog_name[k] = '\0';
	return (check_end_line(storage, i));
}

static int	save_comment(t_storage *storage, int i)
{
	int		k;

	k = 0;
	while (1)
	{
		if (k > COMMENT_LENGTH)
			return (create_error(storage, INVALIDE_LEN_COMMENT));
		if (DATA.line[i] == '\0')
		{
			ft_strdel(&DATA.line);
			if (get_next_line(DATA.file_fd, &DATA.line) <= 0)
				return (create_error(storage, GNL_NOREAD));
			HEADER.comment[k++] = '\n';
			DATA.num_line++;
			i = 0;
		}
		else if (DATA.line[i] == '"')
			break ;
		else
			HEADER.comment[k++] = DATA.line[i++];
	}
	HEADER.comment[k] = '\0';
	return (check_end_line(storage, i));
}

int			save_name_comment(t_storage *storage, char *cmd, int i)
{
	if (DATA.check_name != true && ft_strcmp(NAME_CMD_STRING, cmd) == 0)
	{
		if (save_name(storage, i) == ERROR)
			return (ERROR);
		DATA.check_name = true;
	}
	if (DATA.check_comment != true && ft_strcmp(COMMENT_CMD_STRING, cmd) == 0)
	{
		if (save_comment(storage, i) == ERROR)
			return (ERROR);
		DATA.check_comment = true;
	}
	return (0);
}
