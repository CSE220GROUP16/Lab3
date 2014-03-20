//
//  main.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "testCode.h"
#include "common.h"
#include "scanner.h"
#include "print.h"



FILE *init_lister(const char *name, char source_file_name[], char dte[]);
void quit_scanner(FILE *src_file, Token *list);
void add_token_to_list(Token *list, Token *new_token);

int main(int argc, const char * argv[])
{


    char source_name[MAX_FILE_NAME_LENGTH];
    char date[DATE_STRING_LENGTH];
    FILE *source_file;


    Token *head_t;
    Token *token_t;
    Token *temp_t;
    Token *temp_td;
    Token *token_td;

    ttr_start = 0;

    Token *token_list; //This needs to be implemented as a linked list in scanner.h.
  BOOLEAN continueReadingFile;// = TRUE;  // set var to true
    if (argc < 2)
        {
            test001();
        }

    source_file = init_lister(argv[1], source_name, date);


    if (source_file != NULL)
    {
        init_scanner(source_file, source_name, date);

         // root of link list with nodes of token
        head_t = malloc( sizeof(Token) );
        head_t->val = 0;
        token_t = head_t;
        temp_t = head_t;
       // token_list_t = head_t;


        continueReadingFile = get_source_line();
    int val =0;

        // loop thru the text file line by line until eof
        while ( continueReadingFile == TRUE){

            int a = 4;
            val = val + 1;


            temp_t = get_token();
            while (temp_t != NULL)
                {

                //add_token_to_list(token_list, token);
                token_t->next = temp_t; // create the link
                temp_t->next = NULL;
                temp_t->val = val;
                token_t = temp_t;


                 temp_t = get_token();
                }

            continueReadingFile = get_source_line();

        } // end reading file


// print then delete  link list with tokens
        token_td = head_t->next;

        printf("\n\n\t\t Deleting linked list with tokens\n\n");
        while(token_td)
        {
            printf(" \n%d \t %s", token_td->val, token_td->myUsage_str);
            temp_td = token_td->next;
            free(token_td);
            token_td = temp_td;
        }
        // delete head of linked list
        free(head_t);

  printf("\n\n\t\t Look at top for output from scanner\n");
 printf("\t the immediate above printout is just to delete the linked list and its tokens\n\n");

    quit_scanner(source_file, token_list);
    }
    else
    {
       test002(source_name);
    }
    return 0;
}
void add_token_to_list(Token *list, Token *new_token)
{
    // Add new_token to the list knowing that list is a linked list.
}
void quit_scanner(FILE *src_file, Token *list)
{
    //write code to free all of the memory for the token list
    // already done in
    fclose(src_file);
}
FILE *init_lister(const char *name, char source_file_name[], char dte[])
{
    time_t timer;
    FILE *file;

    strcpy(source_file_name, name);
    file = fopen(source_file_name, "r");
    time(&timer);
    strcpy(dte, asctime(localtime(&timer)));

    return file;
}

