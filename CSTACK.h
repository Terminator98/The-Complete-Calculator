#ifndef CSTACK
#define CSTACK


void welcome() {
	printf("**********************************\n");
	printf("Welcome to The Complete Calculator\n");
	printf("**********************************\n\n");
	printf("Please do your best to enter the equation with no spaces or errors\n");
	printf("Be happy because this calculator can detect the floating point and multiple digits :)\n\n");
}

////////////////////////////////////////////////////

/////////////Stack for conversion///////////////////
struct Stack
{
	char* data;
	int size;
	int sp;

	Stack()
	{
		data = NULL;
		size = 0;
		sp = -1;
	}
	~Stack()
	{
		if (data != NULL)
			free(data);
	}
};




int initialize(Stack* s, int size)
{
	s->data = (char*)malloc(sizeof(char) * size);
	if (s->data == NULL)
		return 0;
	s->size = size;
	return 1;
}

int pop(Stack* s, char* item)
{
	if (s->data == NULL)
		return 0;
	if (s->sp == -1)
		return -1;
	*item = s->data[s->sp];
	s->sp--;
	return 1;
}

int push(Stack* s, char item)
{
	if (s->data == NULL)
		return 0;
	if (s->sp + 1 == s->size)
		return -1;
	s->sp++;
	s->data[s->sp] = item;
}

int isEmpty(Stack* s)
{
	if (s->sp == -1)
		return 1;
	else
		return 0;
}
//////////////////////////////////////////////////////////////////////////


///////////////////STACK FOR EVAL//////////////////////////////////

struct FloatStack
{
	float* data;
	int size;
	int sp;

	FloatStack()
	{
		data = NULL;
		size = 0;
		sp = -1;
	}
	~FloatStack()
	{
		if (data != NULL)
			free(data);
	}
};

int floatinitialize(FloatStack* s, int size)
{
	s->data = (float*)malloc(sizeof(float) * size);
	if (s->data == NULL)
		return 0;
	s->size = size;
	return 1;
}

int floatpop(FloatStack* s, float* item)
{
	if (s->data == NULL)
		return 0;
	if (s->sp == -1)
		return -1;
	*item = s->data[s->sp];
	s->sp--;
	return 1;
}

int floatpush(FloatStack* s, float item)
{
	if (s->data == NULL)
		return 0;
	if (s->sp + 1 == s->size)
		return -1;
	s->sp++;
	s->data[s->sp] = item;
}

int floatisEmpty(FloatStack* s)
{
	if (s->sp == -1)
		return 1;
	else
		return 0;
}


////////////////////////////////////////////////////////////////////


int isOperator(char ch)
{
	char ops[] = { '*', '/', '+', '-', '^' , '%' };
	for (int i = 0; i < strlen(ops); i++)
	{
		if (ch == ops[i])
			return 1;
	}
	return 0;
}

int getOperatorPriority(char op)
{
	if (op == '^')
		return 3;
	if (op == '*' || op == '/' || op == '%')
		return 2;
	if (op == '+' || op == '-')
		return 1;
	return 0;
}

int missingBrackets(char expr[]) {
	int rSum = 0;
	int lSum = 0;
	for (int i = 0; i < strlen(expr); i++) {
		if (expr[i] == '(')
			lSum++;
		else if (expr[i] == ')')
			rSum++;
	}
	if (lSum == rSum)
		return 0;
	return 1;
}

int missingOperand(char expr[]) {
	int opSum = 0;
	int orSum = 0;
	for (int i = 0; i < strlen(expr); i++) {
		if (isOperator(expr[i]) == 1)
			opSum++;
		else if (expr[i] != '(' && expr[i] != ')') {
			while (i < strlen(expr) && (isdigit(expr[i]) || expr[i] == '.')) {
				i++;
			}
			i--;
			orSum++;
		}
	}
	if (opSum + 1 == orSum)
		return 0;
	return 1;
}

void conversion(char infix[], char* postfix, int infix_size) {
	Stack s;
	int postfix_index = 0;
	initialize(&s, infix_size);

	//Iterate through the whole infix input
	for (int i = 0; i < strlen(infix); i++)
	{
		if (infix[i] == '(')
			push(&s, infix[i]);
		else if (infix[i] == ')')
		{
			while (s.data[s.sp] != '(') {

				pop(&s, &postfix[postfix_index++]);
				postfix[postfix_index++] = ' ';
			}
			//Open bracket is still in the stack
			char tmp;
			pop(&s, &tmp);	//Discard the open bracket
		}
		else if (isOperator(infix[i]))
		{
			//As long as the operator in the current infix position is <= the one on top of the stack
			while (getOperatorPriority(infix[i]) <= getOperatorPriority(s.data[s.sp])) {

				pop(&s, &postfix[postfix_index++]);
				postfix[postfix_index++] = ' ';
			}
			//Ready to push the current operator into the stack
			push(&s, infix[i]);
		}


		//Assume it's a digit
		else {

			while (i < infix_size && (isdigit(infix[i]) || infix[i] == '.')) {
				postfix[postfix_index++] = infix[i];
				i++;
			}
			i--;
			postfix[postfix_index++] = ' ';
		}
	}

	//Make sure that the stack is empty
	while (!isEmpty(&s)) {
		postfix[postfix_index++] = ' ';
		pop(&s, &postfix[postfix_index++]);
	}

	postfix[postfix_index] = '\0';

	printf("The infix is %s", infix);
}


void evaluation(char postfix[]) {
	FloatStack es;
	floatinitialize(&es, strlen(postfix));
	//Evaluation
	for (int i = 0; i < strlen(postfix); i++)
	{

		if (isdigit(postfix[i]) || (postfix[i] == ' ' && postfix[i + 1] == '.')) {
			char c[20] = "";
			int j = 0;
			while (isdigit(postfix[i]) || postfix[i] == '.') {
				c[j++] = postfix[i++];
			}
			floatpush(&es, atof(c));
		}

		// if it's space
		else if (postfix[i] == ' ')
			continue;
		else //Is operator
		{
			float x, y;
			if (postfix[i] == '+')
			{
				floatpop(&es, &y);
				floatpop(&es, &x);
				floatpush(&es, x + y);
			}
			if (postfix[i] == '-')
			{
				floatpop(&es, &y);
				floatpop(&es, &x);
				floatpush(&es, x - y);
			}
			if (postfix[i] == '*')
			{
				floatpop(&es, &y);
				floatpop(&es, &x);
				floatpush(&es, x * y);
			}
			if (postfix[i] == '/')
			{
				floatpop(&es, &y);
				floatpop(&es, &x);
				floatpush(&es, x / y);
			}
			if (postfix[i] == '%')
			{

				floatpop(&es, &y);
				floatpop(&es, &x);
				floatpush(&es, (int)x % (int)y);
			}
			if (postfix[i] == '^')
			{
				floatpop(&es, &y);
				floatpop(&es, &x);
				floatpush(&es, pow(x, y));
			}
		}
	}

	float result;
	floatpop(&es, &result);
	printf("The postfix is %s\n", postfix);
	printf("The final result is %f\n", result);
}

#endif // !CSTACK

