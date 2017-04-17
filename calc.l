%{
	#include "y.tab.h"
	extern int yylval;
%}

%%
[ \t] {;}
[0-9]+	{yylval=atoi(yytext); printf("\nget %d\n",yylval); return NUMBER;}
[-+*/\n] {return *yytext; }
. {yyerror("hi"); return 0;}
%%

int yywrap(void)
{
	return 1;
}

