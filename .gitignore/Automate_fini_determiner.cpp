#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <ctype.h>

//***********************************Important****************************************

//   . inique que il a la suite      ; indique fin de déclaration

//************************************************************************************


int  nb_ligne;                       // nb_ligne : nombre ligne de la matrice e transition
int  nb_colone;                      // nb colone : nombre colone de la table transition
int  nb_caractere;                   // nb _carcatere nombre caractere de la chaine à analyser
int  nb_etat_final;                  // nb_etat_inal : nombre etat final 
char char_fichier;                  // caractère du fichier lue 

int delta[20000][20000];             // Table de transition
char alphabet[200000000];            // table Alphabet de utilisateur
int chaine_w_codifier[20000000];     // table chaine codifier 
int F[20000000];                     // Ensemble etat final


// Structure chaine w c-a-d juste pour avoir une chaine dynamique 

struct chaine_w
{
  char caractere;
  struct chaine_w *ptr;
};


// define un nouveau type qui chaine qui a sructure chaine_w

typedef struct chaine_w chaine;


// Automate etat fini determiner 
void automate(int chaine_w_codifier[200000000], int delta[20000][20000], int
  F[20000000], int nb_caractere, int nb_etat_final)
{

  int etat = 0;  // etat q0 initiale
  int indice;
  bool reponse;  // varibale utiliser pour tester si etat retourner par la matrice  transiiton aappartient 

  for (indice = 0; indice < nb_caractere; indice++)
  {
              
    if (chaine_w_codifier[indice] !=  - 1 && chaine_w_codifier[indice] !=  - 2
      && etat !=  - 1)                               // -1 indique fin de la chaine   -2 indique caractère n'appartient pas alphabet  etat== - 1  etat puie
    {
      etat = delta[etat][chaine_w_codifier[indice]]; // nouveau etat 
    } 
    else
    {
      break;                                         // sortire boucle si une des trois est ausse 
    }
  }

  if (chaine_w_codifier[indice] ==  - 2 && etat ==  - 1) // cas etat puie et carcatère qui n'existe pas dans alphabet 
   {
    printf("\n resultat  : Chaine incorrect");
  }

  else
  {
    for (indice = 0; indice < nb_etat_final; indice++)
    {
      if (etat == F[indice]) // etat matrice transition appartient à la ensemble etat finaux
      {
        reponse = true;
        break;               // sort lorque au moins on trouve un 1 element qui appartient  
      }
      else
      {
        reponse = false;
      }
    }
  }
  if (reponse)
  {
    printf("\n resultat  : Chaine correct");
  }
  else
  {
    printf("\n resultat  : Chaine incorrect");
  }

}

// lire carcatère alphabet dans fichier et les afficher dans la console 
int read_Show_alphab_char(FILE *fichier)
{


  int nb_caractere_alph = 0;       //  nombre carcatere dans alpbaet 0 

  if (fichier != NULL)
  {
    char_fichier = getc(fichier); // 1 lecture pour entée dans la boucle
    while (char_fichier != ';')
    {
     // tanque on n'a pas arriver à la fin de la déclaration  
      if (!isspace(char_fichier))
      // carcatère lue et différent de espcae 
      {
        // inerer caractère lue à la table alphabet
        alphabet[nb_caractere_alph] = char_fichier;
       
       // affichage alphabet lue
	    printf("\t-%c", alphabet[nb_caractere_alph]);
       
        // augmenter carcatere alphabet suite a la lecture 1 catcatère du fichier 
	    nb_caractere_alph++;
       
      }
      char_fichier = getc(fichier); // lire caacatère suivant 

    }
    return nb_caractere_alph;

  }

}


// procedure lie matrice  transition dans fichier
void read_Show_matrix_trans(FILE *fichier, int nb_caractere_alph)
{

  int indice, indice1;
  indice = 0;
  indice1 = indice;
  char_fichier = getc(fichier); // lire caractère fichier

  char etat[1];   // element fichier lue sont des caractère  et -1 c'est 2 carcatère pour stocker   
  int etat_trans; // pour assurer bonne convetissement etat avec methode atoi() 
                 //afin de ne pas causer problem quand on va stocker dans matrice delta 

  printf("\n \n    Ma Matrice de transition et la suivante : \n \n");


  // partie decoration affichage  terminal de la matrie de transution qui represente les colones
  for (int i = 0; i < nb_caractere_alph; i++)
  {
    printf("         %c         ", alphabet[i]);
  }
  printf("\n");
  while (char_fichier != ';')      // fin element matrice transiiton
  {
    if (char_fichier != '.')       // passe  ligne suivant 
    {

      if (char_fichier == '-')
      {
        etat[0] = char_fichier;   //etat[0]= -    
        etat[1] = getc(fichier);  // etat[1]= 1
        etat_trans = atoi(etat);  // atoi convertie chaine etat en eniter  '-1' on reslutat -1
        
        delta[indice][indice1] = etat_trans; // stocke etat dans matrice  transition
        indice1++;
      }
      else
      {
        if (!isspace(char_fichier))
        {
          etat[0] = char_fichier;//etat[0]=carcatere
          etat[1] = ' ';//espcae car atoi accept chaine 
          etat_trans = atoi(etat);//convetire chaine etat en enter exemple etat="1 "   atoi()=> chiffre 1
          delta[indice][indice1] = etat_trans; // stocker dans table transition
          indice1++;
        }
      }
    }
    else
    {

      indice++; // passer ligne suivante
      indice1 = 0; // réinisialiser colone debut
    }
    char_fichier = getc(fichier); // lire caractère suivant
  }

  // Partie decoration pour affichage comprehensible
  for (int i = 0; i < indice; i++)
  {

    printf("\n %d ", i);
    for (int j = 0; j < indice1; j++)
    {

      printf("      %d           ", delta[i][j]);

    }

    printf("\n");
  }


}

