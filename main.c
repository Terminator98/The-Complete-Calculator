#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "CSTACK.h"

int main()
{
	char postfix[100];
	char infix[100] = "(500.25+400.36+125.48-(93.24*5))";  //Maximum size of an expresison
	int infix_size = strlen(infix);
	

	welcome();
	// Uncomment the line below to enter the equation yourself but don't forget to delete the initial value of infix first
	//gets_s(infix);

	if (missingBrackets(infix) == 0 && missingOperand(infix) == 0) {

		conversion(infix, postfix, infix_size);
		
		evaluation(postfix);
	}
	else if (missingBrackets(infix) == 1 && missingOperand(infix) == 1)
		printf("Please check your expression :(\n");
	else if (missingBrackets(infix) == 1)
		printf("There's a missing bracket in your expression :(\n");
	else if (missingOperand(infix) == 1)
		printf("There's a missing operand in your expression :(\n");
	return 0;
}