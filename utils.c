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

        if (strcmp(extension, ".pbm") == 0)
        {
            return PBM;
        }
        else if (strcmp(extension, ".pgm") == 0)
        {
            return PGM;
        }
        else if (strcmp(extension, ".ppm") == 0)
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

unsigned int decoupe(char *str, int debut, int *tableau, int nb_caractere)
{
    int i = debut, j = 0, length = strlen(str);
    int pixel = 0, pixel_trouve = 0;
    char pixel_value[2];

    pixel_value[1] = '\0';
    while (i < nb_caractere && j < length)
    {

        if (str[j] && strchr("0123456789 \n\t", str[j]) == NULL)
            return 0;

        if (str[j] != ' ' && str[j] != '\n')
        {
            pixel_value[0] = str[j];
            pixel *= 10;
            pixel += atoi(pixel_value);
            pixel_trouve = 1;
        }
        else if (pixel_trouve)
        {
            tableau[i++] = pixel;
            pixel = 0;
            pixel_trouve = 0;
        }
        j++;
    }

    if (pixel_trouve)
    {
        tableau[i++] = pixel;
        pixel = 0;
        pixel_trouve = 0;
    }
    
    return i;
}

void saute_commentaire(FILE *fichier)
{
    char tmp;
    while (fscanf(fichier, "#%*[^\n]%c", &tmp) == 1);
}

char *creer_ligne(int nb_colones, int taille_max_pixel, int taille_pixel, int *longueur_ligne)
{
    unsigned int longueur = 0;
    char *ligne;

    /**
     * @brief 
     * la longueur maximale d'un ligne est égale au nombre de chiffres de la 
     * valeur d'un pixel fois le nombre de colones de l'image, plus le nombre
     * de caractères d'espacement de la ligne (nombre de colones - 1) plus 1
     * (pour le symbol de fin des chaines de caractères)
    */

    longueur = nb_colones*nombre_de_chiffre(taille_max_pixel) + nb_colones;
    longueur *= taille_pixel;
    longueur += 2;
    ligne = (char *) malloc(sizeof(char)*longueur);
    
    if (longueur_ligne != NULL)
        *longueur_ligne = longueur;

    if (ligne != NULL)
        return ligne;
    
    return NULL;
}

int taille_pixel(NOMBRE_MAGIQUE num)
{
    if (num == P3)
        return 3;
    return 1;
}