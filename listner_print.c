#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <string.h>
#include <time.h>
#include <stdbool.h>


#include "listner_print.h"
#include "globals.h"


/*  ************************************************
    function print each line with line number in front
    ************************************************/
void print_line_lab2(char print_buff[]){
    static int  line_count =0; //that variable alive even not inside the function
    line_count +=1;            //increment line count by 1
    //print page header and line content
    if ((line_count % MAX_LINES_PER_PAGE_lab2) == 1)
    {print_page_header(); }
    printf("%s",print_buff);
}
/*  ************************************************
    Function just print page header
    ************************************************/
void print_page_header(){
    printf("**************************************\n");
    printf("************* Page Header  ***********\n");
    printf("*************              ***********\n")     ;
    printf("**************************************\n");
}

