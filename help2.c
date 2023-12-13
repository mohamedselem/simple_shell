#include <unistd.h>
#include "shell.h"

/**
 * help_unsetenv - function to prints help of unsetenv built in
 *
 * Return: Nothing
 */
void help_unsetenv(void)
{
	_puts("unsetenv: unsetenv [VARIABLE]\n");
	_puts("    start a new environment variable, or ");
	_puts("    modifies already existing one.\n\n");
	_puts("    VARIABLE mustn't have the character '='.\n");
	_puts("    If no arguments given, setenv will prints the current ");
	_puts("    environment.\n");
}

/**
 * help_cd - func can prints help of cd built in
 *
 * Return: Nothing
 */
void help_cd(void)
{
	_puts("cd: cd open [DIRECTORY]\n");
	_puts("    Change the working directory.\n\n");
	_puts("    Changes current directory to DIR.  ");
	_puts("    The default DIRECTORY is the value of the\n");
	_puts("    HOME shell variable.\n\n");
	_puts("    Options:\n");
	_puts("    -  If a minus signed is used instead a dir, ");
	_puts("    cd changes to the\n");
	_puts("    previous used DIR\n\n");
	_puts("    Each time cd will runs success, the env variable ");
	_puts("    PWD updated\n\n");
	_puts("    Exit Status:\n");
	_puts("    Returns 1 if the DIR is changed, and if $PWD is set ");
	_puts("    successfully when\n");
	_puts("    is used; -1 otherwise.\n");
}
/**
 * help_help - func can prints help of help built in
 *
 * Return: Nothing
 */
void help_help(void)
{
	_puts("help: help [BUILTIN ...]\n");
	_puts("    Display info about builtins commands.\n\n");
	_puts("    Displays brief summary of builtin commands.  If BUILTIN is\n");
	_puts("    specified, gives detailed on all commands ");
	_puts("    match BUILTIN,\n");
	_puts("    otherwise list of help topic is printed.\n\n");
	_puts("    Arguments:\n");
	_puts("      BUILTIN   Builtin specifying a help topic\n\n");
	_puts("    Exit Status:\n");
	_puts("    Returns success unless PATTERN isn't found ");
	_puts("    options is given.\n");
}
/**
 * help_alias - func do prints help of alias
 *
 * Return: Nothing
 */
void help_alias(void)
{
	_puts("alias: alias [name[='value'] ...]\n");
	_puts("    Define aliases.\n\n");
	_puts("    Without arguments, `alias' print the list ");
	_puts("    in the Reusable\n");
	_puts("    form `alias NAME=VALUE' on output.\n\n");
	_puts("     Otherwise, alias is defined for each NAME ");
	_puts("    VALUE has been given.\n");
	_puts("    A trailing space VALUE causes the next word to ");
	_puts("    be checked \n");
	_puts("    alias substitutions when alias is expanded.\n\n");
	_puts("    Exit Status:\n");
	_puts("    alias return true unless a NAME is supplied for which ");
	_puts("    no alias has been given\n");
	_puts("    defined.\n");
}
