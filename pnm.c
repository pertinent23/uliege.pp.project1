/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: HEUBA BATOMEN Franck Duval S227629
 * @date: 
 * @projet: INFO0030 Projet 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"
#include "pnm.h"


/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {

   /* Insérez ici les champs de la structure PNM */
   int nb_colones;
   int nb_lignes;
   int **matrice;
   TYPE_FICHIER type;
   NOMBRE_MAGIQUE nombre_magique;
};


/**
 * @brief 
 * Va créer un objet PNM_t puis le mettre en mémoire
 * et le retourner
 * 
 * @return struct PNM_t 
*/
static struct PNM_t *construit() 
{
   struct PNM_t *image;

   image = (struct PNM_t *) malloc(sizeof(struct PNM_t));

   if (image == NULL)
      return NULL;
   
   return image;
}


/**
 * @brief
 * va initialiser la matrice de l'objet PNM_t 
 * si elle existe déjà rien ne va se passer
 * 
 * retourne 0 si tout c'est bien passé et 1 dans 
 * le cas contraire
 * 
 * @param nb_lignes 
 * @param nb_colones 
*/
static int initialise(struct PNM_t *image, int lignes, int colones)
{
   assert(lignes > 0 && colones > 0);

   if (image->matrice == NULL)
   {
      image->matrice = (int **) malloc(sizeof(int *) * lignes);

      if (image->matrice == NULL) 
      {
         free(image);
         return 1;
      }

      int i = 0;

      for(; i<lignes; i++)
      {
         image->matrice[i] = (int *) malloc(sizeof(int) * colones);
         if (image->matrice[i] == NULL)
         {
            for(; i>=0; i--)
               free(image->matrice[i]);
            free(image);
            return 1;
         }
      }

      image->nb_lignes = lignes;
      image->nb_colones = colones;
   }
   return 0;
}

/**
 * @brief 
 * Cette fonction permet de dédruire 
 * un objet crée
 * 
 * @param image 
*/
static void detruit(struct PNM_t *image) 
{
   assert(image != NULL && image->nb_lignes > 0 && image->nb_colones > 0);
   int i = 0;

   if (image->matrice != NULL)
   {
      for(; i<image->nb_lignes; i++)
      {
         if (image->matrice[i] != NULL)
            free(image->matrice[i]);
      }
   }

   free(image);
}

int load_pnm(PNM **image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fichier = fopen(filename, "r");

   if (fichier != NULL)
   {
      *image = construit();

      if (image == NULL)
      {
         fclose(fichier);
         return -1;
      }

      fclose(fichier);
   }

   /* Insérez le code ici */

   return -2;
}

int write_pnm(PNM *image, char* filename) {

   detruit(image);
   return 0;
}

