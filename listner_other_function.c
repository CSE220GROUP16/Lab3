

#include <stdio.h>
#include <stdlib.h> /* for atoi() */
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "listner_other_function.h"
#include "globals.h"




/*  ************************************************
    Function take input file as input and open the
    file for reading.  it will exit with false if
    file not readable.  else it will print time stamp
    to output file.
    ************************************************/
    /*
    // did not use in lab 3
    // used the one provided in the lab3 homework
void init_lister(char fileN[] ){
char *moder = "r";
strcpy(source_name,fileN); // destination, source
source_file = fopen(source_name, moder);
//case 2
if(testCase == 2)
   testForCase2(source_file);




if (source_file == NULL) {
  printf("Can't open input file %s!\n", source_name);
  exit(1);
}
time(&now);
sprintf(dateAndTime, "%s", ctime(&now));
printf("input file name is : %s  time is: %s", source_name, dateAndTime );
}

*/

/*  ************************************************
    function reads text line by line with fgets as
    line in not NULL.
    ************************************************/
bool get_source_line(){
// variable declaration and init
bool value = false;
bool line2Long = false;
char source_buffer[fileLineLength];
char print_buffer[fileLineLength];
char * temp;


// continue if is not end of the file.
if( fgets (source_buffer, fileLineLength, source_file)!=NULL ) {
        // truncate the line array if line size is larger than allowed size
        if(strlen(source_buffer)>lineMax)
        {
        temp = &source_buffer[lineMax]; //temp holds value of max line
        source_buffer[lineMax]='\0';   //line max value to eol
        line2Long = true;              //line2Long is true
        }
          value = true;                //value use for continue reading
          line_number += 1;            //line number increment by 1
          //use sprintf function to store line number and line content
          sprintf(print_buffer,"%d: %s",line_number,source_buffer);
          print_line_lab2(print_buffer);    //call print line function


        //restore to the original line content.
        if (line2Long)
        {
            strcpy(temp, &source_buffer[lineMax]);
            printf("\n");
        }
    }


//value = false;
return value;
}

