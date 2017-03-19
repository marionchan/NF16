#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED
#define NMAX 30

typedef struct Produit {
    char *marque;
    float prix;
    char qualite;
    int quantite_en_stock;
    struct Produit *suivant;

}T_Produit;

typedef struct Rayon{
    char *nom_rayon;
    int nombre_produits;
    T_Produit *premier;
    struct Rayon *suivant;
}T_Rayon;

typedef struct Magasin {
    char *nom;
    T_Rayon *premier;
}T_Magasin;

typedef struct Recherche{
    T_Produit* prod;
    char* nom_rayon;
    struct Recherche *suivant;
}T_Recherche;


T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);
int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon);
int ajouterProduit(T_Rayon *rayon, T_Produit *produit);
void afficherMagasin(T_Magasin *magasin);
void afficherRayon(T_Rayon *rayon);
//fonction qui permet de rechercher le bon rayon en ayant le nom de celui-ci
T_Rayon *rechercherRayon(char *nom, T_Magasin *magasin);
int supprimerProduit(T_Rayon *rayon, char* marque_produit);
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);
//fonction pour supprimer tout les produits lors de la suppression d'un rayon
void supprimerProduitsRayon(T_Rayon* ray);
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);
//fonction pour la recherche de produits
T_Recherche* ajouterProduitRecher(T_Recherche *recherche, T_Produit *prod, char* nom_rayon);
#endif // TP3_H_INCLUDED
