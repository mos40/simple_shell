#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly connected list code by Mkhonza
 * @num: the number field code by Mkhonza
 * @str: a string code by Mkhonza
 * @next: to the incoming node code by Mkhonza
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains arguements to pass into a function, code by Mkhon
 *		allowing uniform for function ptr struct code by Mkhonza
 *@arg: cstring made from getline holding arguements code by Mkhonza
 *@argv: an array of cstrings made from arg code by Mkhonza
 *@path: a cstring path for the active command code by Mkhonza
 *@argc: the argument count code by Mkhonza
 *@line_count: the error count code by Mkhonza
 *@err_num: the error code for exit code by Mkhonza
 *@linecount_flag: line of input code by Mkhonza
 *@fname: the program filename code by Mkhonza
 *@env: connected list primary cpy of environ code by Mkhonza
 *@environ: custom amended cpy of environ from LL env code by Mkhonza
 *@history: the history node code by Mkhonza
 *@alias: the alias node code by Mkhonza
 *@env_changed: on if environ was changed code by Mkhonza
 *@status: the bring status of the last command code by Mkhonza
 *@cmd_buf: address to cmd_buffe, chaining code by Mkhonza
 *@cmd_buf_type: CMD_type code by Mkhonza
 *@readfd: the line input code by Mkhonza
 *@histcount: the history line number count code by Mkhonza
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

	char **cmd_buf; /* ptr to cmd ; chain buf, code by Mkhonza */
	int cmd_buf_type; /* CMD_type ||, &&, ;code by Mkhonza */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL,/* Start of initialization block*/ \
NULL, NULL, NULL, 0, 0, NULL, /* Macro to initialize*/ \
0, 0, 0 /* End of initialization block */}
/**
 *struct builtin -  builtin cstring and attached function code by Mkhonza
 *@type: the builtin command flag code by Mkhonza
 *@func: the function code by Mkhonza
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_loopconstruct.c */
int hsh_structure(info_t *, char **);
int detect_built_in(info_t *);
void detect_cmd(info_t *);
void fork_child_cmd(info_t *);

/* toem_compiler.c */
int verify_is_cmd(info_t *, char *);
char *doubles_chars(char *, int, int);
char *detect_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_fails.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_character_array.c */
int str_size(char *);
int _str_Cmp(char *, char *);
char *begins_with(const char *, const char *);
char *_str_Cat(char *, char *);

/* toem_character_array1.c */
char *string_copy(char *, char *);
char *string_replicate(const char *);
void print_string(char *);
int write_putchar(char);

/* toem_leaves_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strt(char *, char *);
char **strt2(char *, char);

/* toem_redistribution.c */
char *distribution(char *, char, unsigned int);
void filefree(char **);
void *re_allocate(void *, unsigned int, unsigned int);

/* toem_memorization.c */
int bfree(void **);

/* toem_pont_atoi.c */
int isInteractive(info_t *);
int is_Delim(char, char *);
int _isAlpha(int);
int custom_atoi(char *);

/* toem_fails1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *format_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_setline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_setinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_setting.c */
char *_getEnviron(info_t *, const char *);
int _myEnviron(info_t *);
int _mysetEnviron(info_t *);
int _myunsetEnviron(info_t *);
int populate_Enviro_list(info_t *);

/* toem_setenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_record.c */
char *get_hist_file(info_t *info);
int note_history(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int new_number_hist(info_t *info);

/* toem_checklists.c */
list_t *insert2node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_checklists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_identifier.c */
int is_info_chain(info_t *, char *, size_t *);
void test_chain(info_t *, char *, size_t *, size_t, size_t);
int restore_alias(info_t *);
int restore_vars(info_t *);
int restore_string(char **, char *);

#endif
