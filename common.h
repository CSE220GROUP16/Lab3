//
//  common.c
//  Lab3
//
//  Created by Bryce Holton.
//  Copyright (c) 2014 Bryce Holton. All rights reserved.
//

#ifndef CSE220_project2_common_h
#define CSE220_project2_common_h

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#define FORM_FEED_CHAR          '\f'
#define MAX_FILE_NAME_LENGTH    32
#define MAX_SOURCE_LINE_LENGTH  256
#define MAX_TOKEN_STRING_LENGTH MAX_SOURCE_LINE_LENGTH
#define MAX_PRINT_LINE_LENGTH   80
#define MAX_LINES_PER_PAGEw      30
#define DATE_STRING_LENGTH      26

 char source_buffer[MAX_SOURCE_LINE_LENGTH];
 int ttr_start;
 char theCh;
 char theWordUpper[MAX_TOKEN_STRING_LENGTH];
 char theWord[MAX_TOKEN_STRING_LENGTH];
 char theWordIdentifier[MAX_TOKEN_STRING_LENGTH];
 int theWordIndex;
 int rwI;
 int rwJ;
 int aaaaa;

typedef enum
{
    ttab = '\t',
    sspace = ' '
} mySpacess;

typedef enum
{
    FALSE, TRUE
}
BOOLEAN;

/***************************
 Token Codes
 ***************************/
typedef enum
{
    NO_TOKEN, IDENTIFIER, NUMBER, STRING, UPARROW, STAR, LPAREN,
    RPAREN, MINUS, PLUS, EQUAL, LBRACKET,
    RBRACKET, COLON, SEMICOLON, LT, GT, COMMA, PERIOD, SLASH,
    COLONEQUAL, LE, GE, NE, DOTDOT, END_OF_FILE, ERROR, AND,
    ARRAY, BEGIN, CASE, CONST, DIV, DO, DOWNTO, ELSE, END, FFILE,
    FOR, FUNCTION, GOTO, IF, IN, LABEL, MOD, NIL, NOT, OF, OR, PACKED,
    PROCEDURE, PROGRAM, RECORD, REPEAT, SET, THEN, TO, TYPE, UNTIL,
    VAR, WHILE, WITH,
}
TokenCode;

/*****************************
 Literal Type
 *****************************/
typedef enum
{
    INTEGER_LIT, REAL_LIT, STRING_LIT,
}
LiteralType;

typedef union
{
    int lv_int;
    char lv_string[MAX_SOURCE_LINE_LENGTH];
    float lv_real;
}
LiteralValue;
    //LiteralValue numbers;
	//numbers.PI = 3.14;
	//numbers.B = 50;


/**************
 this is a valid Pascal token.  A token must have a literal type,
 a literal value, and a token code.  It also must have a link to
 another token since this must be stored as a linked list.
 ***************/
typedef struct Token_t
{
    LiteralType lt;
    LiteralValue lv;
    TokenCode tc;
    struct Token_t * next; //Missing code goes here
   int myUsage_int;
   char myUsage_str[MAX_SOURCE_LINE_LENGTH];
   int val;
}
Token;

#endif
