/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghtouman <ghtouman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:41:09 by ghtouman          #+#    #+#             */
/*   Updated: 2019/09/16 15:58:41 by ghtouman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void			msg_error_one(t_error error)
{
	if (error.index_error == MISSING_FILE)
		ft_putstr_fd("does not exist.", 2);
	if (error.index_error == NOT_POINT_S)
		ft_putstr_fd("is not a point s.", 2);
	if (error.index_error == FAILED_TO_OPEN)
		ft_putstr_fd("can not be open.", 2);
	if (error.index_error == GNL_NOREAD)
		ft_putstr_fd("can not be read.", 2);
	if (error.index_error == NO_NAME)
		ft_putstr_fd("does not have a name.", 2);
	if (error.index_error == NO_COMMENT)
		ft_putstr_fd("does not have a comment.", 2);
	if (error.index_error == INVALIDE_LEN_NAME)
		ft_putstr_fd("have a invalide size name. In the line : ", 2);
	if (error.index_error == INVALIDE_LEN_COMMENT)
		ft_putstr_fd("have a invalide size comment. In the line : ", 2);
	if (error.index_error == INVALIDE_HEADER)
		ft_putstr_fd("have a invalide header. In the line : ", 2);
	if (error.index_error == INVALIDE_LABEL_NAME)
		ft_putstr_fd("have a invalide label. In the line : ", 2);
	if (error.index_error == INVALIDE_INDEX_LABEL)
		ft_putstr_fd("have a invalide index label. In the line : ", 2);
	if (error.index_error == INVALIDE_DIRECT_LABEL)
		ft_putstr_fd("have a invalide direct label. In the line : ", 2);
}

static void			msg_error_two(t_error error)
{
	if (error.index_error == INVALIDE_DIRECT_NUMBER)
		ft_putstr_fd("have a invalide direct number. In the line : ", 2);
	if (error.index_error == INVALIDE_INDEX_NUMBER)
		ft_putstr_fd("have a invalide index number. In the line : ", 2);
	if (error.index_error == INVALIDE_PARAMETER)
		ft_putstr_fd("have a invalide parameter. In the line : ", 2);
	if (error.index_error == INVALIDE_REGISTER_PARAMETER)
		ft_putstr_fd("have a invalide register parameter. In the line : ", 2);
	if (error.index_error == INVALIDE_REGISTER_NUMBER)
		ft_putstr_fd("have a invalide direct number. In the line : ", 2);
	if (error.index_error == INVALIDE_NUMBER_ARGUMENTS)
		ft_putstr_fd("have a invalide index number. In the line : ", 2);
	if (error.index_error == INVALIDE_ARGUMENT_TYPES)
		ft_putstr_fd("have a invalide parameter. In the line : ", 2);
	if (error.index_error == MAX_SIZE)
		ft_putstr_fd("have invalide size.", 2);
	if (error.index_error == FAILED_TO_CREATE_FILE)
		ft_putstr_fd("failed to create the .cor.", 2);
	if (error.index_error == SYNTAXE_ERROR)
		ft_putstr_fd("have a syntaxe error. In the line : ", 2);
	if (error.index_error == MALLOC_ERROR)
		ft_putstr_fd("have a malloc faile.", 2);
	if (error.index_error == LABEL_NOT_FOUND)
		ft_putstr_fd("label no found.", 2);
}

static void			call_msg(t_error error)
{
	ft_putstr_fd("The file: < ", 2);
	ft_putstr_fd(error.filename, 2);
	ft_putstr_fd(" > ", 2);
	msg_error_one(error);
	msg_error_two(error);
	if (error.num_line == 0 && error.index_error == SYNTAXE_ERROR)
	{
		ft_putnbr_fd(error.num_line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
	else if (error.num_line > 0)
	{
		ft_putnbr_fd(error.num_line + 1, 2);
		ft_putstr_fd(".\n", 2);
	}
	else
		ft_putstr_fd("\n", 2);
}

void				print_msg_error(t_storage *storage)
{
	t_listerror		*tmp;

	tmp = LIST_ERRO;
	while (tmp)
	{
		call_msg(*tmp->content);
		tmp = tmp->next;
	}
}
