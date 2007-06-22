%{

  /* =====[ PCALC.C ]=========================================================

     Description: Programmers calculator.

     Revisions:

     REV     DATE     BY           DESCRIPTION
     ----  --------  ----------    --------------------------------------
     0.00  xx.xx.94  Peter Glen    Initial version.
     0.00  08/28/98  Peter Glen    Command line rework
     0.00  08/28/98  Peter Glen    Date added.
     0.00  08/21/98  Peter Glen    Unix port.

     ======================================================================= */

  /* -------- System includes:  -------------------------------------------- */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>                           
#include <signal.h>
#include <setjmp.h>

#include "hocdecl.h"             /* data declarations, function prototypes */
#include "symbol.h"
#include "help.h"
#include "store.h"
#include "print.h"

  int     fSilent = 0;

  extern  FILE * yyin ;


  %}

%union {                                           /* stack object type    */
    int     intval ;                               /* actual value         */
    long    lngval ;                               /* actual value         */
    double  val ;                                  /* actual value         */
    Symbol  *sym ;                                 /* symbol table ptr     */
}

%token  <val>   NUMBER
%token  <sym>   VAR BUILTIN IBUILTIN  UNDEF STR
%token  <sym>   TO FROM STORE RESTORE STRVAR

%type   <val>   expr
%type   <val>   asgn
%type   <sym>   junk
%type   <sym>   str

%right  '='
%left   '|' '&'
%left   '+' '-'
%left   '*' '/'
%left   UNARYMINUS
%right  '^'                                             /*  exponentiation */

%%

list:
        |   list
        |   list asgn
        |   list junk
        |   list expr               {
                                    print_num($2);
                                    }
        |   list STORE VAR          {
                                    store("pcalc.var", $3->name, $3->u.val);
                                    }
        |   list STORE VAR TO STR   {
                                    store($5->name, $3->name, $3->u.val);
                                    }
        |   list RESTORE VAR        {
                                    restore("pcalc.var",
                                            $3->name, &($3->u.val));
                                    }
        |   list RESTORE VAR FROM STR  {
                                    restore($5->name,
                                            $3->name, &($3->u.val));
                                    }
        |   list error              { yyerrok ; }
        ;


junk:       IBUILTIN str            { (*($1->u.iptr))($2->u.str) ; }
        |   IBUILTIN                { }
        |   IBUILTIN VAR            { (*($1->u.iptr))($2->u.val) ; }
        |   IBUILTIN expr           { (*($1->u.iptr))($2) ;       }
        |   STR                     { printf("%s", $1->name);}
        |   STRVAR                  { printf("%s", $1->u.str);}
        ;

asgn:   VAR '=' expr                { $$ = $1->u.val = $3 ; $1->type = VAR ; }
        | STRVAR '=' STR            { $1->u.str = $3->name; $1->type = STRVAR ;}
        ;


expr:       NUMBER
        |   VAR                     { $$ = $1->u.val }
        |   BUILTIN '(' expr ')'    { $$ = (*($1->u.ptr))($3) ; }
        |   BUILTIN   expr          { $$ = (*($1->u.ptr))($2) ; }
        |   expr '|' expr           { $$ = (long)$1 | (long)$3 ;}
        |   expr '&' expr           { $$ = (long)$1 & (long)$3 ;}
        |   expr '+' expr           { $$ = $1 + $3 ; }
        |   expr '-' expr           { $$ = $1 - $3 ; }
        |   expr '*' expr           { $$ = $1 * $3 ; }
        |   expr '/' expr           {
                                    if ($3 == 0.0)
                                    execerror("division by zero", "") ;
                                    $$ = $1 / $3 ;
                                    }
        |   expr '^' expr           { $$ = Pow( $1, $3) ; }
        |   '(' expr ')'            { $$ = $2 ; }
        |   '-' expr  %prec UNARYMINUS { $$ = -$2 ; }
        ;

str:     STR                    { }
        |STRVAR                 { }
        ;


%%

char *progname ;
int lineno = 1;
jmp_buf begin ;

