//
//  scanner.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//
#include <ctype.h>
#include <stdio.h>
#include "common.h"
#include "scanner.h"
//#include "print.h"

#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
/*******************
 Static functions needed for the scanner
 You need to design the proper parameter list and
 return types for functions with ???.
 ******************/

static char get_char();
static void skip_comment();
static void skip_blanks();
static bool get_word();
static bool get_special();
static bool get_number();
static bool get_string();
int aaaw = 9;
/*
static ??? downshift_word(???);*/
static BOOLEAN is_reserved_word(char myWord1[] );


typedef enum
{
    LETTER, DIGIT, QUOTE, SPECIAL, EOF_CODE,
}
CharCode;

/*********************
 Static Variables for Scanner
 Must be initialized in the init_scanner function.
 *********************/
static FILE *src_file;
static char src_name[MAX_FILE_NAME_LENGTH];
static char todays_date[DATE_STRING_LENGTH];
static CharCode char_table[256];  // The character table

typedef struct
{
    char *string;
    TokenCode token_code;
}
RwStruct;

const RwStruct rw_table[9][10] = {
    {{"do",DO},{"if",IF},{"in",IN},{"of",OF},{"or",OR},{"to",TO},{NULL,0}}, //Reserved words of size 2
    {{"and",AND},{"div",DIV},{"end",END},{"for",FOR},{"mod",MOD},{"nil",NIL},{"not",NOT},{"set",SET},{"var",VAR},{NULL,0}}, //Reserved words of size 3
    {{"case",CASE},{"else",ELSE},{"file",FFILE},{"goto",GOTO},{"then",THEN},{"type",TYPE},{"with",WITH},{NULL,0}}, //Reserved words of size 4
    {{"array",ARRAY},{"begin",BEGIN},{"const",CONST},{"label",LABEL},{"until",UNTIL},{"while",WHILE},{NULL,0}},  //Reserved words of size 5
    {{"downto",DOWNTO}, {"packed",PACKED},{"record",RECORD}, {"repeat",REPEAT},{NULL,0}},  // Reserved words of size 6
    {{"program", PROGRAM},{NULL,0}}, // Reserved words of size 7
    {{"function", FUNCTION},{NULL,0}}, // Reserved words of size 8
    {{"procedure", PROCEDURE},{NULL,0}}  // Reserved words of size 9
};

void init_scanner(FILE *source_file, char source_name[], char date[])
{
    src_file = source_file;
    strcpy(src_name, source_name);
    strcpy(todays_date, date);

    /*******************
     initialize character table, this table is useful for identifying what type of character
     we are looking at by setting our array up to be a copy the ascii table.  Since C thinks of
     a char as like an int you can use ch in get_token as an index into the table.
     *******************/

}
BOOLEAN get_source_line()
{
    char print_buffer[MAX_SOURCE_LINE_LENGTH + 9];
//    char source_buffer[MAX_SOURCE_LINE_LENGTH];  //I've moved this to a function parameter.  Why did I do that?
    static int line_number = 0;

    if (fgets(source_buffer, MAX_SOURCE_LINE_LENGTH, src_file) != NULL)
    {
        ++line_number;
        sprintf(print_buffer, "%4d: %s", line_number, source_buffer);
        print_line(print_buffer, src_name, todays_date);


        return (TRUE);
    }
    else
    {

        return (FALSE);
    }


    //return (FALSE);
}


Token* get_token()
{    int arrLen = strlen(source_buffer);
      Token * get_temp;
      get_temp = malloc( sizeof(Token) );
      get_temp->val = ttr_start;


    char ch; //This can be the current character you are examining during scanning.
    char token_string[MAX_TOKEN_STRING_LENGTH]; //Store your token here as you build it.
    char *token_ptr;// = ???; //write some code to point this to the beginning of token_string

    ch = source_buffer[ ttr_start];
    int i =0;


    ch = get_char();
    if ((ch == ' ') || (ch == '\t'))
        {
            skip_blanks();
            ch = source_buffer[ttr_start];
         }

 if (ch == '{')
        {
             skip_comment();
         ch = source_buffer[++ttr_start];

         }




    //2.  figure out which case you are dealing with LETTER, DIGIT, QUOTE, EOF, or special, by examining ch
    //3.  Call the appropriate function to deal with the cases in 2.


    if ( (ch == '\r') ||(ch == '\n') || (ch == '\f')) // newline or line feed
        {
          free(get_temp);
          ttr_start =0;
          return NULL;
        }
    else if (ch == EOF)
        {//get_string();
         printf("-EOF-");
          free(get_temp);
          return NULL;
        }
    else if ( ( (ch <= 'z')&&(ch>='a') ) || ( (ch <= 'Z')&& (ch >='A')))
        {
            if ( get_word())
            { printf("\t>> %s \t\t%s\n", theWordUpper, theWord );
                sprintf(get_temp->myUsage_str,"%s",theWordUpper);
            }
            else
            {
             printf("\t>> <IDENTIFIER> \t%s \n", theWord);
            sprintf(get_temp->myUsage_str,"%s",theWord);

            }
     return get_temp;
        }
    else if ((ch <= '9') && (ch >='0'))
        {
            if( get_number())
                { printf("\t>> <NUMBER> \t%s \n", theWordUpper);
                    sprintf(get_temp->myUsage_str,"%s",theWordUpper);
                    return get_temp;
                }
            else
            {
             free(get_temp);
              return NULL;
            }


        }
    else if (ch == '\'')
        {
            if (get_string())
            {
            printf("\t>> <STRING> \t\t%s \n",  theWordUpper );
           // print("\nhere1");
            sprintf(get_temp->myUsage_str,"%s",theWord);
          //  print("\nhere2");
            return get_temp;
            }
            else
            {
           printf("\t>> <STRING> \t\t'' \n" );
            sprintf(get_temp->myUsage_str,"%s","''");
              return get_temp;
            }
        }
    else
        {// printf("%c9",ch);
            if (get_special())
            {
            printf("\t>> %s \t\t%s \n", theWordUpper, theWordUpper );
            sprintf(get_temp->myUsage_str,"%s",theWord);
            return get_temp;
            }
            else
            {
             free(get_temp);
              return NULL;
            }

        }


}

