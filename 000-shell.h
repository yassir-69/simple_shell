#ifndef SHELLSIMPLE_H
#define SHELLSIMPLE_H

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* connecting commands in sequence */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* input/output buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* If employing the system's getline() function */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* Transform_numeric() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

extern char **environ;

/*_______________________________________________________________________*/

/**
 * struct liststr - A linked list with nodes connected in
 * a single direction.
 * @number: numeric field
 * @string: character string
 * @the_next_nood: reference to the next node
 */

typedef struct liststr
{
	int number;
	char *string;
	struct liststr *the_next_nood;
} list_t;

/*_______________________________________________________________________*/

/**
 * struct passinfo - Holds pseudo-arguments for passing into a function,
 * ensuring a consistent prototype for a function pointer structure.
 * @environ: A specially altered version of the environment from the linked
 * list labeled as "env".
 * @arg: A string produced from getline that includes arguments.
 * @argc: The count of arguments.
 * @line_count: The count of errors.
 * @err_num: The code indicating errors for exit() operations.
 * @linecount_flag: Determine whether to tally this line of input.
 * @fname: The name of the program file.
 * @status: The status returned by the most recently executed command.
 * @cmd_buf: The location of the pointer to `cmd_buf`, active in the case of
 * command chaining.
 * @env: Local copy of the environment stored in a linked list.
 * @history: The node containing historical data.
 * @alias: The node associated with aliases.
 * @env_changed: The condition indicating whether the environment has been
 * altered.
 * @cmd_buf_type: CMD_type representing logical operators: OR (||), AND (&&),
 * and semicolon (;).
 * @readfd: The file descriptor used for reading line input.
 * @histcount: The count of line numbers in the history.
 * @argv: A collection of strings created from the argument.
 * @path: A textual pathway for the present command.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to the buffer for command chaining with semicolons,
	used for memory management. */
	int cmd_buf_type; /* CMD_type representing logical operators: OR (||), AND (&&),
	and semicolon (;) */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/*_______________________________________________________________________*/

/**
 *struct builtin - contains a builtin string and related function
 *@is_type: the builtin command flag
 *@function: the function
 */
typedef struct builtin
{
	char *is_type;
	int (*function)(info_t *);
} builtin_table;

/*_______________________________________________________________________*/

/* toem_017-is_shell_loop.c */
int hsh(info_t *, char **);
int locate_builtin(info_t *);
void locate_command(info_t *);
void fork_command(info_t *);

/* toem_015-shell_command_path_resolution.c */
int cmd_check(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *locate_route(info_t *, char *, char *);

/* 014-pointer_memory_deallocation_function.c */
int loophsh(char **);

/* toem_005-file_descriptor_output_functions_for_error_handling.c */
void writes_a_string_to_the_standard_error(char *);
int writes_a_character_to_the_standard_error(char);
int writes_to_a_file_descriptor(char c, int fd);
int writes_a_string_to_a_file_descriptor(char *string, int fd);

/* toem_018-string_manipulation_and_comparison_functions_in_c.c */
int string_llen(char *);
int string_ccmp(char *, char *);
char *begins_with(const char *, const char *);
char *string_ccat(char *, char *);

/* toem_019-string_manipulation_and_output_functions_in_c.c */
char *the_string_copies(char *, char *);
char *the_string_duplicates(const char *);
void the_string_prints_input(char *);
int the_character_prints_input(char);

/* toem_007-string_manipulation_functions.c */
char *string_copies(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_charac(char *, char);

/* toem_020-string_tokenization_functions_in_c.c */
char **string_into_words(char *, char *);
char **splits_string_into_words(char *, char);

/* toem_016-memory_manipulation_and_management_functions.c */
char *underscore_memset(char *, char, unsigned int);
void f_free_string(char **);
void *underscore_realloc(void *, unsigned int, unsigned int);

/* toem_014-pointer_memory_deallocation_function.c */
int releasing_resources(void **);

/* toem_001-ShellCoreFunctions.c */
int in_a_user_interactive_mode(info_t *);
int is_a_delimiter(char, char *);
int alphabetic_char(int);
int integer_string(char *);

/* toem_006-error_handling_and_conversion_functions.c */
int handling_errors(char *);
void displays_an_error(info_t *, char *);
int print_decimal(int, int);
char *converts_a_number(long int, int, int);
void eliminates_comments(char *);

/* toem_002-Shell_Command_Implementation.c */
int exit_shell(info_t *);
int cd_shell(info_t *);
int the_help(info_t *);

/* toem_003-Shell_History_and_Alias_Management_Functions.c */
int display_history(info_t *);
int the_alias(info_t *);

/*toem_010-management_functions_for_info_t_structure_in_shell_program */
ssize_t receive_input(info_t *);
int is_get_line(info_t *, char **, size_t *);
void signal_interrupt_handler(int);

/* toem_009-sequential_command_buffering_and_input_handling_in_a_shell_program.c */
void reset_fields_of_information_structure(info_t *);
void set_fields_of_information_structure(info_t *, char **);
void Free_memory_used_information_structure(info_t *, int);

/* toem_004-shell_environment_variable_functions.c */
char *the_get_environ(info_t *, const char *);
int the_environ(info_t *);
int the_set_environ(info_t *);
int unset_environ(info_t *);
int list_populate_environ(info_t *);

/* toem_008-environment_variable_management_functions_in_shell_program.c */
char **retrieve_environment(info_t *);
int unset_an_environment_variable(info_t *, char *);
int set_an_environment_variable(info_t *, char *, char *);

/* toem_011-history_file_management_functions_for_a_shell_program.c */
char *the_history_file(info_t *info);
int write_the_history_file(info_t *info);
int read_command_history_from_file(info_t *info);
int create_list_from_command_history(info_t *info, char *buffer, int linecount);
int update_line_numbers_command_history(info_t *info);

/* toem_012-ngly-linked_list_management.c */
list_t *inserts_new_node(list_t **, const char *, int);
list_t *appends_a_new_node_at_end(list_t **, const char *, int);
size_t prints_list_strings(const list_t *);
int deletes_node_at_specified_index(list_t **, unsigned int);
void frees_memory_allocated_for_linked_list(list_t **);

/* toem_013-linked_list_utilities_for_shell_implementation.c */
size_t length_of_the_list(const list_t *);
char **convert_list_to_strings(list_t *);
size_t display_list(const list_t *);
list_t *starts_with_node(list_t *, char *, char);
ssize_t retrieve_node_index(list_t *, list_t *);

/* toem_021-string_manipulation_and_command_parsing_functions.c */
int chain_delimeter(info_t *, char *, size_t *);
void check_chain_delimeter(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_vars(info_t *);
int substitute_string(char **, char *);

#endif

