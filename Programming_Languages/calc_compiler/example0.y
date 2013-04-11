
/* this file define all teh integer values corresponse with 
 * each type of token.
 */


%{
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern int yyline;
ofstream outfile;

struct xxx {
  	int val;
  	string str_rep;
	bool initialized;
} sym_table[10000];
int sym_table_index = 0;

void yyerror(const char * str);
int yyparse();

%}

%union {
  	int index;
	struct {
	    int val;
	    char str_rep[1000];
	  } attr;
}

%token <index> EOF_NUM              0          
%token <index> SEMINCOLON_NUM       2    
%token <index> COMMA_NUM            4    
%token <index> LPARENTH_NUM         5  
%token <index> RPARENTH_NUM         6   
%token <index> EQ_NUM               9         
%token <index> MINUS_NUM            11     
%token <index> PLUS_NUM             59       
%token <index> TIMES_NUM            12     
%token <index> ID_NUM               17     
%token <index> INTEGERCONST_NUM     18   
%token <index> BEGIN_NUM            24    
%token <index> DIV_NUM              26           
%token <index> INT_NUM              28        
%token <index> END_NUM              31         
%token <index> IS_NUM               40          
%token <index> PROGRAM_NUM          46     
%token <index> VAR_NUM              55       
%token <index> PRINT_NUM            57         

%right  EQ_NUM
%left  PLUS_NUM  MINUS_NUM
%left  TIMES_NUM  DIV_NUM


%type <attr> exp
%type <attr> term
%type <attr> factor
%type <attr> stmt
%type <attr> decl
%type <attr> decl_tail
%type <attr> declaration
%type <attr> declaration_tail
%type <attr> com_stmt
%type <attr> stmt_tail


%%   /* specification */

program: PROGRAM_NUM ID_NUM IS_NUM 
        {
        print_header();
        } declaration 
        {print_header2();
        }com_stmt; 

exp: 
    term 
    {
        
      $$.val = $1.val;
      strcpy($$.str_rep, $1.str_rep);
    }
    
    |
    
    MINUS_NUM term 
    {
        
      $$.val = $2.val * -1;
      string rhs($2.str_rep);
      string final("-" + rhs);
      strcpy($$.str_rep, final.c_str());
    } %prec  TIMES_NUM
    
    |
    
    term PLUS_NUM term 
    {
        
      $$.val = $1.val + $3.val;
      string lhs($1.str_rep);
      string rhs($3.str_rep);
      string final( lhs + " + " + rhs);
      strcpy($$.str_rep, final.c_str());
    }
    
    |
    
    term MINUS_NUM term 
    {
        
      $$.val = $1.val - $3.val;
      string lhs($1.str_rep);
      string rhs($3.str_rep);
      string final( lhs + " - " + rhs);
      strcpy($$.str_rep, final.c_str());
    }
    ;

term: 
    factor 
    {
      $$.val = $1.val;
      strcpy($$.str_rep, $1.str_rep);
    }
    | 
    factor TIMES_NUM factor 
    {
        
      $$.val = $1.val * $3.val;
      string lhs($1.str_rep);
      string rhs($3.str_rep);
      string final( lhs + " * " + rhs);
      strcpy($$.str_rep, final.c_str());
    }
    | 
    factor DIV_NUM factor
    {
      
      if($3.val == 0) {
                cout << "yyerror: divided by zero error. at line " << yyline << endl;
                exit(1);

        }  
  
      $$.val = $1.val / $3.val;
      //CHECK FOR DIVIDE BY ZERO
        
      string lhs($1.str_rep);
      string rhs($3.str_rep);
      string final( lhs + " / " + rhs);
      strcpy($$.str_rep, final.c_str());
    }
    ;

factor: 
    INTEGERCONST_NUM 
	{
        
		$$.val = $1;
		//sym_table[$$.val].val = $1; 
		strcpy($$.str_rep, convertInt($1).c_str());
	}
    | 
    ID_NUM 
	{	
        
        string id = string_table[$1];
        int id_table_index = is_declared(string_table[$1]);
        if(id_table_index != -1)
        {
            if(sym_table[id_table_index].initialized == true)
                $$.val = sym_table[id_table_index].val;
            //ELSE THROW ERROR END PROGRAM
            else {
                cout << "yyerror: Variable " << id << " uninitiated at line " << yyline << endl;
                exit(1);
            }
                
        } else {
            cout << "yyerror: Variable " << id << " undeclared at line " << yyline << endl;
            exit(1);

        }

        strcpy($$.str_rep, id.c_str());
       
	}
    | 
    LPARENTH_NUM exp RPARENTH_NUM
	{	
		$$.val = $2.val;
        string i($2.str_rep);
        string enclosed_w_parents("(" + i + ")");
        strcpy($$.str_rep, enclosed_w_parents.c_str());
	} %prec  TIMES_NUM  ;

