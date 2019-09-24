/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:50:40 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 20:45:47 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			found_cmd(t_storage *storage, int *check, char *cmd)
{
	int		i;
	int		j;
	int		cmd_len;

	i = jump_space_tab(DATA.line);
	j = 0;
	cmd_len = (int)ft_strlen(cmd);
	if (ft_strncmp(DATA.line + i, cmd, cmd_len) == 0)
	{
		i += cmd_len;
		i += jump_space_tab(DATA.line + i);
		if (DATA.line[i] != '"')
			return (create_error(storage, SYNTAXE_ERROR));
		i++;
		if (save_name_comment(storage, cmd, i) == ERROR)
			return (ERROR);
	}
	if (DATA.check_name == true && DATA.check_comment == true)
	{
		HEADER.magic = COREWAR_EXEC_MAGIC;
		*check = DONE;
	}
	return (0);
}

int			check_validate(t_storage *storage)
{
	int		i;
	int		len_name;
	int		len_comment;
	int		ret;

	i = jump_space_tab(DATA.line);
	len_name = ft_strlen(NAME_CMD_STRING);
	len_comment = ft_strlen(COMMENT_CMD_STRING);
	if (DATA.line[i] == COMMENT_CHAR || DATA.line[i] == '\0')
		ret = 0;
	else if (ft_strncmp(COMMENT_CMD_STRING, DATA.line + i, len_comment) == 0)
		ret = 0;
	else if (ft_strncmp(NAME_CMD_STRING, DATA.line + i, len_name) == 0)
		ret = 0;
	else
		ret = create_error(storage, SYNTAXE_ERROR);
	return (ret);
}

int			check_line_function(t_storage *storage, int *check)
{
	int		ret;

	ret = 0;
	if (check_validate(storage) == ERROR)
		ret = ERROR;
	else if (found_cmd(storage, check, NAME_CMD_STRING) == ERROR)
		ret = ERROR;
	else if (found_cmd(storage, check, COMMENT_CMD_STRING) == ERROR)
		ret = ERROR;
	return (ret);
}

int			read_header(t_storage *storage)
{
	int				ret;
	int				check;

	check = 0;
	while (check != DONE && (ret = get_next_line(DATA.file_fd, &DATA.line)) > 0)
	{
		if (check_line_function(storage, &check) == ERROR)
		{
			ft_strdel(&DATA.line);
			get_next_line(ERROR, &DATA.line);
			return (ERROR);
		}
		ft_strdel(&DATA.line);
		DATA.num_line++;
	}
	if (ret < 0)
	{
		create_error(storage, GNL_NOREAD);
		get_next_line(ERROR, &DATA.line);
		return (ERROR);
	}
	return (0);
}
