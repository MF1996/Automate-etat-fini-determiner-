#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//********************************Partie structure ********************************

// Structure maillon pour elle utiliser afin que la chaine analyser soit dynamique
struct maillon {
    char alphaNum;
    struct maillon *ptr;
};

// Structure de maillon ou qui reprensente la codification de la chaine analyser
struct codif_maillon {
    int code;
    struct codif_maillon *ptr;
};


typedef struct maillon *Maillon;
typedef struct codif_maillon *cod_maillon;


//********************************************************************************





//***********************Partie déclaration GLOBAL ********************************


int ligne, colone;                   // Nombre Ligne colone matricr
int long_Alphab;                     // Longeur alphabet
int F[20000000];                     // ensemble etat final
int del[20000][20000];              // Table de transition
char alphabet[200000000];           // Alphabet de utilisateur
Maillon w_chaine, p, new_maill, save;
// w chaine tete de la chaine  new mail nouveau maillon
// ou sera stocker un nouveau cractère
// p pour assurer le chainage entre maillon dans
//le cas utilisateur insere des espace  les espcae sont prix en consideration
// car il peut inserer un autre caractère dans
// le cas contraire save contain addresse ou apés se  caractère donnée il que des espaces

cod_maillon chaine_codif, p1, s, elemine, saveDebElm, saveEnd_Elem;
// chaine codifi contient tete
// de la chaine codfifier p1 pour assurer le chainage ,
//  s  utiliser pour alloer un maillon ou sera stocker la codification du caractère
// elemine utiliser pour ne utiliser tete chaine codofoer et elle andique
//emplcement ou il faut elemeniner les espaces nnon sénificatife que
// a ajouter saveDebElm addresse ou va commncer
// elemination espace et saveEnd_Elem c'est la fin espace a faint de faire le chainage

int taille_w_chaine = 0; // Taille chaine  à analyser

int nb_etat_final;  // Nombre etat final


//***************************************************************************







// ***********************************Automate******************************************

void automate(cod_maillon w_codifier, int del[20000][20000], int F[200000000], int nb_etat_final) {


    bool reponse;
    int etat; // etat
    int enter = w_codifier->code;// 1 mot codifier
    if (enter == -2) {
        //1 carcatère de la chaine n'appatient pas aller etiqye pur affiche message incorrect
        goto printf;
    } else {
        etat = 0;
        while (enter != -1 && etat != -2) {

            // entre -1 fin de la chaine a analyser   etat -2 etat puie

            etat = del[etat][enter];


            w_codifier = w_codifier->ptr;

            enter = w_codifier->code;

            // enter -3 pour dire que il existe un espace exemle    za a  entre le a et a il un espce je l'est codifier en -3

            // ********* ENTER ***************   -2 caractère n'appartient pas a lalphbet de automate
            if (enter == -2 || enter == -3) {
                goto printf; //
            }

        }
    }

    for (int indice = 0; indice < nb_etat_final; indice++) {
        if (etat == F[indice] && etat != -2) {
            reponse = true;
            goto bon;
        } else {

            reponse = false;

        }
    }


    if (reponse == true) {

        bon:
        printf("Chaine Correct");

    } else {

        printf :
        printf("Chaine Incorrect");

    }
}

//************************************************************************************************

// Method alphabet lit elemnt alphabet
void lire_Alphabet() {
    printf("saisisser la  longeur de votre alphabet : ");

    scanf("%d", &long_Alphab);


    alphabet[long_Alphab];


    printf("\n");

    for (int taille = 0; taille < long_Alphab; taille++) {


        printf("donne alphabet: ");

        scanf("%s", &alphabet[taille]);
    }
}


// Methode final lie etat final
void lire_etat_final() {
    printf("Nombre etat final= ");

    scanf("%d", &nb_etat_final);


    F[nb_etat_final];

    // Lire etat finale

    for (int indx = 0; indx < nb_etat_final; indx++) {

        printf("F[%d]=", indx);

        scanf("%d", &F[indx]);
    }
    bool rep = true;
}


// Methode qui lie chaine a analyser
void lire_w() {

    printf("\n Saissiser la chaine a analyser :");


    taille_w_chaine = 0;

    char caractere = '\r'; // pour commence

    w_chaine = (Maillon) malloc(sizeof(w_chaine));

    if (w_chaine != NULL) { // si il espace memoire
        p = w_chaine;    // preserver la tete de la chaine

        caractere = getchar(); // lecture du carcartère tpaer

        if (caractere == '\n') {  // conditin arret de la lecture c-a-d utilisateur tape touche ENTRER

            repeter :                    // etiquette en revient  dans le cas que un utlisteur na pas inserer 1 posiiton des carcartère
            // mais que il tape juste la touche espace
            caractere = getchar(); // relecture se qui tape

            while (caractere != '\n') {
                if (!isspace(caractere)) { // dans le cas n'est pas espce
                    lire :
                    taille_w_chaine++;    // augmenter la taille de chaine

                    p->alphaNum = caractere; // inser cracatère dans le maillon


                    new_maill = (Maillon) malloc(sizeof(new_maill)); // contruit nouveau maillon pour autre carcartère

                    if (new_maill != NULL) {  // verification si a de espce

                        p->ptr = new_maill;      // chainge
                        p = new_maill;          // p 1 pointe ver tete mtn pointe vers new maillon
                        new_maill->ptr = NULL;  // new maill ptr NULL fin de la chaine
                    }
                    caractere = getchar();    // lire
                } else {
                    if (taille_w_chaine >
                        0) {// si taille >0 dans ce que j'es lue c'est pas espace mais de caractère dans je revient a la lecure
                        goto lire;
                    } else {
                        goto repeter;  // utilisateur a taper des espcae comme 1 caracrtère igoner et repter la lecture
                    }

                }
            }
        }

    }
}


