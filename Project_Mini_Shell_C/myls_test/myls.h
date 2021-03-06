#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define SORT_BY_MTIME (1<<0) /* -t */
#define REVERSE       (1<<1) /* -r */
#define ALL           (1<<2) /* -a */
#define RECURSIVE     (1<<3) /* -R */
#define DETAIL        (1<<4) /* -l */
#define MAX_FILE_COUNT   1024
#define MAX_FILENAME_LEN 200
#define MAX_PATH_LEN     500

struct FileList {
        char name[MAX_FILENAME_LEN]; /* nom de fichier ou nom du sous-répertoire */
        struct stat info;            /* informations de fichier                      */
} file_list[MAX_FILE_COUNT];


int  get_file_list(char dirname[], struct FileList *file_list, int mode);
void reverse_file_list(struct FileList *file_list, int count);

/* fonctions print */
void display(struct FileList *file_list, int count, int mode);
void display_file_simply(struct FileList *file_list, int count);
void display_file_detail(struct FileList *file_list, int count);
void display_file_recursively(struct FileList *file_list, int count, int mode);

/* fonctions compare utilisées par qsort () */
int  name_cmp(const void *a, const void *b);
void lower_case(const char *filename, char *new_name);
int  mtime_cmp(const void *a, const void *b);

/* fonctions help sur les informations de fichiers */
void file_mode_to_string(int mode, char str[]);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
