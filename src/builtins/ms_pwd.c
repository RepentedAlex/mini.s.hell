/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:53:08 by apetitco          #+#    #+#             */
/*   Updated: 2024/12/10 16:17:53 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft.h>

/// @brief Handles the case where the "PWD" variable is not found in the shell
/// environment.
/// Adds the current working directory as a new "PWD" entry in the environment.
/// @param mo_shell Pointer to the shell structure containing the shell
/// environment.
/// @param cwd String containing the current working directory in the format
/// "PWD=<directory>". Must not be NULL.
/// @param created_wd Pointer to a dynamically allocated string used to store
/// the new "PWD" variable.
/// This will be populated and added to the environment.
/// @return Returns NO_ERROR on success or ERROR if adding the new "PWD"
/// variable to the environment fails.
static t_error	no_var_in_env(t_mo_shell *mo_shell, char *cwd, char *created_wd)
{
	printf("%s\n", &cwd[4]);
	created_wd = NULL;
	created_wd = append(created_wd, cwd, ft_strlen(cwd));
	free(cwd);
	if (add_str_to_ra(&mo_shell->shell_env, created_wd) == ERROR)
		return (ERROR);
	return (NO_ERROR);
}

/// @brief Retrieves the current working directory and stores it in a temporary
/// buffer.
/// @param cwd Pointer to a pre-allocated buffer for the current working
/// directory. Can be NULL.
/// @param tmp Pointer to a string that will hold the result of `getcwd`. Must
/// be freed by the caller if non-NULL.
/// @return Returns NO_ERROR on success or ERROR if retrieving the current
/// working directory fails. On failure, an error message is printed to STDERR.
static t_error	retrieve_cwd(char *cwd, char **tmp)
{
	*tmp = getcwd(cwd, DEF_BUF_SIZ);
	if (*tmp == NULL)
	{
		free(*tmp);
		ft_putstr_fd("mini.s.hell: error retrieving current directory\n", \
			STDERR_FILENO);
		return (ERROR);
	}
	return (NO_ERROR);
}

/// @brief Handles the `pwd` built-in command, which prints the current working
/// directory.
/// @param args Command-line arguments passed to the `pwd` command. If an
/// invalid option is passed (e.g., an argument starting with '-'), an error
/// message is displayed, and the function exits with a non-zero status.
/// @param mo_shell Pointer to the shell structure containing the shell's state,
/// including environment variables and the last exit status.
/// @param cmd Pointer to the command structure (not used in this function,
/// provided for consistency with other built-in functions).
/// @return Returns 0 on success. Returns 2 if an invalid option is passed.
/// Returns 1 if there is an error retrieving the current working directory.
int	ms_pwd(char **args, t_mo_shell *mo_shell, t_cmd *cmd)
{
	int		var_index;
	char	*var_content;
	char	*cwd;
	char	*tmp;
	char	*created_wd;

	((void)cmd, created_wd = NULL);
	cwd = NULL;
	if (args && args[1] && args[1][0] == '-')
		return (write(1, "Invalid option\n", 15), \
			mo_shell->last_exit_status = 2, 2);
	if (retrieve_cwd(cwd, &tmp) == ERROR)
		return (1);
	cwd = ft_strdup("PWD=");
	cwd = append(cwd, tmp, DEF_BUF_SIZ);
	(free(tmp), tmp = NULL);
	var_index = var_exst("PWD", mo_shell->shell_env);
	if (var_index == -1)
		return (no_var_in_env(mo_shell, cwd, created_wd));
	var_content = mo_shell->shell_env[var_index];
	while (*var_content != '=')
		var_content++;
	var_content++;
	write(1, var_content, ft_strlen(var_content));
	return (free(cwd), cwd = NULL, write(1, "\n", 1), 0);
}