static char get_char()
{ int a = 0;
    theCh = source_buffer[ttr_start];
     //printf("^%c%d-%d^",theCh,a++, ttr_start);

    //  printf("thCh %c \n",theCh);

    return theCh; //source_buffer[ttr_start];

    /*
     If at the end of the current line (how do you check for that?),
     we should call get source line.  If at the EOF (end of file) we should
     set the character ch to EOF and leave the function.
     */

    /*
     Write some code to set the character ch to the next character in the buffer
     */
}
static void skip_blanks()
{
    while ((theCh == ' ') || (theCh == '\t'))
        {

         theCh = source_buffer[++ttr_start];
            // printf("^%c%d-%d^",theCh,a++, ttr_start);

         }
}
static  void skip_comment(void)
{

   while (theCh != '}')
        {

         theCh = source_buffer[++ttr_start];
            // printf("^%c%d-%d^",theCh,a++, ttr_start);

         }
        theCh = source_buffer[++ttr_start];

    /*
     Write some code to skip past the comments in the program and return a pointer
     to the first non blank character.  Watch out for the EOF character.
     */
}

//if return value is false it is an identfier
//else it is a reserve word.
static bool get_word(void)
{
    memset(theWord, '\0', sizeof(theWord));
    memset(theWordIdentifier, '\0', sizeof(theWordIdentifier));
    theWordIndex = 0;
    char ch = theCh;
    bool check_Reserve_Word = false;


 /*
     Write some code to Extract the word
     */

    while ( ((ch <= 'z')&&(ch>='a'))  || ( (ch <= 'Z')&& (ch >='A')) ||((ch <= '9') && (ch >='0')))
    {
        theWord[theWordIndex]= ch;
        theWordIndex++;
        ttr_start++;
        ch= get_char();
    }

    int g =0;
    //Downshift the word, to make it lower case
    memset(theWordUpper, '\0',sizeof(theWordUpper));
    while(theWord[g] != '\0')
    {   theWordUpper[g] = theWord[g];
        theWord[g] = tolower(theWord[g]);
        g++;
        }

    theCh = ch;


    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */
     //printf("\ncalling is_reserved_word\n");
    check_Reserve_Word = is_reserved_word(theWord);

 return check_Reserve_Word;

}


