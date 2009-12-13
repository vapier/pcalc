%{

/*
**  pcalc LEX
*/

#include "ctype.h"
#include "string.h"

#include "hocdecl.h"
#include "symbol.h"
#include "pcalc.h"
#include "convert.h"

/* avoid fwrite() gcc warning */
#define fwrite(ptr, size, num, fp) ({ ssize_t s = fwrite(ptr, size, num, fp); s; })

extern YYSTYPE yylval;
extern  int lineno;



char    *name;
int     nchar, nword, nline ;

int     count(void);

//#define TEST
#define RET_EACH

%}

%%

"STORE" |
"store"                         {
                                count();

                                #ifdef RET_EACH
                                return(STORE);
                                #endif
                                }
"RESTORE" |
"restore"                       {
                                count();

                                #ifdef RET_EACH
                                return(RESTORE);
                                #endif
                                }
"TO" |
"to"                            {
                                count();

                                #ifdef RET_EACH
                                return(TO);
                                #endif
                                }

"FROM" |
"from"                          {
                                count();

                                #ifdef RET_EACH
                                return(FROM);
                                #endif
                                }


"OR" |
"or"                            {
                                count();

                                #ifdef RET_EACH
                                return('|');
                                #endif
                                }

"XOR" |
"xor"                           {
                                count();

                                #ifdef RET_EACH
                                return('X');
                                #endif
                                }

"AND" |
"and"                           {
                                count();

                                #ifdef RET_EACH
                                return('&');
                                #endif
                                }

0x[0-9a-fA-F]+[0-9a-fA-F]* {
                                #ifdef TEST
                                printf(" Hexadec: [ %s ]\n", yytext);
                                #endif

                                yylval.val = (double) hextoll(yytext + 2);

                                #ifdef RET_EACH
                                return(NUMBER);
                                #endif
                                }

0[by][01]+[01]*                 {
                                #ifdef TEST
                                printf(" Binary:  [ %s ]\n", yytext);
                                #endif

                                yylval.val = bintol(yytext + 2);

                                #ifdef RET_EACH
                                return(NUMBER);
                                #endif
                                }

0c[0-7]+[0-7]*                 {
                                #ifdef TEST
                                printf(" Octal:   [ %s ]\n", yytext);
                                #endif

                                yylval.val = otol(yytext + 2);

                                #ifdef RET_EACH
                                return(NUMBER);
                                #endif
                                }

[0-9]+[0-9]*                   {
                                #ifdef TEST
                                printf(" Decimal: [ %s ]\n", yytext);
                                #endif

                                yylval.val = (double) atoll(yytext);

                                #ifdef RET_EACH
                                return(NUMBER);
                                #endif
                                }

"."[0-9]+ |
[0-9]+"."[0-9]* |
[0-9]+[dDeE][+-]?[0-9]+ |
[0-9]+"."[0-9]*[dDeE][+-]?[0-9]+ |
"."[0-9]+[dDeE][+-]?[0-9]+     {
                                #ifdef TEST
                                printf(" Decimal: [ %s ]\n", yytext);
                                #endif

                                yylval.val = (double) atof(yytext);

                                #ifdef RET_EACH
                                return(NUMBER);
                                #endif
                                }

\".*\"                          {
                                Symbol *sp;

                                #ifdef TEST
                                printf(" string: [ %s ]\n", yytext);
                                #endif

                                sp  = lookup_sym(yytext);

                                if(sp)
                                    {
                                    yylval.sym = sp;
                                    return(sp->type);
                                    }
                                else
                                    {
                                    /*
                                     * Kill " "
                                     */
                                    yytext[strlen(yytext) - 1] = '\0';
                                    sp = install_sym(yytext + 1, STR, 0.0);
                                    sp->u.str = sp->name;   //str = strval
                                    yylval.sym = sp;
                                    }

                                #ifdef RET_EACH
                                return(STR);
                                #endif
                                }


\/\/.*                          {
                                #ifdef TEST
                                printf(" Comment: [ %s ]\n", yytext);
                                #endif

                                #ifdef RET_EACH
                                //return(COMM);
                                #endif
                                }

