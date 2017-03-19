#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

typedef struct benevole{
    char nom[20];
    char prenom[20];
    char sexe;
    int CIN;
    int annee;
    struct benevole* suivant;
}Benevole;

typedef struct listBenevoles{
    Benevole *premier;
    int NbreElements;
}ListBenevoles;

typedef struct tranche{
    ListBenevoles *ListBenevoles;
    int borneSup;
    struct tranche *pere;
    struct tranche *filsG;
    struct tranche *filsD;
}Tranche;

/*** FONCTIONS A IMPLEMENTER ***/
Benevole *nouveauBen(char *nom, char *prenom , int CIN, char sexe, int annee);
Tranche *nouvelleTranche(int borneSup);
ListBenevoles *nouvelleListe();
Tranche *ajoutTranche(Tranche *racine , int borneSup);
Benevole *insererBen(Tranche *racine , Benevole *benevole);
Benevole *chercherBen(Tranche *racine ,int CIN, int annee);
int supprimerBen(Tranche **racine , int CIN, int annee);
int supprimerTranche(Tranche **racine , int borneSup);
ListBenevoles *BenDhonneur(Tranche *racine);
int actualiser(Tranche **current, Tranche **racine);
int totalBenTranche(Tranche *racine , int borneSup);
int totalBen(Tranche *racine);
float pourcentageTranche(Tranche *racine , int borneSup);
void afficherTranche(Tranche *racine , int borneSup);
void afficherArbre(Tranche *racine);

/*** FONCTIONS SUPPLEMENTAIRES ***/

//fonction qui insere un b�n�vole dans une liste : renvoie 0 si tout s'est bien pass�, 1 sinon
int insererListBen(Tranche *tranche, Benevole *benevole);

//fonction qui cherche une tranche dans l'arbre selon une borne pass�e en param�tre : renvoie NULL si la tranche n'existe pas
Tranche *chercherTranche(Tranche *racine, int borneSup);

//fonction qui renvoie l'ann�e actuelle
int anneeActuelle();

//fonction qui supprime une liste de b�n�voles, chaque pointeur sur un b�n�vole est d�sallou� et la liste est d�sallou�e
// renvoie 0 si tout s'est bien pass�, 1 sinon
int supprimerListBen(Tranche *t);


//fonction qui renvoie la tranche de l'arbre dont la borneSup est maximale
Tranche* maximum(Tranche *racine);


//fonction qui affiche les b�n�voles d'honneur
void afficherBenDhonneur(ListBenevoles* l);

//fonction qui calcule la borneSup associ�e � une ann�e
int calculBorne(int annee);

//fonction qui permet de d�truire l'arbre
void destructionArbre(Tranche** racine);

//fonction permettant de sauvegarder la liste de b�n�voles du maximum du sous arbre gauche dans la suppression avec 2fils
ListBenevoles* sauvegarderListe(ListBenevoles *l);


#endif // TP4_H_INCLUDED
