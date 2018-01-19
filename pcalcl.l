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

//#define TEST

%}

%%

"STORE" |
"store"                         {
                                return(STORE);
                                }
"RESTORE" |
"restore"                       {
                                return(RESTORE);
                                }
"TO" |
"to"                            {
                                return(TO);
                                }

"FROM" |
"from"                          {
                                return(FROM);
                                }


"OR" |
"or"                            {
                                return('|');
                                }

"XOR" |
"xor"                           {
                                return('X');
                                }

"AND" |
"and"                           {
                                return('&');
                                }

0[xX][0-9a-fA-F]+[0-9a-fA-F]* {
                                #ifdef TEST
                                printf(" Hexadec: [ %s ]\n", yytext);
                                #endif

                                yylval.val = (double) hextoll(yytext + 2);

                                return(NUMBER);
                                }

0[by][01]+[01]*                 {
                                #ifdef TEST
                                printf(" Binary:  [ %s ]\n", yytext);
                                #endif

                                yylval.val = bintol(yytext + 2);

                                return(NUMBER);
                                }

0[co]?[0-7]+[0-7]*              {
                                #ifdef TEST
                                printf(" Octal:   [ %s ]\n", yytext);
                                #endif

                                yylval.val = otol(yytext + 1 + (yytext[1] == 'c' || yytext[1] == 'o' ? 1 : 0));

                                return(NUMBER);
                                }

[0-9]+[0-9]*                   {
                                #ifdef TEST
                                printf(" Decimal: [ %s ]\n", yytext);
                                #endif

                                yylval.val = (double) atoll(yytext);

                                return(NUMBER);
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

                                return(NUMBER);
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

                                return(STR);
                                }


\/\/.*                          {
                                #ifdef TEST
                                printf(" Comment: [ %s ]\n", yytext);
                                #endif

                                //return(COMM);
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

                                        return(BUILTIN);
                                        }
                                    else if(sp->type == IBUILTIN)
                                        {
                                        #ifdef TEST
                                        printf("Bultin: %s\n", sp->name );
                                        #endif

                                        return(IBUILTIN);
                                        }
                                    else if(sp->type == VAR)
                                        {
                                        #ifdef TEST
                                        printf("Var: %s\n", sp->name );
                                        #endif

                                        return(VAR);
                                        }
                                    }
                                else
                                    {
                                    sp = install_sym(yytext, VAR, 0.0);
                                    yylval.sym = sp;
                                    //yylval.sym->u.val = 0.0;

                                    return(VAR);
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

                                return(STRVAR);
                                }

[\r]                            {
                                #ifdef TEST
                                printf(" Comment: [ %s ]\n", yytext);
                                #endif

                                lineno++;
                                //return(COMM);
                                }

[\n]                            {   }

[ \t]+                          {
                                #ifdef TEST
                                //printf(" White:   [ %s ]\n", yytext);
                                #endif

                                //return(WHITE);
                                }

";"                             {
                                return(';');
                                }

"{"                             {
                                return('{');
                                }

"}"                             {
                                return('}');
                                }

","                             {
                                return(',');
                                }

":"                             {
                                return(':');
                                }

"="                             {
                                return('=');
                                }

"("                             {
                                return('(');
                                }

")"                             {
                                return(')');
                                }

"["                             {
                                return('[');
                                }

"]"                             {
                                return(']');
                                }

"."                             {
                                return('.');
                                }

"&"                             {
                                return('&');
                                }

"!"                             {
                                return('!');
                                }

"~"                             {
                                return('~');
                                }

"-"                             {
                                return('-');
                                }

"+"                             {
                                return('+');
                                }

"*"                             {
                                return('*');
                                }

"/"                             {
                                return('/');
                                }

"%"                             {
                                return('%');
                                }

"<<"                            {
                                return('<');
                                }

">>"                            {
                                return('>');
                                }

"^"                             {
                                return('^');
                                }

"|"                             {
                                return('|');
                                }

"?"                             {
                                return('?');
                                }

.                              {
                                //return(yytext[0]);
                               }                    /* ignore all the rest */

%%
