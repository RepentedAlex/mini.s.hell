/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitco <apetitco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:43:32 by apetitco          #+#    #+#             */
/*   Updated: 2024/10/23 13:43:36 by apetitco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char	**get_splash_screen_part1(void)
{
	static char	*part1[] = {
		"\e[0;91m",
		"   ███   ▒██▒ ▒▒▒▒▒▒ ▒██████▒  ▒▒▒    ██        ▒▒▒▒▒▒  "
		"▒▒▒▒▒▒    ▒▒▒    █████░",
		"   ███   ███ ░██████ ███████░ ▒███   ░██       ▒██████ "
		"░██████   ▒███   ░██████",
		"   ███  ▒███           ▒█▒           ▒██      ▒██                 "
		"           ░█░",
		"  ░███  ███▒ ▒▒▒▒▒▒    ██░   ░░░░░   ██░     ▒██ ░░░░  "
		"░░░░░    ░░░░░   ░░░░░▒█",
		NULL
	};

	return (part1);
}

static char	**get_splash_screen_part2(void)
{
	static char	*part2[] = {
		"  ▒███ ▒███░ ██████▒   ██   ░█████░  ██     ░██  ████  "
		"█████▒  ░█▒░██░  ██████▒",
		"  ██▒█░█░██  ██▒▒▒▒    ██   ██▒░██░  ██      ██  ░▒██ "
		"░██░░░   ██  ██░  ██▒██░",
		"  ██░███░██ ░██       ░██  ░██  ██░ ░██      ██▒  ░██ "
		"░█▒     ░██  ██░ ░██ ██░",
		" ░█▒ ██░░██ ▒█▒       ▒█▒  ██░  ▒█▒ ░█▒      ░██  ▒█▒ "
		"██▒     ██░  ░█░ ▒█▒ ███",
		" ▒█░ ██ ██▒ ██████▒   ██░ ░██   ▒█▒ ██████░   ██████░ "
		"██████ ░█▒   ░█▒ ██░ ▒██",
		NULL
	};

	return (part2);
}

static char	**get_splash_screen_part3(void)
{
	static char	*part3[] = {
		" ██  ▒  ▒▒  ▒▒▒▒▒▒    ▒▒  ▒▒    ░▒▒ ░░░░░░    ░░░░░░  "
		"░░░░░  ░░    ░▒▒ ▒▒  ░██",
		" ██                                                "
		"                         ▒█░",
		" ██                                                "
		"                          ██░",
		"░█                                                       "
		"                     █▒",
		"▒█                    "
		"\e[0;36m"
		"Made with <3 by apetitco && llabonde"
		"\e[0;91m"
		"                    ██",
		"\e[0;0m",
		NULL
	};

	return (part3);
}

void	splash_screen(void)
{
	char		**splash[3];
	int			i;
	int			j;

	splash[0] = get_splash_screen_part1();
	splash[1] = get_splash_screen_part2();
	splash[2] = get_splash_screen_part3();
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (splash[i][j] != NULL)
		{
			printf("%s\n", splash[i][j]);
			j++;
		}
		i++;
	}
}
