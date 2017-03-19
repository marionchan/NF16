#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#define NMAX 30

int main()
{
    int choix=0;
    char nom_mag[NMAX];
    char nom_ray[NMAX];
    char marque[NMAX];
    T_Magasin *mag=NULL;
    T_Rayon *ray=NULL;
    T_Produit *prod=NULL;
    int i,quantite;
    float prix,min,max;
    char qualite;
    while (choix!=9){
        printf("\n-----------------MENU-----------------\n");
        printf("1. Creer un magasin\n");
        printf("2. Ajouter un rayon au magasin\n");
        printf("3. Ajouter un produit dans un rayon\n");
        printf("4. Afficher les rayons du magasin\n");
        printf("5. Afficher les produits d'un rayon\n");
        printf("6. Supprimer un produit\n");
        printf("7. Supprimer un rayon\n");
        printf("8. Rechercher un produit par prix\n");
        printf("9. Quitter\n");
        printf("\nChoix ? \n");
        scanf("%d",&choix);
        fflush(stdin);
        switch(choix){
        case 1:
            printf("\nCreation d'un magasin\n");
            printf("entrer le nom du magasin\n");
            scanf("%s",nom_mag);
            mag=creerMagasin(nom_mag);
            if(mag!=NULL){
                printf("\nMagasin %s cree ! \n",nom_mag);
                break;
            }
            printf("Erreur!\n\n");
            break;

        case 2:
            printf("\nAjout d'un rayon au magasin\n");
            if (mag==NULL){
                printf("\nPas de magasin cree\n");
            }
            else {
                printf("Entrer le nom du rayon\n");
                scanf("%s",nom_ray);
                ray=creerRayon(nom_ray);
                if (ray!=NULL){
                    i=ajouterRayon(mag,ray);
                    if (i==1){
                        printf("\nRayon %s ajoute !\n", nom_ray);
                        break;
                    }
                    printf("Erreur!\n");
                    break;
                }
                printf("Erreur!\n");
            }
            break;

        case 3 :
            printf("\nAjout d'un produit a un rayon\n");
            printf("\nMarque du produit?\n");
            scanf("%s",marque);
            printf("Prix du produit ? \n");
            scanf("%f",&prix);
            printf("\nQuantite du produit?\n");
            scanf("%d",&quantite);
            qualite='\0';
            while(qualite!='A' && qualite != 'B' && qualite!='C'){
                    fflush(stdin);
                    printf("\nQualite du produit? (A, B ou C)\n");
                    scanf("%c",&qualite);
            }
            printf("\nRayon ou ajouter le produit?\n");
            scanf("%s",nom_ray);
            if (mag==NULL){
                printf("\nPas de magasin!\n");
                break;
            }
            else {
                ray=rechercherRayon(nom_ray, mag);
                if (ray==NULL){
                    printf("\nRayon inexistant ! \n");
                    break;
                }
                else{
                    prod=creerProduit(marque,prix,qualite,quantite);
                    if(prod==NULL){
                        printf("\nErreur!");
                        break;
                    }
                    else {
                        i=ajouterProduit(ray,prod);
                    }

                }
            }
            break;

        case 4:
            printf("\nAffichage des rayons du magasin\n");
            afficherMagasin(mag);
            break;
        case 5:
            printf("\nAffichage des produits d'un rayon\n");
            printf("\nNom du rayon a afficher?\n");
            scanf("%s",nom_ray);
            ray=rechercherRayon(nom_ray, mag);
            if (ray==NULL){
                printf("\nRayon inexistant ! \n");
                break;
            }
            else
                afficherRayon(ray);
            break;
        case 6:
            printf("\nSuppression d'un produit\n");
            printf("\nQuel rayon ?\n");
            scanf("%s",nom_ray);
            if (mag==NULL){
                printf("Pas de magasin !");
                break;
            }
            ray=rechercherRayon(nom_ray, mag);
            if (ray==NULL){
                printf("\nRayon inexistant ! \n");
                break;
            }
            else {
                printf("\nMarque du produit a supprimer\n");
                scanf("%s",marque);
                i=supprimerProduit(ray, marque);
                if (i==1){
                    printf("\nProduit supprime !\n");
                }
            }
            break;
        case 7:
            printf("\nSuppression d'un rayon\n");
            printf("\nQuel rayon?\n");
            scanf("%s",nom_ray);
            if (mag==NULL){
                printf("Pas de magasin !");
                break;
            }
            i=supprimerRayon(mag,nom_ray);
            if (i==1)
                printf("\nRayon supprime!\n");
            break;
        case 8:
            printf("\nRecherche d'un produit par prix\n");
            if (mag==NULL){
                printf("Pas de magasin !");
                break;
            }
            printf("\nPrix minimum pour la recherche ? \n");
            scanf("%f",&min);
            printf("\nPrix maximum pour la recherche ? \n");
            scanf("%f",&max);
            rechercheProduits(mag, min,max);
            break;
        case 9:
            printf("\nQuitter\n");
            break;
        default:
            printf("Erreur : choix impossible !\n");
            break;

        }
    }
    return 0;
}
