#include "monty.h"
/**
 * swap - Swaps the top two elements of the stack.
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int size = 0;

	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	if (size < 2)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->next = (*stack)->next->next;
	(*stack)->prev = temp;
	temp->next = *stack;
	temp->prev = NULL;
	*stack = temp;
}

/**
 * add - Adds the top two elements of the stack.
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int size = 0;

	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	if (size < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->n += temp->n;
	free(temp);
	if (*stack)
		(*stack)->prev = NULL;
}

/**
 * sub - Subtracts the top element of the stack
 * from the second top element of the stack.
 *
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int size = 0;

	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	if (size < 2)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->n -= temp->n;
	free(temp);
	if (*stack)
		(*stack)->prev = NULL;
}

/**
 * _div - Divides the second top element by the top element of the stack.
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void _div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int size = 0;

	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	if (size < 2)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
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
	(*stack)->n /= temp->n;
	free(temp);
	if (*stack)
		(*stack)->prev = NULL;
}

/**
 * mul - Multiplies the second top element with the top element of the stack.
 * @stack: Is a pointer to the pointer to the stack
 * @line_number: Is the current line number of the opcode
 * Return: void
*/

void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	int size = 0;

	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	if (size < 2)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		free(argRead), fclose(file), free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->n *= temp->n;
	free(temp);
	if (*stack)
		(*stack)->prev = NULL;
}
