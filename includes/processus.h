/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigre <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 18:53:29 by tigre             #+#    #+#             */
/*   Updated: 2019/09/17 22:16:04 by tigre            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSUS_H
# define PROCESSUS_H

typedef void	(*t_instruction)(int *, t_process *,
				t_storage *, unsigned char);

static	t_instruction g_processus[] =
{
	NULL,
	&live,
	&ld,
	&st,
	&add,
	&sub,
	&and,
	&or,
	&xor,
	&zjmp,
	&ldi,
	&sti,
	&forc,
	&lld,
	&lldi,
	&lfork,
	&aff,
	NULL
};

#endif
