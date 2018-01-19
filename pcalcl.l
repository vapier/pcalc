%{

/*
**  pcalc LEX
*/

#include "ctype.h"
#include "string.h"

#include "debug.h"
#include "hocdecl.h"
#include "symbol.h"
#include "pcalc.h"
#include "convert.h"

/* avoid fwrite() gcc warning */
#define fwrite(ptr, size, num, fp) ({ ssize_t s = fwrite(ptr, size, num, fp); s; })

extern YYSTYPE yylval;
extern  int lineno;

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

0[xX][0-9a-fA-F]+([0-9a-fA-F_]*[0-9a-fA-F]+)? {
                                debug(" Hexadec: [ %s ]\n", yytext);

                                yylval.val = (double) hextoll(yytext + 2);

                                return(NUMBER);
                                }

0[by][01]+([01_]*[01]+)?        {
                                debug(" Binary:  [ %s ]\n", yytext);

                                yylval.val = bintol(yytext + 2);

                                return(NUMBER);
                                }

0([oc]?[0-7]+)?([0-7_]*[0-7]+)? {
                                debug(" Octal:   [ %s ]\n", yytext);

                                yylval.val = otol(yytext + 1 + (yytext[1] == 'c' || yytext[1] == 'o' ? 1 : 0));

                                return(NUMBER);
                                }

[0-9]+([0-9_,]*[0-9]+)?         {
                                debug(" Decimal: [ %s ]\n", yytext);

                                yylval.val = (double) dtoll(yytext);

                                return(NUMBER);
                                }

"."[0-9]+ |
[0-9]+"."[0-9]* |
[0-9]+[dDeE][+-]?[0-9]+ |
[0-9]+"."[0-9]*[dDeE][+-]?[0-9]+ |
"."[0-9]+[dDeE][+-]?[0-9]+     {
                                debug(" Decimal: [ %s ]\n", yytext);

                                yylval.val = (double) atof(yytext);

                                return(NUMBER);
                                }

\".*\"                          {
                                Symbol *sp;

                                debug(" string: [ %s ]\n", yytext);

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
                                debug(" Comment: [ %s ]\n", yytext);

                                //return(COMM);
                                }

[a-zA-Z_]+[a-zA-Z0-9_]*         {
                                Symbol *sp;

                                debug(" Ident:   [ %s ]\n", yytext);

                                sp  = lookup_sym(yytext);

                                if(sp)
                                    {
                                    yylval.sym = sp;

                                    if(sp->type == BUILTIN)
                                        {
                                        debug("Bultin: %s\n", sp->name);

                                        return(BUILTIN);
                                        }
                                    else if(sp->type == IBUILTIN)
                                        {
                                        debug("Bultin: %s\n", sp->name);

                                        return(IBUILTIN);
                                        }
                                    else if(sp->type == VAR)
                                        {
                                        debug("Var: %s\n", sp->name);

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

                                debug(" Stringvar: [ %s ]\n", yytext);

                                return(STRVAR);
                                }

[\r]                            {
                                debug(" Comment: [ %s ]\n", yytext);

                                lineno++;
                                //return(COMM);
                                }

[\n]                            {   }

[ \t]+                          {
                                //debug(" White:   [ %s ]\n", yytext);

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