// codifier de la chaine donnée par utilisateurs
void codifier_w() {
    int indice;

    chaine_codif = (cod_maillon) malloc(sizeof(chaine_codif));//tete codofication
    p1 = chaine_codif;
    s = p1;

    while (w_chaine->ptr != NULL) {

        for (indice = 0; indice < long_Alphab; indice++) {

            if (w_chaine->alphaNum == alphabet[indice]) { // si le cracttère exist dans alphabet alors
                // il codifier selon indice ou le cractère et dans le tableau


                p1->code = indice;
                s = (cod_maillon) malloc(sizeof(s)); // Nouveay maillon pour nouvel insertion

                s->ptr = NULL;

                p1->ptr = s;

                p1 = s;

                goto sortir; // aller a etique sortire a fin eviter de verifier condition indidcce = long_alphabet initilement

            }

        }


        if (indice == long_Alphab) {
            //  indice egale longeur alphabet dans le caractère qui et dans la chaine n'appartient pas à l'aphabet du langage
            //  ou que entre deux carcatère il exit un espace
            if (isspace(w_chaine->alphaNum)) {
                //  si un esapce ou plusieure espcae exist
                // entre de caractère de alphabet les espce sont codifier par -3
                p1->code = -3;

            } else {

                p1->code = -2; // carctère qui n'appartirnt pas a l'aphabet

            }

            s = (cod_maillon) malloc(sizeof(s)); // allocatio,
            s->ptr = NULL;
            p1->ptr = s;  // chainage
            p1 = s;      // changement postion de  p

        }

        sortir :
        w_chaine = w_chaine->ptr; // Avancer vert maillon suivant

        // FIn de la chaine
        if (w_chaine->ptr == NULL) {

            p1->code = -1; // fin de la chaine le maillon qui contient code -1 indique que j'ai lue tout la chaine
        }
    }
    elemine = chaine_codif; // presever tete chaine codifier
    bool rep;
    int count = 0;
    while (elemine != NULL) {  // chaine n'est pas terminer
        if ((elemine->ptr)->ptr != NULL) { // adresse du maillon suivant elemine->ptr
            if ((elemine->ptr)->code == -3) { // espace exist
                rep = true;
                if (count == 0) {           // pour dire c'est le premier espace
                    saveDebElm = elemine;  // sauvgarder addresse maillon ou en va eliminer  espace
                    count++;
                }
            } else {

                rep = false;  // eite pas espcae
                count = 0;
            }

        } else {// on est ariver a maillon qui precede le dernier
            saveEnd_Elem = elemine->ptr; // sauvgarder adresse du dernier maillon
            goto exit;   // sort de la boucle car si en rentre erreur  au niveau (elemine->ptr)->ptr != NULL  car maillon suiavnt n'exist pas
        }

        elemine = elemine->ptr;
    }

    exit:    // on trouver  espace

    if (rep == true) {
        saveDebElm->ptr = saveEnd_Elem; // elimine espace en changent juste le chainage
        // moins couteux en espcae memoire
        // de de aller de saveDeb jusqua
        // saveEnd_Elem
    }


}


// LECTURE
int lecture() {

    // Lecture Alphabet

    lire_Alphabet();


    printf("\nNb Ligne Tab Transition    =");

    scanf("%d", &ligne);

    printf("  Nb Colonne Tab Transition  =");

    scanf("%d", &colone);


    printf("\n Enter valeur entière des etats selon leur indice \n dans la table de transition \n si etat exist donne indice etat  sinon -1 \n");

    for (int lgn = 0; lgn < ligne; lgn++) {

        for (int col = 0; col < colone; col++) {

            printf("\n delta [ %d , %d ]= ", lgn, col);

            scanf("%d", &del[lgn][col]);

        }


    }

    // Lecture  Etat final
    lire_etat_final();

    // Lecture Chaine W
    lire_w();

    // Codification de la chaine W
    codifier_w();


}


int main() {

    lecture();

    automate(chaine_codif, del, F, nb_etat_final);


    // libere espace memoire des pointeur utiliser

    free(new_maill);
    free(p);
    free(p1);
    free(chaine_codif);
    free(elemine);
    free(s);
    free(saveDebElm);
    free(saveEnd_Elem);
    free(w_chaine);

}