// Lire etat final et les affichers
void read_Show_final_stat(FILE *fichier)
{

  char_fichier = getc(fichier); // lire caractère 

  int etat_final;               // nombre etat final

  char etat_f[1];               //ensemble etat finaux

  int indice = 0;
  nb_etat_final = 0;      
  printf("\n");
  printf("\n    Est en fin Mais etat finaux sont :");
  while (char_fichier != ';')          // caractère fichier lui 
  {
    if (!isspace(char_fichier))       // caractère lui différent espace
    {
      etat_f[0] = char_fichier;       // stocke  etat dans tab carcatère
      etat_final = atoi(etat_f);      // convertire en entier car etat_final tab entier 
      F[indice] = etat_final;
      printf("\t%d", F[indice]);    // affichage etat finaux
      nb_etat_final++;             
      indice++;
    }
    char_fichier = getc(fichier);   // lire cacatère suvant 
  }
  char_fichier = getc(fichier);    // avance dans le fichier 
}

// Lire et afficher chaine 
chaine *read_Show_chaine_w(FILE *fichier)
{


  chaine *w_chaine,  *ptr_carac_act,  *ptr_carac_suiv;
  // w_chaine tete de la chaine 
  // ptr_carac_act pointeur carcatère actuelle à inserer
  // ptr_carac_suiv contrure un nouveau maillon pour inser nouveau carcarère 

  w_chaine = (chaine*)malloc(sizeof(w_chaine));

  nb_caractere = 0; // compte nb carcatère lue afin de codifier 

  if (w_chaine != NULL) // malloc reussie
  {

    ptr_carac_act = w_chaine; // preserver la tete de la liste

    char_fichier = getc(fichier); // lire caractère

    while (char_fichier != ';')  // on a pas arriver à la fin du déclaration
    {

      ptr_carac_act->caractere = char_fichier; // inser carcatère lue dans la chaine
      nb_caractere++;                          // augmenter nb caractère lue
      ptr_carac_suiv = (chaine*)malloc(sizeof(ptr_carac_suiv));

      if (ptr_carac_suiv != NULL) // malloc reussie
      {

        ptr_carac_act->ptr = ptr_carac_suiv; // chainnage entre maillon actuelle et suivant 
        ptr_carac_act = ptr_carac_suiv;      // pointer ptr_carac_act vers maillon suivant 
        ptr_carac_act->ptr = NULL;           // pour indique fin de chaine 
      }
      char_fichier = getc(fichier);          // lire caractère suivant

    }

  }
  
  // Partie decoration affichage
  
  ptr_carac_act = w_chaine;
  printf("\n");
  printf("chaine a analyser :   ");
  while (ptr_carac_act->ptr != NULL)
  {
    printf("%c", ptr_carac_act->caractere);
    ptr_carac_act = ptr_carac_act->ptr;
  }

  return w_chaine; // retourner chaine a fin de la codifier
}


// codifier chaine_w retourner par methode read_Show_chaine_w
void chaine_codifie_string_w(FILE *fichier, chaine *w_chaine, int nb_caractere,
  int nb_caractere_alph)
{

  for (int indicei = 0; indicei < nb_caractere; indicei++)
  {
    for (int indicej = 0; indicej < nb_caractere_alph; indicej++)
    {

      if (w_chaine->caractere == alphabet[indicej]) // carcatère chaine dynamique exist dans alphabet
      {
        chaine_w_codifier[indicei] = indicej;       // affecter indice du caractère dans tableau alphabet à la chaine codifier
        goto out;                                  // sortir de la boucle pour aller caractère suivant
      }
      else
      {
        if ((indicej + 1) == nb_caractere_alph) // on parcourue tout le tableau alphbet et on rien trouver
        {
          chaine_w_codifier[indicei] =  - 2;   // caractère n'existe pas dans alphber
        }

      }

    }
    out: w_chaine = w_chaine->ptr;


  }

  chaine_w_codifier[nb_caractere] =  - 1; // indique fin de chaine

}


int main()
{

  // 1 ligne du fichier  représente  les caractère de l'alphabet 
  // 2 ligne Table de transiiton
  // 3 ligne Etat finaux 
  // 4 lchaine à analyser

  FILE *fichier = fopen("test.txt", "r");   // ouuvrire fichier mode lecture r 

  printf(
    "\n____________________________Bienvenue______________________________________\n");
  printf(
    "|                                                                         |");
  printf(
    "\n|                Je suis Automate etat fini determiner                    |\n");
  printf(
    "|_________________________________________________________________________|\n");
  printf("\n    Mon  Alphabet  est  :  ");


  int nb_caractere_alph;

  nb_caractere_alph = read_Show_alphab_char(fichier);       // lecture alphabet contenu dans fichier et retourner nombre carcatère alphabet lue
     
  read_Show_matrix_trans(fichier, nb_caractere_alph);      // lecure valeur matrice transition et affichage   
 
 
  read_Show_final_stat(fichier);                           // lire etat final


  chaine_w *w_chaine;

  w_chaine = read_Show_chaine_w(fichier);                // lire retouner chaine lue

  printf("\n");


  printf("\n");

  chaine_w_codifier[nb_caractere];

  chaine_codifie_string_w(fichier, w_chaine, nb_caractere, nb_caractere_alph); // codifier chaine chaine_w stocker dans chaine_w_codifier

  automate(chaine_w_codifier, delta, F, nb_caractere, nb_etat_final); // appelle procedure Automate pour verfier si la chaine correct

  return 0;
}
