#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite) {
    T_Produit *prod=(T_Produit*)malloc(sizeof(T_Produit));
    if(prod==NULL){
        return NULL;
    }
    else {
        prod->marque=(char*)malloc(NMAX*(sizeof(char)));
        strcpy(prod->marque,marque);
        prod->prix=prix;
        prod->qualite=qualite;
        prod->quantite_en_stock=quantite;
        prod->suivant=NULL;
        return prod;
    }
}

T_Rayon *creerRayon(char *nom)
{
    T_Rayon *ray=(T_Rayon*)malloc(sizeof(T_Rayon));
    if (ray==NULL){
        return NULL;
    }
    else {
        ray->nom_rayon=(char*)malloc(NMAX*(sizeof(char)));
        strcpy(ray->nom_rayon,nom);
        ray->nombre_produits=0;
        ray->suivant=NULL;
        ray->premier=NULL;
        return ray;
    }
}

T_Magasin *creerMagasin(char *nom) {
    T_Magasin *magasin=(T_Magasin*)malloc(sizeof(T_Magasin));
    if(magasin==NULL){
        return NULL;
    }
    else {
        magasin->nom=(char*)malloc(NMAX*(sizeof(char)));
        if(magasin->nom==NULL){
            return NULL;
        }
        strcpy(magasin->nom,nom);
        magasin->premier=NULL;
        return magasin;
        }
}

int ajouterRayon(T_Magasin *magasin, T_Rayon *rayon) {
    T_Rayon *tmp=NULL;
     T_Rayon *tmp2=NULL;

    //si le magasin n'a pas de rayon on l'ajoute directement
    if(magasin->premier==NULL) {
        magasin->premier=rayon;
        return 1;
    }
    //sinon on trie dans l'ordre alphabetique et on l'ajoute
    else {
        tmp=magasin->premier;
        // ajout debut de liste
        if(strcmp(tmp->nom_rayon,rayon->nom_rayon)>0){
                magasin->premier=rayon;
                rayon->suivant=tmp;
                return 1;
        }
        else {
        while(strcmp(tmp->nom_rayon,rayon->nom_rayon)<=0){
                //les chaines sont indentiques donc le rayon existe deja
            if(strcmp(tmp->nom_rayon,rayon->nom_rayon)==0){
                printf("\nRayon deja existant!\n");
                return 0;
                }
                //ajout fin de liste
            if(tmp->suivant==NULL){
                tmp->suivant=rayon;
                rayon->suivant=NULL;
                return 1;
            }
            else {
                tmp2=tmp;
                tmp=tmp->suivant;
            }
        }
        //ajout milieu de liste
        tmp2->suivant=rayon;
        rayon->suivant=tmp;
        return 1;
        }
    }
}

int ajouterProduit(T_Rayon *rayon, T_Produit *produit) {
    T_Produit* p=NULL;
    T_Produit* tmp=NULL;
     //si le rayon est vide on ajoute le produit en tete de liste
    if (rayon->premier==NULL) {
        rayon->premier=produit;
        rayon->nombre_produits++;
        printf("\nProduit ajoute ! \n");
        return 1;
    }
    else {
        p=rayon->premier;
        //verification si la marque est deja présente
        while(strcmp(produit->marque,p->marque)!=0 && p->suivant!=NULL){
            p=p->suivant;
        }
        //la marque est deja presente
        if (strcmp(produit->marque,p->marque)==0){
            printf("\nProduit deja present\n");
            free(produit);
            return 0;
        }
        //la marque n'est pas deja presente
        else {
            p=rayon->premier;
            //ajout debut de liste
            if(produit->prix<=p->prix){
                rayon->premier=produit;
                produit->suivant=p;
                rayon->nombre_produits++;
                printf("\nProduit ajoute ! \n");
                return 1;
            }

            while(produit->prix>p->prix){
                tmp=p;
                if (p->suivant==NULL){
                    //ajout fin de liste
                    p->suivant=produit;
                    rayon->nombre_produits++;
                    printf("\n Produit ajoute ! \n");
                    return 1;
                }
                else {
                    p=p->suivant;
                }
            }
            //ajout milieu de liste
            tmp->suivant=produit;
            produit->suivant=p;
            rayon->nombre_produits++;
            printf("\n Produit ajoute ! \n");
            return 1;
        }

    }
    return 0;
}

T_Rayon *rechercherRayon(char *nom, T_Magasin* magasin){
    T_Rayon *ray=magasin->premier;
    if (ray!=NULL){
        while(strcmp(nom,ray->nom_rayon)!=0 && ray->suivant!=NULL){
            ray=ray->suivant;
        }
        if (strcmp(nom,ray->nom_rayon)==0){
            return ray;
        }
        return NULL;
    }
    return NULL;
}



void afficherMagasin(T_Magasin *magasin){
    //si le magasin n'a pas ete cree avant
    if(magasin==NULL){
        printf("\nPas de magasin\n");
        return;
    }
    T_Rayon *tmp=magasin->premier;
    printf("\n______________________________________\n");
    printf("NOM       |     NOMBRE DE PRODUITS");
    printf("\n______________________________________\n");
    //le magasin est vide
    if(tmp==NULL){
        printf("\nPas de rayon\n");
        return;
    }
    //le magasin n'est pas vide
    while(tmp!=NULL){
        printf("%-10s|%10d",tmp->nom_rayon,tmp->nombre_produits);
        tmp=tmp->suivant;
        printf("\n______________________________________\n");
    }

}

