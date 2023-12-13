#include "shell.h"

/**
 * printsHelp - func can prints help of help built in
 *
 * Return: Nothing
 */
void printsHelp(void)
{
	_puts("Shell HSH, version is 1.0(1)-release (x86_64-pc-linux-gnu)\n");
	_puts("These shell commands has defined internally.\n");
	_puts("Type `help' to see this requested list.\n");
	_puts("Type help  'BUILTIN'' to find out more about it");
	_puts("function 'BUILTIN'.\n\n");
	_puts(" exit [n]\n");
	_puts(" env\n");
	_puts(" setenv [VARIABLE] [VALUE]\n");
	_puts(" unsetenv [VARIABLE]\n");
	_puts(" cd [DIRECTORY]\n");
	_puts(" help [BUILTIN ...]\n");
	_puts(" alias [name[='value'] ...]\n");
}
