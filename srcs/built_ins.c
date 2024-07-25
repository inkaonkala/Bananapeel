#include "../minishell.h"

static void handle_exit(char *str)
{
	size_t  len;

	len = ft_strlen(str);
	if (len > 0 && str[len -1] == '\n')
		str[len - 1] = '\0';
	if (ft_strncmp(str, "exit", len) == 0)
	{
		ft_printf("Bye bye BaNaNaNaS!\n");
		exit (1);
	}
}

void built_ins(char *str)
{
    handle_exit(str);

	//check if input is 
	/*
		echo
		pwd
		cd
		env
		export
		unset
	*/
}
