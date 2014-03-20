#ifndef _lab2_globals
#define _lab2_globals


//  define global variable
#define MAX_LINES_PER_PAGE_lab2  50
#define fileNameLength  32
#define dateTimeLength  32
#define fileLineLength  256
#define lineMax 65


//  initialize file pointers and other variables
FILE *source_file, *outputFile;
char source_name[fileNameLength];
char dateAndTime[dateTimeLength];


//  get system time now
time_t now;
extern int line_number;
extern bool testing;
extern int testCase;

//char source_name[MAX_FILE_NAME_LENGTH];
//char date[DATE_STRING_LENGTH];
//FILE *source_file;



#endif