decl: 
    INT_NUM ID_NUM decl_tail
	{
		string _int = "int";
        string id = string_table[$2];
        if(is_declared(id) == -1) {
            $2 = sym_table_index++;
            sym_table[$2].str_rep = id;
            sym_table[$2].initialized = false;
        } else {
            cout << "yyerror: Variable " << id << " duplicate declaration at line " << yyline << endl;
            exit(1);
        }
		string tail = $3.str_rep;
		string final(_int + " " + id + tail);
        
        strcpy($$.str_rep, final.c_str()) ;
	};

decl_tail: 
    COMMA_NUM ID_NUM decl_tail 
    {
        string id = string_table[$2];
        
        string tail($3.str_rep);
        string final(";\nint " + id + tail);

        if(is_declared(id) == -1) {

            $2 = sym_table_index++;
            sym_table[$2].str_rep = id;
            sym_table[$2].initialized = false;

        } else {
                cout << "yyerror: Variable " << id << " duplicate declaration at line " << yyline << endl;
                exit(1);
            }
        
        strcpy($$.str_rep, final.c_str());
    }
    | /*epsilon*/
    {

    }; 

declaration: 
    VAR_NUM decl declaration_tail;
    {
        
        string decl($2.str_rep);
        string declaration_tail($3.str_rep);
        string final(decl + declaration_tail);
        strcpy($$.str_rep, final.c_str());
        print_exp(final);
 
    }
declaration_tail: 
    /*epsilon*/ 
    {
        
        string semicolon(";\n");
        strcpy($$.str_rep, semicolon.c_str());
    }
    | 
    SEMINCOLON_NUM decl declaration_tail
    {
        
        string decl($2.str_rep);
        string tail($3.str_rep);
        string final(";\n" + decl + tail);
        strcpy($$.str_rep, final.c_str());
    }
    ; 

com_stmt: BEGIN_NUM stmt stmt_tail END_NUM {print_end();};
    {
        
        string statement($2.str_rep);
        string tail($3.str_rep);
        string final(statement + tail);
        strcpy($$.str_rep, final.c_str());
   
    }

stmt: 
    ID_NUM EQ_NUM exp 
	{       
            
            int id_table_index = is_declared(string_table[$1]);
            if(id_table_index != -1)
            {
                sym_table[id_table_index].initialized = true;
                sym_table[id_table_index].val = $3.val;
                
                string id(sym_table[id_table_index].str_rep);
                string exp($3.str_rep);

                string final(id + " = " + exp);
                print_exp(final);

            }//NOT DECLARED THROW ERROR, END PROGRAM
            else {
                cout << "yyerror: Variable " << string_table[$1] << " undeclared at line " << yyline << endl;
                exit(1);
            }    

	}
    | 
    PRINT_NUM exp
	{
        
		string s($2.str_rep);
		string s1("cout << " + s + " << endl;");
        strcpy($$.str_rep, s1.c_str());
        cout << sym_table[is_declared($2.str_rep)].val << endl;
        print_exp(s1);
	}	
	;    

stmt_tail: 
    /*epsilon*/ 
    {
        
        string semicolon(";\n");
        strcpy($$.str_rep, semicolon.c_str());

    }
    | 
    SEMINCOLON_NUM stmt stmt_tail 
    {
        
        string statement($2.str_rep);
        string tail($3.str_rep);
        string final(";\n" + statement + tail);
        strcpy($$.str_rep, final.c_str());
    }
    | 
    stmt 
    {   
        string statement($1.str_rep);
        string final(";\n" + statement);
        strcpy($$.str_rep, final.c_str());
    }
    ;



%%


#include "lex.yy.c"
#include <stdio.h>

void print_header()
{
  outfile.open("mya.cpp");
  outfile << "#include <iostream>\n";
  outfile << "#include <stdio.h>\n";
  outfile << "using namespace std;\n\n";
}

void print_header2()
{
    outfile << "main()\n";
    outfile << "{\n";
}

void print_end()
{
  outfile << "}\n";
  outfile.close();
}

int is_declared(string var) 
{ 
    int x;
    int idx = -1;
    for(x = 0; x < sym_table_index; x++) {
        if(var == sym_table[x].str_rep)
        {   idx = x;
            break;
        }
    }

    return idx;
}

void print_exp(string s)
{
  outfile << s << endl;
}

string convertInt(int num)
{
  char t[1000];
  sprintf(t, "%d", num);
  
  string r(t);
  return r;
}

void yyerror(const char *str)
{    printf("yyerror: %s at line %d\n", str, yyline);
}

int yyparse();

main()
{
  if (!yyparse()) {printf("accepted\n");}
  else printf("reject\n");
}    