/*-------------------------------------------------------------------------
**  MAIN     (pcalc.y)
*/

int     (*ptr_getchar)();
int     (*ptr_ungetc)();

FILE    *in_fp = NULL;

int     len;
char    buff[512];

FILE    *in_fp;

int     main(int argc, char *argv[])

{
    int     comm = 0, args;
    char    *env;

    args = parse_comline(argc, argv);

    progname = argv[0];

    if(!argv[1])
        {
        printf ("\nProgrammer's calculator by Peter Glen. Version 1.0\n\n");
        help_help();
        exit(0);
        }
    if(*argv[1] == 'f' && argv[1][1] == '\0')
        {
        funchelp();  exit(0);
        }
    if(*argv[1] == 'l' && argv[1][1] == '\0')
        {
        cbhelp();   exit(0);
        }
    if(*argv[1] == 'o' && argv[1][1] == '\0')
        {
        ophelp();   exit(0);
        }
    if(*argv[1] == 'c'&& argv[1][1] == '\0')
        {
        conshelp();   exit(0);
        }

    if(*argv[1] == '@' )
        {
        // we got file:

        yyin = fopen(&argv[1][1], "rt");
        if(!yyin)
            {
            printf("Cannot find file.\n");
            exit(0);
            }
        }
    else
        {
        // we got command line, write to a file, fake file:

        char    *commandline;
        int     len, cnt;

        for(cnt = args+1; cnt < argc; cnt++)
            {
            strcat(buff, argv[cnt]); strcat(buff, " ");
            }

        //printf("CMDLINE='%s'\n", buff);

        len = strlen(buff);
        yyin = fopen("pcalc.tmp", "w");

        if(!yyin)
            {
            execerror( "cannot create tmp file\n", NULL); exit(0);
            }
        fwrite(buff, len, 1, yyin);
        fputc('\n', yyin);
	//fputc(0x1a,  yyin);
        fclose(yyin);

        yyin = fopen("pcalc.tmp", "r");
        comm = 1;
        }

    init_sym() ;
    setjmp(begin) ;
    signal( SIGFPE, fpecatch) ;                /* Turbo-C uses "ssignal()" */
    yyparse() ;

    if(yyin)
        fclose(yyin);

    if(comm)
        unlink("pcalc.tmp");

    return 0 ;
}


/*-------------------------------------------------------------------------
**  EXECERROR
*/
void    execerror( char *s, char *t)
{
    warning( s, t) ;
    longjmp( begin, 0) ;
}

/*-------------------------------------------------------------------------
**  FPECATCH
*/
void    fpecatch( int aa)
{
    execerror("floating point exception", (char *) 0) ;
}

/*-------------------------------------------------------------------------
**  YYERROR
*/
void    yyerror( char *s)                      /* called by yacc syntax error */
{
    warning( s, (char *) 0) ;
    exit(0);
}

/*-------------------------------------------------------------------------
**  WARNING
*/

void    warning( char *s, char *t)
{
    fprintf( stderr, "%s: %s", progname, s) ;

    //fprintf( stderr, "pcalc WARNING: %s", s) ;

    if (t)
        fprintf( stderr, " %s", t) ;

    fprintf( stderr, " near line %d\n", lineno) ;
}

/*-------------------------------------------------------------------------*/


int     parse_comline(int argc, char *argv[])

{
    int i, j = 0;
    char *ptr;

    for(i=1; i < argc; ++i)
        {
        if (*argv[i] == '-')
            {
            switch(argv[i][1])
                {
                case 'S' :          /* quiet mode */
                case 's' :
                    fSilent = 1;
                    j++;
                    break;

                case 'B' :
                case 'b' :
                    fSilent = 1;
                    j++;
                    break;

                case 'v' :
                    printf (
                "\nProgrammer's calculator by Peter Glen. Version 1.0\n");
                    exit(0);
                    break;

                default:
                    // break on first non switch entry:
                    break;
                }
            }
        }
    return(j);
}

/* EOF */
