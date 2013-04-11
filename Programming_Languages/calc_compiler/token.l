%{
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>




using namespace std;
extern int put_string(char *str, int len);

/* definitions */
#define EOF_NUM              0          
#define SEMINCOLON_NUM       2    
#define COMMA_NUM            4    
#define LPARENTH_NUM         5  
#define RPARENTH_NUM         6   
#define EQ_NUM               9         
#define MINUS_NUM            11     
#define PLUS_NUM             59       
#define TIMES_NUM            12     
#define ID_NUM               17     
#define INTEGERCONST_NUM     18   
#define BEGIN_NUM            24    
#define DIV_NUM              26           
#define INT_NUM              28        
#define END_NUM              31         
#define IS_NUM               40          
#define PROGRAM_NUM          46     
#define VAR_NUM              55       
#define PRINT_NUM            57     


vector<string> string_table;
int string_table_index = 0;

int yyline = 1, yycolumn = 1;
%}

delim   [ \t]
ws      {delim}+
letter [a-zA-Z]
digit  [0-9]
id     {letter}({letter}|{digit})*
number {digit}+

%%
\n        {yyline++;yycolumn=1;}
{ws}      {yycolumn += yyleng;}

[bB][eE][gG][iI][nN] {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return (BEGIN_NUM);}
[dD][iI][vV]		{yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return (DIV_NUM);}
[iI][nN][tT][eE][gG][eE][rR]		{yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return (INT_NUM);}
[eE][nN][dD]           {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng);  return(END_NUM);}
[iI][sS]        {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(IS_NUM);}
[pP][rR][iI][nN][tT] {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(PRINT_NUM);}
[pP][rR][oO][gG][rR][aA][mM]   {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(PROGRAM_NUM);}
[vV][aA][rR]		{yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return (VAR_NUM);}
 


{id}      {  yycolumn += yyleng;
		yylval.index = put_string(yytext, yyleng); 
             return (ID_NUM);
          }
{number}  {yycolumn += yyleng; yylval.index = atoi(yytext); return (INTEGERCONST_NUM);}

";"       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(SEMINCOLON_NUM);}
","       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(COMMA_NUM);}
"("       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(LPARENTH_NUM);}
")"       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(RPARENTH_NUM);}
"="       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(EQ_NUM);}
"-"       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return(MINUS_NUM);}
"+"         {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return (PLUS_NUM);}
"*"       {yycolumn += yyleng; yylval.index = put_string(yytext, yyleng); return (TIMES_NUM);}
.         {
           printf("inproper character '%s', line=%d column=%d\n", 
           yytext, yyline, yycolumn); yycolumn += yyleng;}

%%

int yywrap()
{  if (feof(stdin)) return 1;
   return 0;
}

int put_string(char *str, int len)
{
  string s(str);
  string_table.push_back(s);
  string_table_index++;
  return string_table_index-1; 
} 





