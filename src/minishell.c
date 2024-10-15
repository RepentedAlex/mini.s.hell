/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:16 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/08 11:49:47 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief The main mini.s.hell function ! :D
/// @param argc The number of arguments passed via the CLI.
/// @param argv The arguments passed via the CLI.
/// @param envp The environment variables.
/// @return EXIT_FAILURE on error and EXIT_SUCCESS otherwise.
int	mini_s_hell(int argc, char *argv[], char *envp[])
{
	t_mo_shell	mo_shell;

	(void)argc, (void)argv, (void)envp;
	ft_bzero(&mo_shell, sizeof(t_mo_shell));
	while (1)
	{
		//0. Read input
		mo_shell.og_input = readline(PROMPT);
		// TODO Remove readline's printing the line read

		if (check_open_quotes(mo_shell.og_input) == ERROR)
			return (printf("mini.s.hell: quotes are not closed\n"), ERROR);

		mo_shell.expanded_input = expand_variables(mo_shell.og_input, envp);	// TODO Verif pour variables inexistantes
		printf("1%s\n", mo_shell.expanded_input);	// TODO REMOVE

		mo_shell.splitted_input = setup_first_block(mo_shell.expanded_input);
		printf("2%s\n", mo_shell.splitted_input->str);					//TODO REMOVE

		if (look_for_pipes(&mo_shell.splitted_input) == true)					// TODO
		{
			if (check_pipes_syntax(&mo_shell.splitted_input) == ERROR)			// TODO
				return (printf("mini.s.hell: syntax error near unexpected token '|'\n"), ERROR);

			split_pipes(&mo_shell.splitted_input);								// TODO + define in which field to assign
		}

		if (look_for_redir(&mo_shell.splitted_input) == true)					// TODO
		{
			if (check_redir_syntax(&mo_shell.splitted_input) == ERROR)			// TODO
				return (printf("mini.s.hell: \n"), ERROR);				// TODO Specify character

			split_redir(&mo_shell.splitted_input);
		}

		//TODO SPLIT SPACES TO CLEAN BLOCKS
		split_spaces(&mo_shell.splitted_input);


		// == == == TRANSITION VERS l'EXEC == == ==

		launch_builtins(mo_shell.splitted_input);

	}
	garbage_collect(&mo_shell);
	return (EXIT_SUCCESS);
}

//TODO Might be a good idea to implement a non-interactive version.
int	main(const int argc, char *argv[], char *envp[])
{
	if (isatty(STDIN_FILENO) == 1)
		return (mini_s_hell(argc, argv, envp));
	return (0);
}
