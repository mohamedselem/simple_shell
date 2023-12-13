#include <unistd.h>
#include "shell.h"

/**
 * signal_handler - handles fun ctrl + c in the runtime
 * @z: unused value for betty
 *
 * Return: Nothing
 */
void signal_handler(int z)
{
	(void) z;
	write(1, "\n$ ", 3);
}
/**
 * signal_handler2 - handles fun ctrl + c in cmd exec
 * @z: unused value for betty
 *
 * Return: Nothing
 */
void signal_handler2(int z)
{
	(void) z;
	write(1, "\n", 1);
}
