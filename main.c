/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakoch <jakoch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 12:48:31 by jakoch            #+#    #+#             */
/*   Updated: 2026/06/02 14:31:51 by jakoch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**
**	This main was created only for local testing during eval and self tests.
**	It shouldn't be submitted to your 42 Student Github for peer-evaluation and moulinette.
**	Same goes for the files folder containing the test fd's.
**	It is just a basic tester for the mandatory part using one fd at a time.
**
*/

#include "get_next_line.h"
#include <stdio.h>  // printf
#include <fcntl.h>  // open, O_RDONLY

int	main(int argc, char **argv)
{
	int	fd;
		char *line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (printf("Choose a correct file name!\n"), 1);
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		return (0);
	}
	else
	{
		printf("======== WELCOME TO GNL TESTER =========\n");
		printf("Choose from these file names: \n");
		printf("files/long_no_nl.txt \n");
		printf("files/long_with_nl.txt \n");
		printf("files/only_one_nl.txt \n");
		printf("files/short_no_nl.txt \n");
		printf("files/empty.txt \n");
		printf("files/many_nl_no_text.txt \n");
		printf("files/text_nl_inbetween.txt \n");
		printf("files/varying_lengths_nl.txt \n");
		printf("files/10k.txt \n");
		printf("files/short_with_nl.txt \n\n");
		
		printf("===== FEEL FREE TO ADD YOUR OWN TEST ====== \n");
		printf("files/YOUR_FILE.txt \n\n");
		// ./test only works when compiling with cc <files> -o test
		printf("======= USAGE =======\n");
		printf("./test FILE_NAME | cat -e\n\n");
		
		printf("========= CHECKING MEMORY LEAKS ==========\n");
		printf("valgrind ./test FILE_NAME | cat -e\n\n");
	}
}
