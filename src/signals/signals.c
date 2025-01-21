/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:04 by llabonde          #+#    #+#             */
/*   Updated: 2025/01/03 14:22:33 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_quit_signal(void)
{
	struct termios	tty;

	if (tcgetattr(STDIN_FILENO, &tty) < 0)
		return ;
	tty.c_cc[VQUIT] = _POSIX_VDISABLE;
	tty.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
		return ;
}

/// @brief Clears the current readline input line.
/// This function erases the content of the current line in the readline buffer
/// and prepares for a new input line.

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

/// @brief Handles the `SIGINT` (interrupt) signal.
/// @param code The signal code, not used in this handler.
/// This function is called when the process receives the `SIGINT` signal
/// (typically from pressing Ctrl+C). It clears the current readline input,
/// prints a newline, and redisplays the prompt if `g_signal_pid` is 0.
static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	clear_rl_line();
	if (g_signal_pid == 0)
		rl_redisplay();
}

/// @brief Handles the `SIGABRT` (abort) signal.
/// @param code The signal code, not used in this handler.
/// This function is called when the process receives the `SIGABRT` signal.
/// It writes "abort" to standard output to inform the user that the process
/// was aborted.
static void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}

/// @brief Sets up custom signal handlers for the shell.
/// This function configures the shell to handle `SIGINT` (interrupt),
/// `SIGABRT` (abort), and ignore `SIGQUIT` (quit) signals.
/// `SIGINT` and `SIGABRT` signals are linked to custom handler functions to
/// manage shell behavior, while `SIGQUIT` is ignored.
/// The signal handlers are set to provide more control over how the shell
/// responds to these signals.
void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
	disable_quit_signal();
}
