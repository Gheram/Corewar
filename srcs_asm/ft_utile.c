/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:34:51 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/18 15:23:09 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				jump_space_tab(char *line)
{
	int			jump;

	jump = 0;
	while (line[jump] == ' ' || line[jump] == '\t')
		jump++;
	return (jump);
}

int				create_label(t_storage *storage, char *label)
{
	t_list_cmd	*new_cmd;
	t_cmd		cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.label = label;
	if (!(cmd.arg = (char**)malloc(sizeof(char*) * 1)))
		return (create_error(storage, MALLOC_ERROR));
	cmd.nb = -1;
	new_cmd = (t_list_cmd*)ft_lstnew(&cmd, sizeof(t_cmd));
	ft_lstpush_back((t_list**)&CMD, (t_list*)new_cmd);
	if (CMD == NULL)
		return (ERROR);
	return (0);
}

static int		more_label(t_storage *storage, char *line)
{
	int			i;
	t_bool		no_label;

	i = 0;
	no_label = false;
	while (line[i] && line[i] != LABEL_CHAR && line[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
			no_label = true;
		i++;
	}
	if (no_label == true)
		return (0);
	DATA.total_label++;
	create_label(storage, ft_strndup(line, i));
	i += jump_space_tab(LINE);
	return (i);
}

char			*check_label_line(t_storage *storage, char *line)
{
	int			i;
	int			ret;

	i = 0;
	if (line[0] != '\0' && line[0] != COMMENT_CHAR)
		return (line);
	while (1)
	{
		ft_strdel(&LINE);
		if ((ret = get_next_line(DATA.file_fd, &LINE)) <= 0)
		{
			if (ret < 0)
				create_error(storage, GNL_NOREAD);
			else if (ret == 0)
				return ("*");
			return (NULL);
		}
		i = 0;
		DATA.num_line++;
		i += jump_space_tab(LINE);
		i += more_label(storage, LINE + i);
		if (LINE[i] != COMMENT_CHAR && LINE[i] != '\0')
			return (LINE + i);
	}
	return (NULL);
}

void			print_create_msg(t_storage *storage)
{
	ft_putstr_fd("Writing output program to ", 1);
	ft_putstr_fd(DATA.filename, 1);
	ft_putstr_fd(".cor\n", 1);
	free_corfile(storage);
}
