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
#include <string.h>

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
   unsigned int maximun_pixel;
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
         image->matrice[i] = (int *) malloc(sizeof(int) * colones * taille_pixel(image->nombre_magique));
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
   int i = 0, j, result, longueur_ligne;
   char *ligne, nombre_magique[3];

   if (fichier != NULL)
   {
      *image = construit();

      if (image == NULL)
      {
         fclose(fichier);
         return -1;
      }

      /**
       * @brief 
       * permet de verifier que le nombre 
       * magique soit bien présent
      */

      if (fscanf(fichier, "%[P1-3]\n", nombre_magique) != 1 || ((*image)->nombre_magique = str_vers_nombre_magique(nombre_magique)) == NOMBRE_MAGIQUE_INCONNU)
      {
         fclose(fichier);
         return -3;
      }


      /**
       * @brief 
       * permet le filtrage des commentaires
       * dans le fichier 
      */
      saute_commentaire(fichier);


      /**
       * @brief 
       * ici on veut recupérer le nombre de lignes
       * et de colones dans le fichier
      */

      if (
         fscanf(fichier, "%d%*[^0-9]%d\n", &(*image)->nb_colones, &(*image)->nb_lignes) != 2 ||
         (*image)->nb_colones <= 0 ||
         (*image)->nb_lignes <= 0 
      )
      {
         fclose(fichier);
         return -3;
      }

      if ((*image)->nombre_magique != P1)
      {
         /**
          * @brief 
          * permet le filtrage des commentaires
          * dans le fichier 
         */
         saute_commentaire(fichier);

         /**
          * @brief 
          * ici on veut récupérer la taille maximale
          * d'un pixel
         */

         if (
            fscanf(fichier, "%u\n", &(*image)->maximun_pixel) != 1 ||
            ((*image)->nombre_magique == P2 && (*image)->maximun_pixel > MAXIMUN_POUR_PIXEL) ||
            ((*image)->nombre_magique == P3 && (*image)->maximun_pixel > MAXIMUM_POUR_COULEUR)
         ) 
         {
            fclose(fichier);
            return -3;
         }

      }
      else
         (*image)->maximun_pixel = 1; 

      
      (*image)->type = str_vers_type_fichier(filename);
      /**
       * @brief 
       * ici nous verifions si les extensions de fichiers
       * correspondent à leur nombre magique 
      */
      switch ((*image)->nombre_magique)
      {
         case P1:
            if ((*image)->type != PBM)
            {
               fclose(fichier);
               return -2;
            }
            break;
         
         case P2:
            if ((*image)->type != PGM)
            {
               fclose(fichier);
               return -2;
            }
            break;
         
         case P3:
            if ((*image)->type != PPM)
            {
               fclose(fichier);
               return -2;
            }
            break;
         
         case NOMBRE_MAGIQUE_INCONNU:
            break;
      }

      /**
       * @brief 
       * ici nous créons la matrice qui va contenir tous les
       * pixels de l'image 
      */
      if (initialise(*image, (*image)->nb_lignes, (*image)->nb_colones))
      {
         fclose(fichier);
         return -1;
      }

      ligne = creer_ligne(
         (*image)->nb_colones, 
         (*image)->maximun_pixel, 
         taille_pixel((*image)->nombre_magique), 
         &longueur_ligne
      );

      if (ligne == NULL)
      {
         fclose(fichier);
         detruit(*image);
         return -1;
      }

      i = j = 0;
      while (i < (*image)->nb_lignes)
      {
         /**
          * @brief 
          * permet le filtrage des commentaires
          * dans le fichier 
         */
         saute_commentaire(fichier);
         
         /**
          * @brief Construct a new if object
          * ici on va lire une ligne, vérifier si ce n'est
          * pas la fin du fichier et decouper cette ligne
          * pour l'intégrer dans notre matrice 
         */

         if (
            fgets(ligne, longueur_ligne, fichier) == NULL || 
            (result = decoupe(ligne, j, (*image)->matrice[i], (*image)->nb_colones*taille_pixel((*image)->nombre_magique))) == 0
         )
         {
            free(ligne);
            fclose(fichier);
            detruit(*image);
            return -3;
         }

         j += result - j;

         if (j >= (*image)->nb_colones*taille_pixel((*image)->nombre_magique))
         {
            j = 0;
            i++;
         }
      }

      free(ligne);
      fclose(fichier);
      return 0;
   }

   return -2;
}

int write_pnm(PNM *image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fichier;
   char *ligne, pixel[7];
   const char *invalide = "/\\:*?\"<>|";
   int i = 0, j, length = (int) strlen(filename);

   while (i<length)
   {
      if (strchr(invalide, filename[i]) != NULL)
         return -1;
      i++;
   }
   
   fichier = fopen(filename, "w");

   if (image == NULL)
      return -2;

   fprintf(fichier, "%s\n", nombre_magique_vers_str(image->nombre_magique));
   fprintf(fichier, "%d %d\n", image->nb_colones, image->nb_lignes);

   if (image->nombre_magique != P1)
      fprintf(fichier, "%u\n", image->maximun_pixel);

   ligne = creer_ligne( 
      image->nb_colones, 
      image->maximun_pixel, 
      taille_pixel(image->nombre_magique), 
      NULL
   );

   if (ligne == NULL)
   {
      fclose(fichier);
      remove(filename);
      return -2;
   }

   i = 0;

   for(; i<image->nb_lignes; i++)
   {
      j = 0;
      ligne[0] = '\0';

      for(; j<image->nb_colones*taille_pixel(image->nombre_magique); j++)
      {
         sprintf(pixel, "%d", image->matrice[i][j]);
         strcat(ligne, pixel);
         strcat(ligne, " ");
      }

      fprintf(fichier, "%s\n", ligne);
   }

   free(ligne);
   fclose(fichier);
   detruit(image);

   return 0;
}

