%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);

int regs[26];
int base;
%}
%start list
%token DIGIT LETTER
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%%                   /* beginning of rules section */
list:                       /*empty */
         |
        list stat '\n'
         |
        list error '\n'
         {
           printf("errorrrrrr\n");
           yyerrok;
         }
         ;
stat:    expr
         {
           printf("%d\n",$1);
         }
         |
         LETTER '=' expr
         {
           printf("here\n");
           regs[$1] = $3;
         }
         ;
expr:    '(' expr ')'
         {
           $$ = $2;
         }
         |
         expr '+' expr
         {
           $$ = $1 + $3;
         }
          |
         expr '-' expr
         {
           $$ = $1 - $3;
         }
         |
         LETTER
         {
           $$ = regs[$1];
         }
         |
         number
         ;
number:  DIGIT
         {
           //printf("first here!!");
           $$ = $1;
           base = ($1==0) ? 8 : 10;
         }       |
         number DIGIT
         {
           printf("%d %d \n", $1, $2);
           $$ = base * $1 + $2;
         }
         ;
%%
int main()
{
 return(yyparse());
}
void yyerror(const char *s)
{
  fprintf(stderr, "%s\n",s);
}
int yywrap()
{
  return(1);
}
