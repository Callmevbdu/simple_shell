#include "shell.h"

/**
 * addNode - function that adds a new node at the beginning of a linked list
 * @h: pointer to the list_t list
 * @s: new string
 * @n: index given to history
 * Return: the linked list size
 */

list_t *addNode(list_t **h, const char *s, int n)
{
	list_t *new;

	if (!h)
		return (NULL);

	new = malloc(sizeof(list_t));

	if (!new)
		return (NULL);

	_memSet((void *)new, 0, sizeof(list_t));
	new->number = n;
	if (s)
	{
		new->strings = _strdup(s);
		if (!new->strings)
		{
			free(new);
			return (NULL);
		}
	}

	new->complete = *h;
	*h = new;
	return (new);
}

/**
 * addNodeEnd - adds a new node at the end of a linked list
 * @head: double pointer to the list_t list
 * @str: string to put in the new node
 * @n: node index
 * Return: linked list size
 */

list_t *addNodeEnd(list_t **head, const char *str, int n)
{
	list_t *current;
	list_t *new;

	if (!head)
		return (NULL);

	current = *head;

	new = malloc(sizeof(list_t));

	if (!new)
		return (NULL);

	_memSet((void *)new, 0, sizeof(list_t));

	new->number = n;

	if (str)
	{
		new->strings = _strdup(str);
		if (!new->strings)
		{
			free(new);
			return (NULL);
		}
	}

	if (current)
	{
		while (current->complete)
			current = current->complete;
		current->complete = new;
	}
	else
		*head = new;

	return (new);
}

/**
 * removeNode - function that deletes a node in a list at a certain index
 * @h: pointer to the first element in the list
 * @idx: index of the node to delete
 * Return: 1 (Success), or 0 (Fail)
 */

int removeNode(list_t **h, unsigned int idx)
{
	list_t *current;
	list_t *temp;
	unsigned int itr = 0;

	if (!h || !*h)
		return (0);

	if (!idx)
	{
		current = *h;
		*h = (*h)->complete;
		free(current->strings);
		free(current);
		return (1);
	}

	current = *h;

	while (current)
	{
		if (itr == idx)
		{
			temp->complete = current->complete;
			free(current->strings);
			free(current);
			return (1);
		}

		itr++;
		temp = current;
		current = current->complete;
	}

	return (0);
}

/**
 * listPrefix - function that prints the prefix the string starts with
 * @current: pointer to node
 * @pre: prefix to find
 * @ch: character to search
 * Return: the matching node
 */

list_t *listPrefix(list_t *current, char *pre, char ch)
{
	char *ptr = NULL;

	while (current)
	{
		ptr = strstr(current->strings, pre);

		if (ptr && ((ch == -1) || (*ptr == ch)))
		{
			return (current);
		}

		current = current->complete;
	}

	return (NULL);
}

/**
 * listPrint - function that prints all elements of linked list
 * @h: pointer
 * Return: size of the list
 */

size_t listPrint(const list_t *h)
{
	size_t itr = 0;

	while (h)
	{
		_puts(convertNum(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->strings ? h->strings : "(nil)");
		_puts("\n");

		h = h->complete;
		itr++;
	}

	return (itr);
}