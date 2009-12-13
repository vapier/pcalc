
/* =====[ store.c ]=========================================================

   Description:    Store varible for pcalc

   Revisions:

      REV     DATE     BY           DESCRIPTION
      ----  --------  ----------    --------------------------------------
      0.00  21/9/98   Peter Glen    Initial version.

   ======================================================================= */

/* -------- System includes:  -------------------------------------------- */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* -------- Includes:  --------------------------------------------------- */

#include "store.h"
#include "symbol.h"
#include "hocdecl.h"             /* data declarations, function prototypes */

/* -------- Implementation: ---------------------------------------------- */

static char    work_str[128];

int     store(char *file, char *name, double var)

{
    FILE    *fp  = NULL;
    int     found = FALSE;
    int     namelen;
    char    tmp[18];
    Symbol *ms = lookup_sym("DEBUG_STORE");

    if(ms && ms->u.val)
        printf("Storing: %s\n", name);

    strncpy(tmp, name, 16);                     // cutted local copy
    tmp[16] = '\0';
    namelen =  strlen(tmp);

    fp = fopen(file, "r+");

    if(!fp)
      {
	fp = fopen(file, "w+");
	if(ms && ms->u.val)
	  printf("Creating out file\n");
      }
    if(!fp)
      {
	if(ms && ms->u.val)
	  printf("Could not create file.\n");
	return(0);
      }

    *work_str = 0;
    
    while(TRUE)
        {
        long pos = ftell(fp);

	if(!fgets(work_str, sizeof(work_str), fp))
	  {
	  break;
	  }
	//printf("fgets got:  %s\n", work_str);
	
        if(*work_str == 0)
	  {
	    // printf("empty string\n");
	    break;
	  }
	if(!strncmp(work_str, tmp, namelen))
            {
            fseek(fp, pos, SEEK_SET);
            found = TRUE;
            break;
            }
        if(feof(fp))
	  break;
        if(ferror(fp))
            break;
        }
    sprintf(work_str, "%-16s = %-16e\n", tmp, var);
    fputs(work_str, fp);
    fclose(fp);
    return(1);
}


int     restore(char *file, char *name, double *var)

{
    FILE    *fp  = NULL;
    int     found = FALSE;
    int     namelen;
    char    tmp[18];

    Symbol *ms = lookup_sym("DEBUG_STORE");

    if(ms && ms->u.val )
        printf("Restoring: %s\n", name);

    strncpy(tmp, name, 16);                     // cutted local copy
    tmp[16] = '\0';
    namelen =  strlen(tmp);

    *var = 0.0;

    fp = fopen(file, "rt+");

    if(!fp)
        return(0);

    while(TRUE)
        {
	  if(!fgets(work_str, sizeof(work_str), fp))
	    break;
	  
	  if(!strncmp(work_str, tmp, namelen))
            {
	      found = TRUE;
	      break;
            }
	  if(feof(fp))
            break;
	  if(ferror(fp))
            break;
        }
    if(found)
      {
        float dd;
        sscanf(work_str, "%*s = %e", &dd);
        *var = dd;
      }
    fclose(fp);
    return(1);
}

/* EOF */


