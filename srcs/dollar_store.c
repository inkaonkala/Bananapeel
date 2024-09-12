/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_store.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:05:09 by jbremser          #+#    #+#             */
/*   Updated: 2024/09/11 18:32:00 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_node *find_key(char *key, t_node *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		else
			env = env->next;
	}
    // printf("find the key: %s\n", key);
    return (NULL);
}

static char *expand_var(char *str, t_node *env)
{
	t_node	*temp_node;
	char	*var_name;
	int 	i;
	int 	j;
	size_t		value_len;
	char	*temp_str;
	// char	*temp_str;
	
	printf("str1: %s\n", str);
	value_len = 0;
	i = 1;
	while (str[i] && (str[i] != ' ' && str[i] != '\0' && str[i] != '\'' && str[i] != '"' && str[i] != '.'))
        i++;
	printf("str2: %s\n", str);
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (str);	
	j = 1;
	while (j < i)
	{
		var_name[j - 1] = str[j];
		j++;
	}	
	var_name[j - 1] = '\0';
    temp_node = find_key(var_name, env);
	printf("str3: %s\n", str);
	if (temp_node && temp_node->value)
	{
		value_len = ft_strlen(temp_node->value);
		if (value_len <= ft_strlen(str))
		{
			ft_strlcpy(str, temp_node->value, value_len + 1);	// memmove changed to strlcpy which null terminates
			printf("str4: %s\n", str);
		}
		else
			{
				printf("str5: %s\n", str);
				temp_str = ft_strdup(temp_node->value);
				//  free(str);
				str = temp_str;
				printf("str6: %s\n", str);
			}
		// ft_memmove(str + value_len, str + i, ft_strlen(str + i)); // +1 for the null terminator
		printf("str7: %s\n", str);
		printf("\nafter memmove\n");
	}
	else
		printf("Variable not found or has no value: %s\n", var_name);
	free(var_name);
	return (str);
} 


	// {
	// 	temp_str = ft_strdup(temp_node->value);
	// 	free(str);
	// 	str = temp_str;	
	// }

// static char *expand_var(char *str, t_node *env)
// {
// 	t_node	*temp_node;
// 	char	*var_name;
// 	int 	i;
// 	int 	j;
// 	int		value_len;
//  	int		remaining_len;
// 	char 	*new_str;

// 	value_len = 0;
// 	i = 1;
// 	while (str[i] && (str[i] != ' ' && str[i] != '\0' && str[i] != '\'' && str[i] != '"' && str[i] != '.'))
//         i++;
// 	var_name = ft_calloc(i, sizeof(char));
// 	if (!var_name)
// 		return (str);	
// 	j = 1;
// 	while (j < i)
// 	{
// 		var_name[j - 1] = str[j];
// 		j++;
// 	}	
// 	var_name[j - 1] = '\0';
//     temp_node = find_key(var_name, env);
// 	if (temp_node && temp_node->value)
// 	{
// 		value_len = ft_strlen(temp_node->value);
// 		remaining_len = ft_strlen(str + i);
// 		new_str = ft_calloc(ft_strlen(str) + value_len + 1, sizeof(char));
//         if (!new_str)
//         {
//             free(var_name);
//             return str;
//         }

// 		ft_memmove(new_str, temp_node->value, value_len);
// 		ft_memmove(str + value_len, str + i, remaining_len + 1); // +1 for the null terminator
// 		free(str);
// 		str = new_str;
// 		printf("\nafter memmove\n");
// 	}
// 	else
// 	{
// 		// Allocate memory for the original string if no expansion occurred
// 		new_str = ft_strdup(str);
// 		if (!new_str)
// 		{
// 			printf("Variable not found or has no value: %s\n", var_name);
// 			free(var_name);
// 			return (str);
// 		}
// 		str = new_str;
// 	}
		
// 	free(var_name);
// 	return (str);
// } 
	// var_name[i - 1] = str[i];  // Copy the variable name excluding the '$'
	// Assuming expand_var is defined elsewhere
    // printf("\nend of expand did it work:\n str: %s\n var_name: %s\n key: %s\n value: %s \n\n", str, var_name, temp_node->key, temp_node->value);
	// {
	// 	env = find_key(var_name, env);
	// 	ft_memmove()
	// }


char	*dollar_check(char *str, t_node *env)
{
	int i = 0;
	int single_quote = 0;
	int double_quote = 0;
	char *dollar_ptr;

	// Find the first occurrence of '$' using ft_strchr
	if (!(dollar_ptr = ft_strchr(str, 36))) // 36 is ASCII for '$'
		return (str);

	int dollar_pos = dollar_ptr - str; // Calculate the index of '$'

	while (str[i]) // Loop through the string
	{
		// Toggle single quote flag, but only if not inside double quotes
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;

		// Toggle double quote flag
		else if (str[i] == '"')
			double_quote = !double_quote;
		
		// Check if we've reached the dollar sign ($)
		if (i == dollar_pos)
		{
			// Expand the variable if not in single quotes or if single quotes are within double quotes
			if (!single_quote || (single_quote && double_quote))
			{
				str = expand_var(dollar_ptr, env); // Call expand_var when expansion is allowed
				printf("after expansion str: %s\n", str);
				return (str);
			}
			else
			{
				// If within single quotes and no double quotes, do nothing
				printf("no expansion inside single quotes\n");
				return (str);
			}
		}
		i++;
	}
	return (str);
}


// void	dollar_check(char *str, t_node **env)
// {
// 	int i = 0;
// 	int single_quote = 0;
// 	int double_quote = 0;
// 	char *dollar_ptr;

// 	// Find the first occurrence of '$' using ft_strchr
// 	if (!(dollar_ptr = ft_strchr(str, 36))) // 36 is ASCII for '$'
// 		return ;

// 	int dollar_pos = dollar_ptr - str; // Calculate the index of '$'

// 	while (str[i]) // Loop through the string
// 	{
// 		if (str[i] == '\'') // Toggle single quote flag
//         {
//             temp = i;
//             single_quote = !single_quote;
//         }
// 		else if (str[i] == '"') // Toggle double quote flag
// 			double_quote = !double_quote;
		
// 		// Check if we've reached the dollar sign ($)
// 		if (i == dollar_pos)
// 		{
// 			// If inside double quotes
// 			if (!single_quote)
// 			{
//                 if (find_key)
// 				expand_var(str); // Call expand_var when inside single quotes
// 				return;
// 			}
// 			// If inside double quotes or no quotes
// 			else if (!single_quote || (double_quote && !single_quote))
// 			{
// 				printf("no quotes\n"); // Placeholder behavior
// 				return;
// 			}
// 		}
// 		i++;
// 	}
// }
