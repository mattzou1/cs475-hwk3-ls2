#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"

const char tab[] = "    ";

//builds full path name from path and file name 
char * fullPathName(char* path, char* name) {
    int len = strlen(path) + strlen(name) + 2;
    char * fullName = (char*)malloc(len);
    memset(fullName, 0, len);
    strcat(fullName, path); 
    strcat(fullName, "/"); 
    strcat(fullName, name); 
    return fullName;
}

// TODO: function definitions here for ls2
void mode1(char path[], stack_t *s, int indent){
    DIR* folder = opendir(path); 
    struct stat info; 
    struct dirent* file = readdir(folder);
    //loops until it can't find a file
    while(file != NULL){
        //check for . and .. directories 
        if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0){
            char* fullname = fullPathName(path, file->d_name);
            lstat(fullname, &info);
            //check to see if file is regular 
            if(S_ISREG(info.st_mode) == 1){
                //turn byte size into a string
                char s1[10];
                sprintf(s1, "%ld", info.st_size);
                //format regular file string and push to stack 
                int len = strlen(tab) * indent + strlen(file->d_name) + strlen(" (") + 11 + strlen(" bytes)");
                char* s2 =  (char*)malloc(len);
                memset(s2, 0, len);
                for(int i = 0; i < indent; i++){
                    strcat(s2, tab); 
                }
                strcat(s2, file->d_name);
                strcat(s2, " (");
                strcat(s2, s1);
                strcat(s2," bytes)");
                strcat(s2, "\0");
                push(s, s2);

            }
            //check to see if file is directory 
            if(S_ISDIR(info.st_mode) == 1){
                char* s1 = fullPathName(path, file->d_name);
                //recurse 
                mode1(s1, s, indent + 1);

                //format directory string and push to stack
                int len = strlen(tab) * indent + strlen(file->d_name) + strlen("/ (directory)") + 1;
                char* s0 = (char*)malloc(len); 
                memset(s0, 0, len);
                for(int i = 0; i < indent; i++){
                    strcat(s0, tab); 
                }
                strcat(s0, file->d_name); 
                strcat(s0, "/ (directory)"); 
                strcat(s0, "\0");
                push(s, s0); 
                free(s1);
            }
            free(fullname);
        }
        file = readdir(folder);
    }
    
    closedir(folder);
    free(file);
}

int mode2(char path[], char targetFile[], stack_t *s, int indent){
    int found = 0;
    DIR* folder = opendir(path); 
    struct stat info; 
    struct dirent* file = readdir(folder);
    //loops until it can't find a file
    while(file != NULL){
        //check for . and .. directories 
        if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0){
            char* fullname = fullPathName(path, file->d_name);
            lstat(fullname, &info);
            //check to see if file is regular 
            if(S_ISREG(info.st_mode) == 1){
                //check to see if file is target file
                if(strcmp(file->d_name, targetFile) == 0){
                    //if file is found set found to true 
                    found = 1; 
                    //turn byte size into a string
                    char s1[10];
                    sprintf(s1, "%ld", info.st_size);
                    //format regular file string and push to stack 
                    int len = strlen(tab) * indent + strlen(file->d_name) + strlen(" (") + 11 + strlen(" bytes)");
                    char* s2 =  (char*)malloc(len);
                    memset(s2, 0, len);
                    for(int i = 0; i < indent; i++){
                        strcat(s2, tab); 
                    }
                    strcat(s2, file->d_name);
                    strcat(s2, " (");
                    strcat(s2, s1);
                    strcat(s2," bytes)");
                    strcat(s2, "\0");
                    push(s, s2);
                }
            }
            //check to see if file is directory 
            if(S_ISDIR(info.st_mode) == 1){
                char* s1 = fullPathName(path, file->d_name);
                //recurse 
                int ifFound = mode2(s1, targetFile, s, indent + 1);
                //check if targetfile is found in directory
                if(ifFound == 1){
                    //set found to true for parent directories 
                    found = 1; 
                    //format directory string and push to stack
                    int len = strlen(tab) * indent + strlen(file->d_name) + strlen("/ (directory)") + 1;
                    char* s0 = (char*)malloc(len); 
                    memset(s0, 0, len);
                    for(int i = 0; i < indent; i++){
                        strcat(s0, tab); 
                    }
                    strcat(s0, file->d_name); 
                    strcat(s0, "/ (directory)"); 
                    strcat(s0, "\0");
                    push(s, s0); 
                }
                free(s1);
            }
            free(fullname);
        }
        file = readdir(folder);
    }
    closedir(folder);
    free(file);
    return found; 
}