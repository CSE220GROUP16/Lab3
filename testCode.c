#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "testCode.h"

void test001();
void test002();


void test001()
{
    printf(" failed test 01: missing input file, should be ./lab3 pascalFile.pas\n\t you need to enter the PASCAL source file\n \texited program");
        exit(1);
}


void test002(char * sn)
{
 printf("failed test 02: could not open file:%s ; exited program",sn);
}
