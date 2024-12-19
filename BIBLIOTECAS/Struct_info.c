#include <stdlib.h>
#include "Struct_info.h"


void liberar_INFO(INFO *info)
{
    free(info->nome);
    free(info);
}