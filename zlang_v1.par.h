#include <phorward.h>

#define MALLOC_STEP 10

char * strbuf = NULL;

/* Append character to current string */
static void strbuf_create()
{
    strbuf = (char*)pmalloc( ( MALLOC_STEP + 2 ) * sizeof( char ) );

    strbuf[0] = '\0';
    strbuf[1] = '\0';
    strbuf[2] = '\0';
}

/* Append character to current string */
static void strbuf_append_ch(char ch )
{
    int len = pstrlen( strbuf );

    if( len % MALLOC_STEP == 0 )
        strbuf = (char*)prealloc( (char*)strbuf, ( len + MALLOC_STEP + 2 )
            * sizeof( char ) );

    strbuf[len] = ch;
    strbuf[len+1] = '\0';
    strbuf[len+2] = '\0';
}

/* Append string to current string */
static void strbuf_append_str(char * str)
{
    int len = pstrlen( str );
    for (int i = 0; i < len; i++) strbuf_append_ch(str[i]);
}

inline static void emit_vdecl(char * v1, char * v2) {
  printf("%s %s; // VARIABLE type = [%s]  name = [%s]\n", v1, v2, v1, v2);
}