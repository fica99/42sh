#include "parser.h"

void    alias_sub(t_lex_tkn **token)
{
    char *val;

    if (!g_aliases.vars)
        return ;
    if ((val = ft_getvar((*token)->value, g_aliases.vars)))
    {
        free((*token)->value);
        (*token)->value = ft_strdup(val);
    }
}
