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
    int aaa = 9;
    Token *head;
    Token *token;
    Token *temp;
    Token *temp_d;
    Token *token_d;

    Token *head_t;
    Token *token_t;
    Token *temp_t;
    Token *temp_td;
    Token *token_td;

    ttr_start = 0;
    //theCh = assigned firest in scanner.c

    //Token *tail;
    Token *token_list; //This needs to be implemented as a linked list in scanner.h.
  BOOLEAN continueReadingFile;// = TRUE;  // set var to true
    if (argc < 2)
        {
        printf(" missing input file, should be ./lab3 pascalFile.pas\n you need to enter the PASCAL source file\n exited program");
        exit(1);
        }

    source_file = init_lister(argv[1], source_name, date);

    //MAX_LINES_PER_PAGEw
    if (source_file != NULL)
    {
       // printf("test 4 ");
        init_scanner(source_file, source_name, date);


        // root of link list with line form source code
        head = malloc( sizeof(Token) );
        head->val = 0;
        token = head;
        temp = head;
        token_list = head;

         // root of link list with nodes of token
        head_t = malloc( sizeof(Token) );
        head_t->val = 0;
        token_t = head_t;
        temp_t = head_t;
       // token_list_t = head_t;


        continueReadingFile = get_source_line();

        //continueReadingFile = get_source_line(source_buffer);
        // loop thru the text file line by line until eof
        while ( continueReadingFile == TRUE){
                temp = malloc( sizeof(Token) );
                token->next = temp; // create the link
                temp->next = NULL;
                temp->val = token->val + 1; // assign token number

        // loop breaks if raches eof with false return



            sprintf(temp->myUsage_str, "%s", source_buffer);
            token = temp;
            int a = 4;


           // printf("\thello6 %d\n\t", ttr_start);
            temp_t = get_token();
            while (temp_t != NULL)
                {

                //add_token_to_list(token_list, token);
                token_t->next = temp_t; // create the link
                temp_t->next = NULL;
                temp_t->val = temp->val;//token_t->val + 1; // assign token number
                token_t = temp_t;

              //  free(token_t);
                 temp_t = get_token();
                }
              //printf("\n\thello8 %d\n", ttr_start);
           // while (--a > 0);//What is the sentinal value that ends this loop?

            // get another line from source file
            continueReadingFile = get_source_line();

        } // end reading file

        // print then delete  link list with line numbers
        token_d = head->next;

       // printf("\n\n\t\t Printing linklist of tokens\n\n")
        while(token_d)
        {
           // printf(" %d %s", token_d->val, token_d->myUsage_str);
            temp_d = token_d->next;
            free(token_d);
            token_d = temp_d;
        }
        // delete head of linked list
        free(head);

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
        printf("could not open file:%s ; exited program",source_name);
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

