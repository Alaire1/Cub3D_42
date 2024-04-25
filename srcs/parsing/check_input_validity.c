/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_validity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraban <akaraban.student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:09:23 by narigi-e          #+#    #+#             */
/*   Updated: 2024/04/23 21:01:15 by akaraban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <errno.h>
#include <unistd.h>
void	print_error(char *error)
{
	char	*color_error;

	if (error == NULL)
		return ;
	color_error = malloc(ft_strlen(RED) + ft_strlen(error)
			+ ft_strlen(RESET) + 2);
	// if (color_error == NULL)
	// {
	// 	(void)write(2, "Memory allocation failed\n", 24);
	// 	exit(ERROR);
	// }
	ft_strcpy(color_error, RED);
	ft_strcat(color_error, error);
	ft_strcat(color_error, RESET);
	ft_strcat(color_error, "\n");
	write(2, color_error, ft_strlen(color_error));
	free(color_error);
}

static int	check_argc(int argc)
{
	if (argc > 2)
	{
		print_error("Too many arguments");
		return (ERROR);
	}
	else if (argc < 2)
	{
		print_error("Too few arguments");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_file_extension(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension == NULL)
	{
		print_error("No file extension");
		return (ERROR);
	}
	else if (ft_strcmp(extension, ".cub") != 0)
	{
		print_error("Invalid file extension");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			print_error("File does not exist");
		else if (errno == EACCES)
			print_error("Permission denied");
		else
			print_error("An error occurred");
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

int	check_for_valid_input(char **argv, int argc)
{
	if (check_argc(argc) == ERROR)
		return (ERROR);
	if (check_file_extension(argv[1]) == ERROR)
		return (ERROR);
	if (check_file(argv[1]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
