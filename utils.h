/**
 * utils.h
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: HEUBA BATOMEN Franck Duval S227629
 * @date: 
 * @projet: INFO0030 Projet 1
*/

#ifndef __UTILS__
#define __UTILS__

/*
 * Déclaration du type TYPE_FICHIER
*/
typedef enum{
    TYPE_INCONNU = 27, PBM, PGM, PPM  
} TYPE_FICHIER;

/*
 * Déclaration du type NOMBRE_MAGIQUE
*/
typedef enum{
    NOMBRE_MAGIQUE_INCONNU = 1, P1, P2, P3
} NOMBRE_MAGIQUE;


/**
 * @brief 
 * retourne le nombre magique à partir de sa valeur
 * en chaine de caractère. 
 * 
 * @param nombre_magique 
 * @return NOMBRE_MAGIQUE 
*/
NOMBRE_MAGIQUE str_vers_nombre_magique(char *nombre_magique);

/**
 * @brief 
 * retourne le type de fichier à partir de son nom
 * si le type de fichier n'est pas identifié, la fonction
 * 
 * @param file_name 
 * @return TYPE_FICHIER 
*/
TYPE_FICHIER str_vers_type_fichier(char *file_name);

/**
 * @brief 
 * retourne le type de fichier à partir de son format
 * si le type de fichier n'est pas identifié, la fonction
 * 
 * @param file_name 
 * @return TYPE_FICHIER 
*/
TYPE_FICHIER format_vers_type_fichier(char *format);


/**
 * @brief 
 * Retourne le nombre magique sous la forme
 * de chaine de caractère
 * 
 * @param nb 
 * @return char* 
*/
char *nombre_magique_vers_str(NOMBRE_MAGIQUE nb);


/**
 * @brief 
 * retourne le nombre de chiffre d'un nombre
 * 
 * @param nb 
 * @return unsigned int 
 */
unsigned int nombre_de_chiffre(int nb);

/**
 * @brief 
 * cette fonction va chercher tous les entiers dans une chaine
 * de caractère et les socker dans un tableau
 * 
 * @param str 
 * @param tableau 
 * @param nb_caractere 
 * @return unsigned int 
*/
unsigned int decoupe(char *str, int *tableau, int nb_caractere);


#endif // 