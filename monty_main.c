#include "monty.h"

int buf_number = 0;
char **argRead = NULL;
int queue_status = 0;
stack_t *stack = NULL;
FILE *file;

/**
 * main - Entry to main program
 * @argc: var to hold the count of arg entered
 * @argv: a pointer to pointer to hold arg entered
 * Return: 0 on success and -1 upon failure
 */

int main(int argc, char **argv)
{
	char buffer[120];
	int counter;
	instruction_t instr[] = {
		{"push", push}, {"pall", pall}, {"pint", pint}, {"pop", pop}, {"swap", swap},
		{"add", add}, {"sub", sub}, {"div", _div}, {"mul", mul}, {"pchar", pchar},
		{"mod", mod}, {"pstr", pstr}, {"rotl", rotl}, {"rotr", rotr}, {NULL, NULL}
	};

	if (argc == 0 || argc == 1 || argc > 2)
		fprintf(stderr, "USAGE: monty file %s\n", argv[1]), exit(EXIT_FAILURE);

	file = fopen(argv[1], "r");
	if (file == NULL)
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);
	while (fgets(buffer, sizeof(buffer), file))
	{
		buf_number++;
		argRead = tokenize_str(buffer);
		if ((argRead == NULL) || (argRead[0][0] == '#') ||
				(strcmp(argRead[0], "nop") == 0))
		{
			free(argRead);
			continue;
		}
		if (strcmp(argRead[0], "queue") == 0)
		{
			queue_status = 1;
			free(argRead);
			continue;
		}
		if (strcmp(args[0], "stack") == 0)
		{
			queue_status = 0;
			free(argRead);
			continue;
		}
		while (instr[counter].opcode != NULL)
		{
			if (strcmp(argRead[0], instr[counter].opcode) == 0)
			{
				instr[counter].f(&stack, buf_number);
				break;
			}
			if (instr[counter + 1].opcode == NULL)
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", buf_number, argRead[0]);
				free(argRead), fclose(file), free_stack(stack);
				return (EXIT_FAILURE);
			}
			counter++;
		}
		free(argRead);
	}
	fclose(file), free_stack(stack);
	return (EXIT_SUCCESS);
}

/**
 * tokenize_str - breaks strings into an an array
 * @buffer: collection of characters to be tokenized
 * Return:  a collection of string
 */

char **tokenize_str(char *buffer)
{
	char **strtokenized = malloc(sizeof(char *) * 3);

	if (strtokenized == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	strtokenized[0] = strtok(buffer, "\t\n");
	if (strtokenized[0] == NULL)
	{
		free(strtokenized);
		return (NULL);
	}
	strtokenized[1] = strtok(NULL, "\t\n");
	strtokenized[2] = NULL;
	return (strtokenized);
}

/**
 * is_digit - function confirms if a string has digits only
 * @valueEntered: variable of type string
 * Return: 1 if true or 0 if false
 */

int is_digit(char *valueEntered)
{
	int count = 0;

	while (valueEntered[count])
	{
		if ((count == 0) && (valueEntered[count] == '-') &&
				(valueEntered[count + 1]))
			continue;
		if (valueEntered[count] >= '0' && valueEntered[count] <= '9')
			continue;
		return (0);
	}
	return (1);
}
