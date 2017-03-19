#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tp4.h"

int main(){

    int choix=0,borne,i,arbreCree=0;
    Tranche *t=NULL;
    Benevole *b=NULL;
    ListBenevoles *l=NULL;
    char nom[20];
    char prenom[20];
    int annee,CIN;
    char sexe;
    while (choix!=13){
        printf("\n--------------------------------MENU--------------------------------\n");
        printf("1.\tInitialiser un arbre\n");
        printf("2.\tAjouter une tranche\n");
        printf("3.\tAjouter un benevole dans une tranche d'age\n");
        printf("4.\tAfficher les tranches d'age d'un ABR\n");
        printf("5.\tAfficher les benevoles d'une tranche d'age\n");
        printf("6.\tSupprimer un benevole\n");
        printf("7.\tSupprimer une tranche\n");
        printf("8.\tAfficher les benevoles d'honneur\n");
        printf("9.\tAfficher le nombre total de benevoles\n");
        printf("10.\tActualiser l'ABR\n");
        printf("11.\tAfficher le pourcentage de benevoles d'une tranche d'age\n");
        printf("12.\tDetruire l'arbre\n");
        printf("13.\tQuitter\n");
        printf("\nChoix ? \n");
        scanf("%d",&choix);
        fflush(stdin);
        switch (choix){
        case 1:
            printf("\nInitialisation d'un arbre\n");
            Tranche *arbre=NULL;
            printf("Arbre initialise!\n");
            arbreCree=1;
            break;
        case 2:
            printf("Ajout d'une tranche\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("Entrer la borne supérieur\n");
            scanf("%d",&borne);
            if(arbre==NULL){
                arbre=nouvelleTranche(borne);
                break;
            }
            t=ajoutTranche(arbre,borne);
            if(t==NULL){
                printf("erreur\n");
            }
            break;
        case 3:
            printf("Ajout d'un bénévole dans une tranche d'age\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("Nom\n");
            fgets(nom,sizeof nom,stdin);
            //suppression du retour chariot
            nom[strlen(nom)-1]='\0';
            printf("Prenom\n");
            fgets(prenom,sizeof prenom,stdin);
            //suppression du retour chariot
            prenom[strlen(prenom)-1]='\0';
            printf("annee de naissance\n");
            scanf("%d",&annee);
            fflush(stdin);
            sexe='X';
            while(sexe!='M' && sexe!='F'){
                printf("sexe : M ou F \n");
                scanf("%c",&sexe);
                fflush(stdin);
            }
            printf("cin\n");
            scanf("%d",&CIN);
            b=nouveauBen(nom,prenom,CIN,sexe,annee);
            if(b==NULL){
                printf("Erreur!\n");
                break;
            }
            borne=calculBorne(annee);
            //printf("borne:%d\n",borne);
            if(arbre==NULL){
                arbre=nouvelleTranche(borne);
            }
            b=insererBen(arbre,b);
            if(b==NULL){
                printf("Erreur!\n");
                break;
            }
            break;
        case 4:
            printf("Affichage des tranches d'age d'un ABR\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            afficherArbre(arbre);
            break;
        case 5:
            printf("Affichage des benevoles d'une tranche d'age\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("Entrer la borne sup de la tranche\n");
            scanf("%d",&borne);
            afficherTranche(arbre,borne);
            break;
        case 6:
            printf("Suppression d'un benevole\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("Annee\n");
            scanf("%d",&annee);
            printf("Cin\n");
            scanf("%d",&CIN);
            i=supprimerBen(&arbre,CIN,annee);
            if(i==0){
                printf("Benevole supprime!\n");
                break;
            }
            printf("Erreur\n");
            break;
        case 7:
            printf("Suppression d'une tranche\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("Borne de la tranche\n");
            scanf("%d",&borne);
            i=supprimerTranche(&arbre,borne);
            break;
        case 8:
            printf("Affichage des bénévoles d'honneur\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            l=BenDhonneur(arbre);
            afficherBenDhonneur(l);
            break;
        case 9:
            printf("Affichage du nombre total de benevoles\n\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("**************************************\n");
            printf("Nombre total de benevoles : %d\n", totalBen(arbre));
            printf("**************************************\n");
            break;
        case 10:
            printf("Actualisation de l'ABR\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("%d benevoles ont ete deplaces\n",actualiser(&arbre,&arbre));
            break;
        case 11:
            printf("Affichage du pourcentage de bénévoles d'une tranche d'age\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            printf("borne\n");
            scanf("%d",&borne);
            printf("Pourcentage de la tranche %d : %f \n", borne, pourcentageTranche(arbre,borne));
            break;
        case 12:
            printf("Destruction de l'arbre\n");
            if(arbreCree==0){
                printf("Pas d'arbre initialise\n");
                break;
            }
            destructionArbre(&arbre);
            arbreCree=0;
            break;
        case 13:
            printf("Sortie\n");
            break;
        default:
            printf("Erreur de saisie\n");
        }
    }
    return 0;
}


