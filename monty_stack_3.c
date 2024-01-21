#include "monty.h"

/**
 * mod - Computes the rest of the division of the second top element by
 * the top element
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int size = 0;

	(void) (line_number);

	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	if (size < 2)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->n %= temp->n;
	free(temp);
	if (*stack)
		(*stack)->prev = NULL;
}

/**
 * pchar - pchar prints the char at the top of the stack,
 * followed by a new line.
 * @stack: is a double pointer pointing to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void pchar(stack_t **stack, unsigned int line_number)
{
	(void) (line_number);
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		free(argRead), fclose(file);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", (*stack)->n);
}

/**
 * pstr - This pstr prints the string starting at the top of the stack,
 * followed by a new line.
 *
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void) (line_number);
	while (temp != NULL)
	{
		if (temp->n < 0 || temp->n > 127 || temp->n == 0)
			break;
		printf("%c", temp->n);
		temp = temp->next;
	}
	printf("\n");
}

/**
 * rotl - This rotates the stack to the top
 * which means that top element becomes
 * the last one and the second top element of the stack becomes the first one
 *
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *first = *stack;
	stack_t *temp = *stack;

	(void) (line_number);

	if (*stack == NULL)
		return;
	if (*stack && (*stack)->next == NULL)
		return;

	while (temp->next != NULL)
		temp = temp->next;

	first = (*stack)->next;
	first->prev = NULL;

	temp->next = *stack;
	(*stack)->next = NULL;
	(*stack)->prev = temp;

	*stack = first;
}

/**
 * rotr - This rotates the stack to the bottomi
 * which means that last element becomes
 * the top element of the stack
 *
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *last;
	stack_t *temp = *stack;

	(void) (line_number);

	if (*stack == NULL)
		return;
	if (*stack && (*stack)->next == NULL)
		return;

	while (temp->next->next != NULL)
		temp = temp->next;

	last = temp->next;
	temp->next = NULL;

	last->next = *stack;
	last->prev = NULL;
	(*stack)->prev = last;
	*stack = last;
}
