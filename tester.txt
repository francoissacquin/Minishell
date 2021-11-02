/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:01:49 by ogenser           #+#    #+#             */
/*   Updated: 2021/08/31 16:03:36 by ogenser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
#include <string.h>
#include "libft/libft.h"
#include <unistd.h>

# define NOCOLOR printf("\033[0m");
# define RED  printf("\033[0;31m");
# define GREEN  printf("\033[0;32m");
# define ORANGE  printf("\033[0;33m");
# define BLUE  printf("\033[0;34m");
# define PURPLE  printf("\033[0;35m");
# define CYAN  printf("\033[0;36m");
# define LIGHTGRAY  printf("\033[0;37m");
# define DARKGRAY  printf("\033[1;30m");
# define LIGHTRED  printf("\033[1;31m");
# define LIGHTGREEN  printf("\033[1;32m");
# define YELLOW  printf("\033[1;33m");
# define LIGHTBLUE  printf("\033[1;34m");
# define LIGHTPURPLE  printf("\033[1;35m");
# define LIGHTCYAN  printf("\033[1;36m");
# define WHITE  printf("\033[1;37m");

char *ft_emoji(int i)
{
	static char *emoji[50];

	emoji[0] = "😀";
	emoji[1] = "😃";
	emoji[2] = "😄";		
	emoji[3] = "😁";
	emoji[4] = "😆";	
	emoji[5] = "😅";
	emoji[6] = "🤣";	
	emoji[7] = "😂";	
	emoji[8] = "🙂";		
	emoji[9] = "🙃";
	emoji[10] = "😉";
	emoji[12] = "😊";
	emoji[13] = "😇";
	emoji[14] = "🥰";
	emoji[15] = "😍";
	emoji[16] = "🤩";		
	emoji[17] = "😘";
	emoji[18] = "😗";		
	emoji[19] = "😚";
	emoji[21] = "😙";	
	emoji[22] = "😋";	
	emoji[23] = "😛";		
	emoji[24] = "😜";
	emoji[25] = "🤪";	
	emoji[26] = "😝";
	emoji[27] = "🤑";
	emoji[28] = "🤗";
	emoji[29] = "🤭";		
	emoji[30] = "🤫";
	return(emoji[i]);
}

int main(int ac, char **av)
{
	char *test[250];
	char testascii[130];
	int i = 0;
	
	if(ac != 2)
	{
		puts("les arguments");
		return(0);
	}


	CYAN printf("\n\nTESTER"); NOCOLOR

	PURPLE printf("\ngeneral tests\n\n"); NOCOLOR
	test[0] = " hello ";
	test[1] = "";
	test[2] = " \n ";
	test[3] = " \t ";
	test[4] = " \U0001f602 ";
	test[5] = malloc(sizeof(char *) * 800);
	test[5] = " Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece\
	of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin \
	professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, \
	from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the \
	undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \
	(The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, \
	very popular during the Renaissance. The first line of Lorem Ipsum,, \
	comes from a line in section 1.10.32. ";
	test[6] = " -2147483648 ";
	test[7] = " 2147483647 ";
	i = 0;

	const char*binary_name = "./client";
	char output_array[5000];

	while (i <= 7)
	{
		sprintf(output_array, "%s", binary_name);
		strcat(output_array, " ");
		strcat(output_array, av[1]);
		strcat(output_array, " ");
    	strcat(output_array, test[i]);
		printf("|||%s|\n", output_array);
		system(output_array);
		ft_bzero(output_array, strlen(output_array));
		i++;
	}
	GREEN printf("\n\nASCII tests\n\n"); NOCOLOR
	i = 0;
	while (i <= 127)
	{
		testascii[i] = i;
		// printf("%c\n", testascii[i]);
		sprintf(output_array, "%s", binary_name);
		strcat(output_array, " ");
		strcat(output_array, av[1]);
		strcat(output_array, " ");
    	strcat(output_array, (char[2]){testascii[i], '\0'});
		printf("|||%s|\n", output_array);
		system(output_array);
		ft_bzero(output_array, strlen(output_array));
		i++;
	}
	testascii[128] = 0;
	YELLOW printf("\n\nUNICODE tests\n\n"); NOCOLOR
	i = 0;
	while (i < 30)
	{
		// printf("|||%s|\n", ft_emoji(i));
		sprintf(output_array, "%s", binary_name);
		strcat(output_array, " ");
		strcat(output_array, av[1]);
		strcat(output_array, " ");
		if (ft_emoji(i) != NULL)
	    	strcat(output_array, ft_emoji(i));
		printf("|||%s|\n", output_array);
		system(output_array);
		i++;
	}
	PURPLE printf("\nEND tests\n"); NOCOLOR
	return(0);
}

//gcc -Wall -Wextra -Werror libft/libft.a -fsanitize=address -g tester.c