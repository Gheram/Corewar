/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 16:59:15 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/17 22:16:23 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_reg(t_storage *storage, char *line)
{
	int		reg;
	int		i;

	if (line[0] == DIRECT_CHAR || line[0] == LABEL_CHAR
		|| (ft_isdigit(line[0]) == 1) || line[0] == '-')
		return (0);
	if (line[0] == 'r')
	{
		reg = ft_atoi(line + 1);
		i = ft_intlen(reg);
		if (line[1] == '0')
			i++;
		if (reg <= REG_NUMBER && reg > 0)
			return (1 + i);
		else
			return (create_error(storage, INVALIDE_REGISTER_NUMBER));
	}
	else
		return (create_error(storage, INVALIDE_REGISTER_PARAMETER));
	return (0);
}

static int	check_value_ind(t_storage *storage, char *line, int i, int len)
{
	if ((len = check_is_value(line + i)) == ERROR)
		return (create_error(storage, INVALIDE_INDEX_NUMBER));
	return (i + len + jump_space_tab(line + len));
}

static int	check_label_dir(t_storage *storage, char *line)
{
	int		len;

	if ((len = check_is_label(line + 2)) == ERROR)
		return (create_error(storage, INVALIDE_DIRECT_LABEL));
	return (len + jump_space_tab(line + len) + 2);
}

int			check_dir(t_storage *storage, char *line)
{
	int		len;
	int		i;

	if (line[0] == 'r' || line[0] == LABEL_CHAR || (ft_isdigit(line[0]) == 1)
		|| line[0] == '-')
		return (0);
	i = 1;
	if (line[0] == DIRECT_CHAR)
	{
		(line[i] == '-') ? i = 2 : i;
		if (line[i] == LABEL_CHAR)
			return (check_label_dir(storage, line));
		else if (ft_isdigit(line[i]) == 1)
		{
			if ((len = check_is_value(line + i)) == ERROR)
				return (create_error(storage, INVALIDE_DIRECT_NUMBER));
			return (i + len + jump_space_tab(line + i + len));
		}
		else
			return (create_error(storage, SYNTAXE_ERROR));
	}
	else
		return (create_error(storage, SYNTAXE_ERROR));
	return (0);
}

int			check_ind(t_storage *storage, char *line)
{
	int		len;
	int		i;

	i = 0;
	if (line[i] == 'r' || line[i] == DIRECT_CHAR)
		return (0);
	(line[i] == '-') ? i = 1 : i;
	len = 0;
	if (line[i] == LABEL_CHAR || (ft_isdigit(line[i]) == 1))
	{
		if (line[i] == LABEL_CHAR)
		{
			len = check_is_label(line + 1 + i);
			if (len == ERROR)
				return (create_error(storage, INVALIDE_INDEX_LABEL));
			return (len + jump_space_tab(line + len) + 1);
		}
		if (ft_isdigit(line[i]) == 1)
			return (check_value_ind(storage, line, i, len));
	}
	else
		return (create_error(storage, SYNTAXE_ERROR));
	return (0);
}
