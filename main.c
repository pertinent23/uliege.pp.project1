/**
 * main.c
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
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>

#include "pnm.h"
#include "utils.h"

/**
 * @brief 
 * cette fonction va gérer les arguments et retourner au code appellant
 * ce dont il a besoin
 * 
 * elle retourne 0 s'il ny a pas d'erreur et 1 dans le cas contraire
 * 
 * @param argc 
 * @param argv 
 * @param optstring 
 * @param entree 
 * @param sortie 
 * @param format 
 * @return int 
*/
static int gestionnaire(int argc, char *argv[], char *optstring, char **entree, char **sortie, char **format)
{
   int opt, erreur = 0;
   int i = 0, f = 0, o = 0;

   while ((opt = getopt(argc, argv, optstring)) != -1)
   {
      switch (opt)
      {
         case 'i':
            *entree = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));
            i = 1;

            if (*entree != NULL)
               strcpy(*entree, optarg);
            else
               erreur = -3;

            break;
         
         case 'f':
            *format = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));
            f = 1;
            
            if (*format != NULL)
               strcpy(*format, optarg);
            else
               erreur = -3;

            break;
         
         case 'o':
            *sortie = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));
            o = 1;
            
            if (*sortie != NULL)
               strcpy(*sortie, optarg);
            else
               erreur = -3;

            break;
         
         case ':':
            erreur = -1;
            break;
         
         case '?':
            erreur = -2;
            break;

         default:
            erreur = -4;
            break;
      }
   }

   if (erreur)
   {
      if (*entree != NULL)
         free(*entree);
      
      if (*sortie != NULL)
         free(*sortie);
      
      if (*format != NULL)
         free(*format);
      
      if (erreur == -1)
         printf("\n>> Argument de paramètre manquant." );
      else if (erreur == -2)
         printf("\n>> Paramètre inconnu entrée." );
      else if (erreur == -3)
         printf("\n>> Problème de gestion des entrées/sorties/format peut-être dû à leur taille." );
      else 
         printf("\n>> Erreur inconnue." );
      
      return 1;
   }
   else if (!i && !o && !f)
   {
      printf("\n>> Aucun paramètres: -f -i -o" );
      return 1;
   }
   else if (!i)
   {
      printf("\n>> Paramètre obligatoire manquant: -i" );
      return 1;
   }
   else if (!o)
   {
      printf("\n>> Paramètre obligatoire manquant: -o" );
      return 1;
   }
   else if (!f)
   {
      printf("\n>> Paramètre obligatoire manquant: -f" );
      return 1;
   }

   return 0;
}

int main(int argc, char *argv[]) {

   char *optstring = ":f:i:o:";
   char *entree, *sortie, *format;
   TYPE_FICHIER t_entree, t_sortie, t_format;

   printf("\n\n---------------------------------------------------------");
   printf("\n>> Debut du traitement...");
   
   if (!gestionnaire(argc, argv, optstring, &entree, &sortie, &format)) 
   {
      t_entree = str_vers_type_fichier(entree); 
      t_sortie = str_vers_type_fichier(sortie);
      t_format = format_vers_type_fichier(format);

      if (t_format != t_entree || t_format != t_sortie)
      {
         printf("\n>> Le format ne correspond pas à l'extension du fichier.");
      }
      else if (t_entree != t_sortie)
      {
         printf("\n>> Le fichier d'entrée et sortie n'on pas le même format.");
      }
      else 
      {
         PNM *image;
         int result;

         if ((result = load_pnm(&image, entree)) == 0)
         {
            if((result = write_pnm(image, sortie)) != 0)
            {
               switch (result)
               {
                  case -1:
                     printf("\n>> Le nom du fichier en sortie est malformé.");
                     break;

                  case -2:
                     printf("\n>> L'image n'a pas pu ếtre sauvegardé.");
                     break;
               }
            }
            else
            {
               printf("\n>> Image `%s` parfaitement sauvergardé comme `%s`.", entree, sortie);
            }
         }
         else
         {
            switch (result)
            {
               case -1:
                  printf("\n>> Erreur d'allocation mémoire.");
                  break;
               
               case -2:
                  printf("\n>> Le nom du fichier en entrée est mal formé.");
                  break;
               
               case -3:
                  printf("\n>> Contenu du fichier mal formé.");
                  break;
            }
         }
      }
   }   

   printf("\n>> Fin du traitement...");
   printf("\n---------------------------------------------------------\n\n");

   return 0;
}