static bool get_number()
{
    /*
     Write some code to Extract the number and convert it to a literal number.
     */
   memset(theWord, '\0', sizeof(theWord));
    memset(theWordIdentifier, '\0', sizeof(theWordIdentifier));
    theWordIndex = 0;
    char ch = theCh;
    bool check_number = false;


 /*
     Write some code to Extract the word
     */
   while ((ch=='-') ||(ch =='e')||(ch=='.')|| (ch <= '9') && (ch >='0'))
            {
        theWord[theWordIndex]= ch;
        theWordIndex++;
        ttr_start++;
        ch= get_char();
        //printf("%c",ch);
        check_number = true;
    }
    int g =0;
    //Downshift the word, to make it lower case
    memset(theWordUpper, '\0',sizeof(theWordUpper));
    while(theWord[g] != '\0')
    {   theWordUpper[g] = theWord[g];
        //theWord[g] = tolower(theWord[g]);
        g++;
        }

//printf("\ngot theword lower: %s \n",theWord);
    theCh = ch;


    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */

 return check_number;


}
static bool get_string()
{
    /*
     Write some code to Extract the string
     */
    memset(theWord, '\0', sizeof(theWord));
    memset(theWordIdentifier, '\0', sizeof(theWordIdentifier));
    theWordIndex = 0;
    char ch = theCh;
    bool check_string = false;

    theCh = source_buffer[++ttr_start];
    ch = theCh;

 while (ch !='\'')
            {
        theWord[theWordIndex]= ch;
        theWordIndex++;
        ttr_start++;
        ch= get_char();
        //printf("%c",ch);
        check_string = true;
    }

 if   (check_string)
 {

      int g =0;
    //Downshift the word, to make it lower case
    memset(theWordUpper, '\0',sizeof(theWordUpper));
    while(theWord[g] != '\0')
    {   theWordUpper[g] = theWord[g];
        //theWord[g] = tolower(theWord[g]);
        g++;
        }
 theCh = source_buffer[++ttr_start];
 }
 else
    {
     theCh = source_buffer[++ttr_start];

    }

   return check_string;
}
static bool get_special(void)
{
    memset(theWord, '\0', sizeof(theWord));
    memset(theWordIdentifier, '\0', sizeof(theWordIdentifier));
    theWordIndex = 0;
    char ch = theCh;
    bool check_special = false;


 /*
     Write some code to Extract the word
     */

     switch(ch)
     {  case '^':
        case '*':
        case ',':
        case '(':
        case ')':
        case '-':
        case '+':
        case '=':
        case '[':
        case ']':
        //case ':':
        case ';':
       // case '<':
        //case '>':
        //case '.':
        case '/':
            theWord[theWordIndex]= ch;
            theWordIndex++;
            ttr_start++;
            theCh= get_char();
            ch=theCh;
            check_special = true;
            break;
        case ':':
            theWord[theWordIndex]= ch;
            theWordIndex++;
            ttr_start++;
            theCh= get_char();
            ch=theCh;
            if (theCh == '=')
            {   theWord[theWordIndex]= ch;
                theWordIndex++;
                ttr_start++;
                theCh= get_char();
                ch=theCh;
                check_special = true;
            }
            else{
                check_special = true;
            }
            break;
        case '<':
            theWord[theWordIndex]= ch;
            theWordIndex++;
            ttr_start++;
            theCh= get_char();
            ch=theCh;
            if (theCh == '=')
            {   theWord[theWordIndex]= ch;
                theWordIndex++;
                ttr_start++;
                theCh= get_char();
                ch=theCh;
                check_special = true;
            }
            else if (theCh == '>')
            {   theWord[theWordIndex]= ch;
                theWordIndex++;
                ttr_start++;
                theCh= get_char();
                ch=theCh;
                check_special = true;
            }
            else {
                check_special = true;   }
            break;
        case '>':
            theWord[theWordIndex]= ch;
            theWordIndex++;
            ttr_start++;
            theCh= get_char();
            ch=theCh;
            if (theCh == '=')
            {   theWord[theWordIndex]= ch;
                theWordIndex++;
                ttr_start++;
                theCh= get_char();
                ch=theCh;
                check_special = true;
            }
            else{
                check_special = true;
                }
            break;

        case '.':
            theWord[theWordIndex]= ch;
            theWordIndex++;
            ttr_start++;
            theCh= get_char();
            ch=theCh;
            if (theCh == '.')
            {   theWord[theWordIndex]= ch;
                theWordIndex++;
                ttr_start++;
                theCh= get_char();
                ch=theCh;
                check_special = true;
            }
            else{
            check_special = true;

            }
            break;
    default:
        check_special = false;
       break;
    }

//printf("\ngot theword: %s \n",theWord);
if (check_special)
{


    int g =0;
    //Downshift the word, to make it lower case
    memset(theWordUpper, '\0',sizeof(theWordUpper));
    while(theWord[g] != '\0')
    {   theWordUpper[g] = theWord[g];
       //theWord[g] = tolower(theWord[g]);
        g++;
        }
}

    /*
     Write some code to Check if the word is a reserved word.
     if it is not a reserved word its an identifier.
     */

 return check_special;

}
//static ??? downshift_word(???)
//{
    /*
     Make all of the characters in the incoming word lower case.
     */
//}
static BOOLEAN is_reserved_word(char myWord1[])
{   TokenCode isThere;
    int i,j;
   // int tot =0;
    BOOLEAN mayBe = FALSE;
   // isThere = WITH;
    //tot=Enum.GetNames(typeof(isThere)).Length;
    //tot = WITH;
    int result = 1;
    int d = strlen(myWord1);
    for (i=0;i <9; i++)
    { for (j=0; j <10; j++)
        {char * a[20];
       const RwStruct * ww;
        ww = &rw_table[i][j];
        if (ww->token_code != 0)
        {
        result = strncmp(rw_table[i][j].string, theWord,d );

            //printf("\nhello 9.2\n");
            if (result == 0)
            {
                mayBe = TRUE;
                rwI=i;
                rwJ=j;
            }
           // printf("\nhello 9.3\n");
        }// prevent core dump
        }//inner for
    }


    return mayBe;
}