[a-zA-Z_]+[a-zA-Z0-9_]*         {
                                Symbol *sp;

                                #ifdef TEST
                                printf(" Ident:   [ %s ]\n", yytext);
                                #endif

                                sp  = lookup_sym(yytext);

                                if(sp)
                                    {
                                    yylval.sym = sp;

                                    if(sp->type == BUILTIN)
                                        {
                                        #ifdef TEST
                                        printf("Bultin: %s\n", sp->name );
                                        #endif

                                        #ifdef RET_EACH
                                        return(BUILTIN);
                                        #endif
                                        }
                                    else if(sp->type == IBUILTIN)
                                        {
                                        #ifdef TEST
                                        printf("Bultin: %s\n", sp->name );
                                        #endif

                                        #ifdef RET_EACH
                                        return(IBUILTIN);
                                        #endif
                                        }
                                    else if(sp->type == VAR)
                                        {
                                        #ifdef TEST
                                        printf("Var: %s\n", sp->name );
                                        #endif

                                        #ifdef RET_EACH
                                        return(VAR);
                                        #endif
                                        }
                                    }
                                else
                                    {
                                    sp = install_sym(yytext, VAR, 0.0);
                                    yylval.sym = sp;
                                    //yylval.sym->u.val = 0.0;

                                    #ifdef RET_EACH
                                    return(VAR);
                                    #endif
                                    }
                                }

$[a-zA-Z_]+[a-zA-Z0-9_]*       {

                                yylval.sym = lookup_sym(yytext);

                                if(!yylval.sym)
                                    {
                                    yylval.sym =
                                        install_sym(yytext, STRVAR, 0.0);
                                    }

                                #ifdef TEST
                                printf(" Stringvar: [ %s ]\n", yytext);
                                #endif

                                #ifdef RET_EACH
                                return(STRVAR);
                                #endif
                                }

[\r]                            {
                                #ifdef TEST
                                printf(" Comment: [ %s ]\n", yytext);
                                #endif

                                #ifdef RET_EACH
                                lineno++;
                                //return(COMM);
                                #endif
                                }

[\n]                            {   }

[ \t]+                          {
                                #ifdef TEST
                                //printf(" White:   [ %s ]\n", yytext);
                                #endif

                                #ifdef RET_EACH
                                //return(WHITE);
                                #endif
                                }

";"                             {
                                count();

                                #ifdef RET_EACH
                                return(';');
                                #endif
                                }

"{"                             {
                                count();

                                #ifdef RET_EACH
                                return('{');
                                #endif
                                }

"}"                             {
                                count();

                                #ifdef RET_EACH
                                return('}');
                                #endif
                                }

","                             {
                                count();

                                #ifdef RET_EACH
                                return(',');
                                #endif
                                }

":"                             {
                                count();

                                #ifdef RET_EACH
                                return(':');
                                #endif
                                }

"="                             {
                                count();

                                #ifdef RET_EACH
                                return('=');
                                #endif
                                }

"("                             {
                                count();

                                #ifdef RET_EACH
                                return('(');
                                #endif
                                }

")"                             {
                                count();

                                #ifdef RET_EACH
                                return(')');
                                #endif
                                }

"["                             {
                                count();

                                #ifdef RET_EACH
                                return('[');
                                #endif
                                }

"]"                             {
                                count();

                                #ifdef RET_EACH
                                return(']');
                                #endif
                                }

"."                             {
                                count();

                                #ifdef RET_EACH
                                return('.');
                                #endif
                                }

"&"                             {
                                count();

                                #ifdef RET_EACH
                                return('&');
                                #endif
                                }

"!"                             {
                                count();

                                #ifdef RET_EACH
                                return('!');
                                #endif
                                }

"~"                             {
                                count();

                                #ifdef RET_EACH
                                return('~');
                                #endif
                                }

"-"                             {
                                count();

                                #ifdef RET_EACH
                                return('-');
                                #endif
                                }

"+"                             {
                                count();

                                #ifdef RET_EACH
                                return('+');
                                #endif
                                }

"*"                             {
                                count();

                                #ifdef RET_EACH
                                return('*');
                                #endif
                                }

"/"                             {
                                count();

                                #ifdef RET_EACH
                                return('/');
                                #endif
                                }

"%"                             {
                                count();

                                #ifdef RET_EACH
                                return('%');
                                #endif
                                }

"<<"                            {
                                count();

                                #ifdef RET_EACH
                                return('<');
                                #endif
                                }

">>"                            {
                                count();

                                #ifdef RET_EACH
                                return('>');
                                #endif
                                }

"^"                             {
                                count();

                                #ifdef RET_EACH
                                return('^');
                                #endif
                                }

"|"                             {
                                count();

                                #ifdef RET_EACH
                                return('|');
                                #endif
                                }

"?"                             {
                                count();

                                #ifdef RET_EACH
                                return('?');
                                #endif
                                }

.                              {
                                count();

                                #ifdef RET_EACH
                                //return(yytext[0]);
                                #endif
                               }                    /* ignore all the rest */

%%

int     count(void)

{
	return 0;
}
