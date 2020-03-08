#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*grammar is :
  S->aE
  E->+bT
  T->*cT/e  (e represents epsilon).
  */
  
//******************the expression valid for this grammar is : a+b*c$





char exp[10];// A global string to store the expression.
int count=0; //global variable to take one character to compare at a time.
void S();  //routine for starting symbol.
void E();
void T();
void match(char t); //function to match the character.

int main()
{
	printf("Enter the expression:\n"); //user input string.
	scanf("%s",exp);
	S();  //call start subroutine.
	if(exp[count]=='$') printf("expression is valid\n");   
	else printf("Invalid expression\n");
	return 0;
	
}

//function for first production from start symbol S.
void S()
{
	if(exp[count]=='a')
	{
		match('a');
		E();
	}
}

//function for second production.
void E()
{
	if(exp[count] =='+')
	{
		match('+');
		match('b');
		T();
	}
}
//function for third production of non terminal T
void T()
{
	if(exp[count]=='*')
	{
		match('*');
		match('c');
		T();
	}
	else return ;
}

//function for matching.
void match(char t)
{
	if(exp[count]== t)
	{
		count++;
	}
	else 
	{
		printf("Invalid Expression\n");
		exit(0);
		
	}
}
