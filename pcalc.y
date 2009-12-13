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
#include <unistd.h>

#include "hocdecl.h"             /* data declarations, function prototypes */
#include "symbol.h"
#include "help.h"
#include "store.h"
#include "print.h"

  int     fNibble = 0;
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
%left   '|'
%left   '&'
%left   '<' '>'
%left   '+' '-'
%left   '*' '/' '%'
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
        |   '~' expr                { $$ = ~((long)$2) ; }
        |   expr '|' expr           { $$ = (long)$1 | (long)$3 ;}
        |   expr '&' expr           { $$ = (long)$1 & (long)$3 ;}
        |   expr 'X' expr           { $$ = (long)$1 ^ (long)$3 ;}
        |   expr '<' expr           { $$ = (long)$1 << (long)$3 ; }
        |   expr '>' expr           { $$ = (long)$1 >> (long)$3 ; }
        |   expr '+' expr           { $$ = $1 + $3 ; }
        |   expr '-' expr           { $$ = $1 - $3 ; }
        |   expr '*' expr           { $$ = $1 * $3 ; }
        |   expr '/' expr           {
                                    if ($3 == 0.0)
                                    execerror("division by zero", "") ;
                                    $$ = $1 / $3 ;
                                    }
        |   expr '%' expr           { $$ = (long)$1 % (long)$3 ; }
        |   expr '^' expr           { $$ = Pow( $1, $3) ; }
        |   '(' expr ')'            { $$ = $2 ; }
        |   '-' expr  %prec UNARYMINUS { $$ = -$2 ; }
        ;

str:     STR                    { }
        |STRVAR                 { }
        ;


%%

int parse_comline(int argc, char *argv[]);

char *progname ;
int lineno = 1;
jmp_buf begin ;

/*-------------------------------------------------------------------------
**  MAIN     (pcalc.y)
*/

int     (*ptr_getchar)();
int     (*ptr_ungetc)();

int     main(int argc, char *argv[])

{
    int     args;
    char    template_local[] = "pcalc.tmp.XXXXXX",
            template_global[] = "/tmp/pcalc.tmp.XXXXXX",
            *template = NULL;

    args = parse_comline(argc, argv);

    progname = argv[0];

    if(!argv[1])
        {
        printf ("\nProgrammer's calculator by Peter Glen. Version " VERSION "\n\n");
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
            fprintf(stderr, "Cannot find file.\n");
            exit(0);
            }
        }
    else
        {
        // we got command line, write to a file, fake file:

        int     cnt;
        int     tmpfile;

        template = template_local;
        tmpfile = mkstemp(template);

        if(tmpfile == -1)
            {
            template = template_global;
            tmpfile = mkstemp(template);
            if(tmpfile == -1)
                {
                fprintf(stderr, "cannot create tmp file\n"); exit(0);
                }
            }
        /* XXX: hack! unlink here because if parsing fails, flex will
         * exit and we won't be able to unlink the file below */
        unlink(template);

        yyin = fdopen(tmpfile, "r+");

        for(cnt = args+1; cnt < argc; cnt++)
            fprintf(yyin, "%s ", argv[cnt]);
        fprintf(yyin, "\n");
        //write(tmpfile, "\x1a", 1);
        rewind(yyin);
        }

    init_sym() ;
    setjmp(begin) ;
    signal( SIGFPE, fpecatch) ;                /* Turbo-C uses "ssignal()" */
    yyparse() ;

    if(yyin)
        {
        if (template)
            unlink(template); /* unlink before we close to avoid race */
        fclose(yyin); /* this closes tmpfile too */
        }

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

    for(i=1; i < argc; ++i)
        {
        if (*argv[i] == '-')
            {
            switch(argv[i][1])
                {
                case 'h' :
                    printf (
                "\nProgrammer's calculator by Peter Glen.\n\n"
                "Usage: pcalc <stuff to calculate>\n"
                "       pcalc @script\n"
                "\nOptions:\n"
                "  -n      nibble mode (space out binary display)\n"
                "  -s,-S   silent mode\n"
                "  -b,-B   silent mode\n"
                "  -v      version\n"
                "  -h      help\n"
                "\nFor more info, run pcalc without any options, or see the README.\n\n");

                case 'n' :          /* nibble mode */
                    fNibble = 1;
                    j++;
                    break;

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
                    puts("Programmer's calculator by Peter Glen. Version " VERSION);
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