void afficherRayon(T_Rayon *rayon){
    T_Produit *prod=rayon->premier;
    printf("\n__________________________________________________________________\n");
    printf("MARQUE    |   PRIX   | QUALITE | QUANTITE EN STOCK");
    printf("\n__________________________________________________________________\n");
    //le rayon est vide
    if(prod==NULL){
        printf("Aucun produit\n");
        return;
    }
    //le rayon n'est pas vide
    while (prod!=NULL){
        printf("%-10s|%10.2f|    %c    |%10d",prod->marque,prod->prix,prod->qualite,prod->quantite_en_stock);
        prod=prod->suivant;
        printf("\n__________________________________________________________________\n");
    }
    return;
}

int supprimerProduit(T_Rayon *rayon, char* marque_produit){
    T_Produit *prod=rayon->premier;
    T_Produit *tmp=NULL;
    //le rayon est vide
    if(prod==NULL){
        printf("Pas de produit dans le rayon\n");
        return 0;
    }
    //le rayon n'est pas vide
    else {
            //suppression debut de chaine
        if(strcmp(prod->marque,marque_produit)==0){
            tmp=rayon->premier;
            rayon->premier=rayon->premier->suivant;
            free(tmp->marque);
            free(tmp);
            rayon->nombre_produits--;
            return 1;
        }
        else {
            while(strcmp(prod->marque,marque_produit)!=0){
                tmp=prod;
                prod=prod->suivant;
                //le produit n'existe pas dans le rayon
                if(prod==NULL){
                    printf("Produit inexistant\n");
                    return 0;
                }
            }
            //suppression du produit
            tmp->suivant=prod->suivant;
            free(prod->marque);
            free(prod);
            rayon->nombre_produits--;
            return 1;
        }
    }
}


int supprimerRayon(T_Magasin *magasin, char *nom_rayon){
    //pas de magasin cree
    if(magasin==NULL){
        printf("\n Pas de magasin ! \n");
        return 0;
    }
    else {
        T_Rayon *ray=magasin->premier;
        T_Rayon *prec=NULL;
        //si le magasin est vide
        if(ray==NULL){
            printf("\n Pas de rayon dans le magasin ! \n");
            return 0;
        }
        else {
                //suppression debut de chaine
            if(strcmp(ray->nom_rayon,nom_rayon)==0){
                magasin->premier=magasin->premier->suivant;
                supprimerProduitsRayon(ray);
                free(ray->nom_rayon);
                free(ray);
                return 1;
            }
            else {
                while (strcmp(ray->nom_rayon,nom_rayon)!=0){
                    prec=ray;
                    ray=ray->suivant;
                    if (ray==NULL){
                        printf("\n Rayon inexistant !\n");
                        return 0;
                    }
                }
                prec->suivant=ray->suivant;
                supprimerProduitsRayon(ray);
                free(ray->nom_rayon);
                free(ray);
                return 1;
            }
        }
    }
}

void supprimerProduitsRayon(T_Rayon* ray){
    T_Produit *tmp=NULL;
    while(ray->premier!=NULL){
        tmp=ray->premier;
        ray->premier=ray->premier->suivant;
        free(tmp->marque);
        free(tmp);
    }
    return;
}


void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max){
    T_Rayon *ray=magasin->premier;
    T_Recherche *tab=NULL;
    if (ray==NULL){
        printf("Pas de rayon dans le magasin \n");
        return;
    }
    T_Produit *prod=NULL;
    while(ray!=NULL){
        prod=ray->premier;
        while(prod!=NULL){
            if (prod->prix>=prix_min && prod->prix<=prix_max){
                if (tab==NULL){
                    tab=(T_Recherche*)malloc(sizeof(T_Recherche));
                    tab->prod=(T_Produit*)malloc(sizeof(T_Produit));
                    tab->prod=prod;
                    tab->nom_rayon=(char*)malloc(NMAX*sizeof(char));
                    tab->nom_rayon=ray->nom_rayon;
                    tab->suivant=NULL;
                }
                else {
                    tab=ajouterProduitRecher(tab,prod,ray->nom_rayon);
                }

            }
            prod=prod->suivant;
        }
        ray=ray->suivant;
    }
    if(tab==NULL){
        printf("Aucun resultat\n");
    }
    else {
        printf("\n_________________________________________________________________________\n");
        printf("MARQUE    |     PRIX    | QUALITE | QUANTITE |   RAYON");
        printf("\n_________________________________________________________________________\n");
       while(tab!=NULL){
        printf("%-10s|%10.2f\t|    %c    |%10d|%10s",tab->prod->marque,tab->prod->prix, tab->prod->qualite, tab->prod->quantite_en_stock,tab->nom_rayon);
        printf("\n_________________________________________________________________________\n");
        T_Recherche* tmp=tab;
        tab=tab->suivant;
        free(tmp);
       }
       free(tab);
    }

}

T_Recherche* ajouterProduitRecher(T_Recherche *recherche, T_Produit *prod, char* nom_rayon){
        T_Recherche *tmp=recherche;
        T_Recherche *prec=NULL;
        T_Recherche *newR=(T_Recherche*)malloc(sizeof(T_Recherche));
        newR->prod=(T_Produit*)malloc(sizeof(T_Produit));
        newR->prod=prod;
        newR->nom_rayon=(char*)malloc(NMAX*(sizeof(char)));
        newR->nom_rayon=nom_rayon;
        newR->suivant=NULL;
        if(recherche->prod->prix>=prod->prix){
            newR->suivant=recherche;
            return newR;
        }
        while(tmp->prod->prix<prod->prix){
                if(tmp->suivant==NULL){
                        tmp->suivant=newR;
                        return recherche;
                }
                else {
                    prec=tmp;
                    tmp=tmp->suivant;
                }
        }
        prec->suivant=newR;
        newR->suivant=tmp;
        return recherche;

    }
