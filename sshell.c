#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define S_RL_BUFF_SIZE 1024
#define S_TOK_BUFFSIZE 64
#define S_TOK_DELIM " \t\r\n\a"

#define S_ALLOC_ERR "sshell: allocation error\n"

int s_cd(char** args);
int s_help(char** args);
int s_exit(char** args);

char* builtint_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtint_func[])(char**) = {
    &s_cd,
    &s_help,
    &s_exit
};

int s_num_builtins(){
    return sizeof(builtint_str) / sizeof(char *);
}

int s_cd(char** args){
    if (args[1] == NULL){
        fprintf(stderr, "sshell: expected argument to \"cd\"\n");
    }else{
        if (chdir(args[1]) != 0){
            perror("sshell");
        }
    }
    return 1;
}

int s_help(char** args){
    printf("ssxshi's sshell\n");
    printf("Type program names, arguments, and hit enter!\n");
    printf("The following commands are built in:\n");

    for (int i = 0; i < s_num_builtins(); i++){
        printf("  %s\n", builtint_str[i]);
    }

    printf("Use the [man] command for information on other programs.\n");
    return 1;
}

int s_exit(char** args){
    return 0;
}

char* s_read_line(){
    int buff_size = S_RL_BUFF_SIZE;
    int pos = 0;

    char* buff = malloc(sizeof *buff * buff_size);
    int c;

    if (!buff){
        fprintf(stderr, S_ALLOC_ERR);
        exit(EXIT_FAILURE);
    }

    while (1){
        c = getchar();

        if (c == EOF || c == '\n'){
            buff[pos] = '\0';
            return buff;
        }

        buff[pos++] = c;

        if (pos >= buff_size){
            buff_size += S_RL_BUFF_SIZE;
            buff = realloc(buff, buff_size);
            if (!buff){
                fprintf(stderr, S_ALLOC_ERR);
                exit(EXIT_FAILURE);
            }
        }
    }
}

char** s_split_line(char* line){
    int buff_size = S_TOK_BUFFSIZE;
    char** tokens = malloc(sizeof line * buff_size);
    char* token;
    int pos = 0;

    if (!tokens){
        fprintf(stderr, S_ALLOC_ERR);
        exit(EXIT_FAILURE);
    }

    token = strtok(line, S_TOK_DELIM);
    while (token != NULL){
        tokens[pos++] = token;

        if (pos >= buff_size){
            buff_size += S_TOK_BUFFSIZE;
            tokens = realloc(tokens, sizeof token * buff_size);
            if (!tokens){
                fprintf(stderr, S_ALLOC_ERR);
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, S_TOK_DELIM);
    }

    tokens[pos] = NULL;
    return tokens;
}

int s_launch(char** args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0){
        if (execvp(args[0], args) == -1){
            perror("sshell");
        }
        exit(EXIT_FAILURE);
    }else if (pid < 0){
        perror("sshell");
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int s_execute(char** args){
    if (args[0] == NULL) return 1;

    for (int i = 0; i < s_num_builtins(); i++){
        if (strcmp(args[0], builtint_str[i]) != 0) continue;
        return (*builtint_func[i])(args);
    }

    return s_launch(args);
}

void s_loop(){
    char* line;
    char** args;
    int status;

    do{
        printf("s@s: ");
        line = s_read_line();
        args = s_split_line(line);
        status = s_execute(args);

        free(line);
        free(args);
    }while(status);
}

int main(int argc, char** argv){

    s_loop();
    
    return EXIT_SUCCESS;
}
