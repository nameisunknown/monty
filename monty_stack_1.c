#include "monty.h"

/**
 * push - Appends new element at the top of the stack
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *top;
	stack_t *temp;

	if (argRead[1] == NULL || !is_digit(argRead[1]))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	top = malloc(sizeof(stack_t));
	if (top == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		fclose(file), free(argRead), free_stack(*stack), exit(EXIT_FAILURE);
	}
	top->n = atoi(argRead[1]);

	if (*stack == NULL)
	{
		top->next = NULL;
		top->prev = NULL;
		*stack = top;
		return;
	}
	temp = *stack;
	if (queue_status)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = top;
		top->prev = temp;
		top->next = NULL;
	}
	else
	{
		top->next = *stack;
		top->prev = NULL;
		*stack = top;
		temp->prev = *stack;
	}
}

/**
 * pall - Prints all the elements of the stack starting from the top
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	(void) (line_number);
	if (*stack == NULL)
		return;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * pint - Prints the value at the top of the stack
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free(argRead), fclose(file);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - Removes the top element of the stack.
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		free(argRead), fclose(file);
		exit(EXIT_FAILURE);
	}
	*stack = (*stack)->next;
	free(temp);
	if (*stack)
		(*stack)->prev = NULL;
}

/**
 * free_stack - frees a stack
 * @stack: Is the stack to free
 * Return: void
*/
void free_stack(stack_t *stack)
{
	stack_t *tmp;

	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}
