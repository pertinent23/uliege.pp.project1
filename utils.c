/**
 * utils.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: HEUBA BATOMEN Franck Duval S227629
 * @date: 
 * @projet: INFO0030 Projet 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#include "utils.h"

NOMBRE_MAGIQUE str_vers_nombre_magique(char *nombre_magique)
{
    if ( nombre_magique != NULL )
    {
        if (strcmp(nombre_magique, "P1") == 0)
        {
            return P1;
        }
        else if (strcmp(nombre_magique, "P2") == 0)
        {
            return P2;
        }
        else if (strcmp(nombre_magique, "P3") == 0)
        {
            return P3;
        }
    }
    return NOMBRE_MAGIQUE_INCONNU;
}

TYPE_FICHIER str_vers_type_fichier(char *file_name)
{
    if (file_name != NULL && strlen(file_name) > 4)
    {
        char extension[5];
        int length = strlen(file_name), i = length - 4, j = 0;
        for(; i<length; i++)
            extension[j++] = file_name[i];
        extension[j] = '\0';

        if (strcmp(extension, "pbm") == 0)
        {
            return PBM;
        }
        else if (strcmp(extension, "pgm") == 0)
        {
            return PGM;
        }
        else if (strcmp(extension, "ppm") == 0)
        {
            return PPM;
        }
    }
    return TYPE_INCONNU;
}

TYPE_FICHIER format_vers_type_fichier(char *format)
{
    if (format != NULL)
    {
        if (strcmp(format, "PBM") == 0)
        {
            return PBM;
        }
        else if (strcmp(format, "PGM") == 0)
        {
            return PGM;
        }
        else if (strcmp(format, "PPM") == 0)
        {
            return PPM;
        }
    }
    return TYPE_INCONNU;
}

char *nombre_magique_vers_str(NOMBRE_MAGIQUE nb)
{
    switch (nb)
    {
        case P1:
            return "P1";
        
        case P2:
            return "P2";
        
        case P3:
            return "P3";

        default:
            return "";
    }
}

unsigned int nombre_de_chiffre(int nb)
{
    unsigned int result = 1;

    while (nb >= 10)
    {
        nb /= 10;
        result++;
    }
    
    return result;
}