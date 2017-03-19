#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "tp4.h"

/*****************************
 *  Fonctions à implémenter  *
 *****************************/


Benevole *nouveauBen(char *nom, char *prenom , int CIN, char sexe, int annee){
    Benevole *newB=(Benevole*)malloc(sizeof(Benevole));
    if(newB==NULL){
        return NULL;
    }
    newB->suivant=NULL;
    strcpy(newB->nom,nom);
    strcpy(newB->prenom,prenom);
    newB->CIN=CIN;
    newB->sexe=sexe;
    newB->annee=annee;
    return newB;
}


Tranche *nouvelleTranche(int borneSup){
    Tranche *newT=(Tranche*)malloc(sizeof(Tranche));
    if(newT==NULL){
        return NULL;
    }
     if (borneSup%5!=0)
        borneSup=5*(borneSup/5)+5;
    newT->pere=NULL;
    newT->filsD=NULL;
    newT->filsG=NULL;
    newT->borneSup=borneSup;
    newT->ListBenevoles=NULL;
    return newT;
}


ListBenevoles *nouvelleListe(){
    ListBenevoles *newL=(ListBenevoles*)malloc(sizeof(ListBenevoles));
    if(newL==NULL){
        return NULL;
    }
    newL->premier=NULL;
    newL->NbreElements=0;
    return newL;
}

Tranche *ajoutTranche(Tranche *racine , int borneSup){
    //on calcule la borne associee a l'age entré
    if (borneSup%5!=0)
        borneSup=5*(borneSup/5)+5;
    Tranche *it=racine;
    Tranche *it2=NULL;
    while(it!=NULL){
        it2=it;
        if(borneSup<it->borneSup){
            it=it->filsG;
        }
        else if(borneSup==it->borneSup){
            printf("Borne déja présente\n");
            return NULL;
        }
        else{
        it=it->filsD;
        }
    }
    Tranche *newT=nouvelleTranche(borneSup);
    newT->pere=it2;
    if(borneSup<it2->borneSup){
        it2->filsG=newT;
    }
    else {
        it2->filsD=newT;
    }
    return newT;
}

Benevole *insererBen(Tranche *racine , Benevole *benevole){
    int borne,i;
    borne=calculBorne(benevole->annee);
   Tranche *it=chercherTranche(racine,borne);
    if(it!=NULL && it->borneSup==borne){
        i=insererListBen(it,benevole);
        if (i==0){
            it->ListBenevoles->NbreElements++;
            return benevole;
        }
        return NULL;
    }
    else {
        Tranche *newT=ajoutTranche(racine,borne);
        i=insererListBen(newT,benevole);
        if(i==0){
            newT->ListBenevoles->NbreElements++;
            return benevole;
        }
        return NULL;
    }
}


Benevole *chercherBen(Tranche *racine ,int CIN, int annee){
    int borne;
    borne=calculBorne(annee);
    Tranche *it=chercherTranche(racine,borne);
    if(it==NULL){
        printf("Tranche non presente\n");
        return NULL;
    }
    Benevole *b=it->ListBenevoles->premier;
    while(b!=NULL && b->CIN!=CIN){
        b=b->suivant;
    }
    if(b==NULL){
        printf("Benevole n'existe pas\n");
        return NULL;
    }
    printf("benevole trouve\n");
    return b;
}

int supprimerBen(Tranche **racine , int CIN, int annee){
    int borne,i;
    borne=calculBorne(annee);
    Tranche *it=chercherTranche((*racine),borne);
    if(it==NULL || it->ListBenevoles->premier==NULL){
        printf("Tranche non presente\n");
        return 1;
    }
    Benevole *tmp=NULL;
    if(it->ListBenevoles->premier->CIN==CIN){
        tmp=it->ListBenevoles->premier;
        it->ListBenevoles->premier=it->ListBenevoles->premier->suivant;
        free(tmp);
        it->ListBenevoles->NbreElements--;
        if(it->ListBenevoles->NbreElements==0){
            i=supprimerTranche(racine,borne);
            if(i==1)
                return 1;
        }
        return 0;
    }
    Benevole* b=it->ListBenevoles->premier;
    while(b->suivant!=NULL && b->suivant->CIN!=CIN){
        b=b->suivant;
    }
    if(b->suivant==NULL)
        return 1;
    tmp=b->suivant;
    b->suivant=b->suivant->suivant;
    free(tmp);
    it->ListBenevoles->NbreElements--;
    if(it->ListBenevoles->NbreElements==0){
        i=supprimerTranche(racine,borne);
        if(i==1)
            return 1;
    }
    return 0;
}

int supprimerTranche(Tranche **racine , int borneSup){
    if(*racine==NULL)
        return 1;
    Tranche *it=*racine;
    Tranche *it2=NULL;
    int i;
    while(it!=NULL && it->borneSup!=borneSup){
        it2=it;
        if(it->borneSup>borneSup){
            it=it->filsG;
        }
        else{
            it=it->filsD;
        }
    }
    if(it==NULL){
            printf("Tranche non presente\n");
        return 1;
    }
    //si la tranche a supprimer n'a pas de fils
    if(it->filsG==NULL && it->filsD==NULL){
        if(it2==NULL){
            Tranche *tmp=*racine;
            i=supprimerListBen(*racine);
            if(i==1)
                return 1;
            *racine=NULL;
            free(tmp);

            return 0;
        }
        if(it2->borneSup>borneSup){
            it2->filsG=NULL;
        }
        if(it2->borneSup<borneSup){
            it2->filsD=NULL;
        }
        i=supprimerListBen(it);
        if(i==1)
            return 1;
        free(it);
        return 0;
    }
    if(it->filsG!=NULL && it->filsD==NULL){
        //si le pere est NULL = le noeud a supp est la racine
        if(it2==NULL){
            Tranche *tmp=*racine;
            i=supprimerListBen(*racine);
            if(i==1)
                return 1;
            *racine=(*racine)->filsG;
            (*racine)->pere=NULL;
            free(tmp);
            return 0;
        }
        if(it2->borneSup>borneSup){
            it2->filsG=it->filsG;
            it->filsG->pere=it2;
        }
        if(it2->borneSup<borneSup){
            it2->filsD=it->filsG;
            it->filsG->pere=it2;
        }
        i=supprimerListBen(it);
        if(i==1)
            return 1;
        free(it);
        return 0;
    }

    if(it->filsG==NULL && it->filsD!=NULL){
        if(it2==NULL){
            Tranche *tmp=*racine;
            i=supprimerListBen(*racine);
            if(i==1)
                return 1;
            *racine=(*racine)->filsD;
            (*racine)->pere=NULL;
            free(tmp);
            return 0;
        }
        if(it2->borneSup>borneSup){
            it2->filsG=it->filsD;
            it->filsD->pere=it2;
        }
        if(it2->borneSup<borneSup){
            it2->filsD=it->filsD;
            it->filsD->pere=it2;
        }
        i=supprimerListBen(it);
        if(i==1)
            return 1;
        free(it);
        return 0;
    }
    else{
        i=supprimerListBen(it);
        if(i==1)
            return 1;
        it->ListBenevoles=nouvelleListe();
        Tranche *max;
        max=maximum(it->filsG);
        int maxsave=max->borneSup;
        ListBenevoles *save=sauvegarderListe(max->ListBenevoles);
        if(it2==NULL){
            supprimerTranche(racine,max->borneSup);
            (*racine)->borneSup=maxsave;
            (*racine)->ListBenevoles=save;
            return 0;
        }
        else {
            supprimerTranche(&it2,max->borneSup);
            it->borneSup=maxsave;
            it->ListBenevoles=save;
            return 0;
        }

    }
}

ListBenevoles *BenDhonneur(Tranche *racine){
    Tranche *t;
    t=maximum(racine);
    ListBenevoles *l=nouvelleListe();
    int anneemax;
    Benevole *b=t->ListBenevoles->premier;
    while(b->suivant!=NULL){
        b=b->suivant;
    }
    anneemax=b->annee;
    b=t->ListBenevoles->premier;
    while(b->annee>anneemax){
        b=b->suivant;
    }
    l->premier=b;
    // pour trouver le nombre d'elements :
    Benevole *it=l->premier;
    int cpt=0;
    while(it!=NULL) {
        it=it->suivant;
        cpt++;
    }
    l->NbreElements=cpt;
    return l;
}

int actualiser(Tranche **current, Tranche **racine){
        int cpt_tmp=0;
        int cpt2=0;
        int annee;
        Benevole *b=NULL;
        Benevole *save=NULL;
        annee=anneeActuelle()-(*current)->borneSup;
                b=(*current)->ListBenevoles->premier;
                //le premier a directement l'age a supprimer
                if(b->annee==annee){
                    save=b;
                    //on deplace toute la liste
                    (*current)->ListBenevoles->premier=NULL;
                    cpt_tmp=(*current)->ListBenevoles->NbreElements;
                    cpt2=cpt_tmp;

                }
                else {
                    while(b->suivant!=NULL && b->suivant->annee>annee){
                        b=b->suivant;
                        cpt_tmp++;
                    }
                    cpt_tmp=(*current)->ListBenevoles->NbreElements-cpt_tmp-1;
                    save=b->suivant;
                    // on détache les bénévoles à déplacer
                    b->suivant=NULL;
                    cpt2=cpt_tmp;
                }
                if((*current)->filsG!=NULL){
                    cpt_tmp=cpt_tmp+actualiser(&((*current)->filsG),racine);
                }
                if((*current)->filsD!=NULL){
                    cpt_tmp=cpt_tmp+actualiser(&((*current)->filsD),racine);
                }
                //si il y a des benevoles à deplacer
                if(save!=NULL){
                    //on cherche la tranche ou l'on doit deplacer les benevoles
                    Tranche *t=chercherTranche((*racine),(*current)->borneSup+5);
                    //si la tranche n'est pas présente on doit la creer
                    if(t==NULL){
                        Tranche *newT=ajoutTranche((*racine),(*current)->borneSup+5);
                        newT->ListBenevoles=nouvelleListe();
                        newT->ListBenevoles->premier=save;
                        newT->ListBenevoles->NbreElements=cpt2;
                    }

                    else {
                        //on sauvergarde le premier de la liste
                        Benevole *tmp=t->ListBenevoles->premier;
                        //on ajoute les autres en tete de liste
                        t->ListBenevoles->premier=save;
                        Benevole *tmp2=t->ListBenevoles->premier;

                        while(tmp2->suivant!=NULL){
                            //cpt_tmp++;
                        tmp2=tmp2->suivant;
                        }
                        //on rattache l'ancienne tete de liste à la nouvelle tete de liste
                        tmp2->suivant=tmp;
                        t->ListBenevoles->NbreElements=t->ListBenevoles->NbreElements+cpt2;
                    }
                    (*current)->ListBenevoles->NbreElements=(*current)->ListBenevoles->NbreElements-cpt2;

                }
                //si apres le deplacement la liste est vide on supprime la tranche
                if((*current)->ListBenevoles->NbreElements==0)
                        supprimerTranche(racine,(*current)->borneSup);
        return cpt_tmp;

}

int totalBenTranche(Tranche *racine , int borneSup){
    Tranche *t=chercherTranche(racine,borneSup);
    if(t==NULL){
        printf("Tranche non presente\n");
        return -1;
    }
    return t->ListBenevoles->NbreElements;

}

int totalBen(Tranche *racine){
    if(racine==NULL || racine->ListBenevoles==NULL || racine->ListBenevoles->NbreElements==0){
        return 0;
    }
    return racine->ListBenevoles->NbreElements+totalBen(racine->filsG)+totalBen(racine->filsD);

}

float pourcentageTranche(Tranche *racine , int borneSup){
    Tranche *it=chercherTranche(racine,borneSup);
    if(it==NULL){
        printf("Tranche non presente\n");
        return 0;
    }
    return (float)it->ListBenevoles->NbreElements/(float)totalBen(racine);
}

void afficherTranche(Tranche *racine , int borneSup){
    Tranche *it=chercherTranche(racine,borneSup);
    if(it==NULL){
        printf("Tranche non presente\n");
        return;
    }
    if(it->ListBenevoles==NULL){
        printf("Pas de benevoles dans cette tranche\n");
        return;
    }
    Benevole *b=it->ListBenevoles->premier;
    printf("\nNombre de benevoles dans la tranche : %d \n",it->ListBenevoles->NbreElements);
    printf("-----------------------------------------\n");
    printf("Nom\t  Prenom    Sexe  Annee  CIN\n");
    printf("-----------------------------------------\n");
    while(b!=NULL){
        printf("%-10s%-10s%c     %d  %d\n",b->nom,b->prenom,b->sexe,b->annee,b->CIN);
        printf("-----------------------------------------\n");
        b=b->suivant;
    }
    return;
}

void afficherArbre(Tranche *racine){
    if(racine==NULL){
        return;
    }
    afficherArbre(racine->filsG);
    printf(" %d ", racine->borneSup);
    afficherArbre(racine->filsD);
    return;
}



/******************************
 *  Fonctions supplémentaires *
 ******************************/


int anneeActuelle(){
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);
    return instant.tm_year + 1900;
}

int calculBorne(int annee){
    int age=anneeActuelle()-annee;
    if (age%5==0){
        return age;
    }
    else{
        return 5*(age/5)+5;
    }
}


int insererListBen(Tranche *tranche, Benevole *benevole){
    if(tranche==NULL || benevole==NULL){
        return 1;
    }
    if(tranche->ListBenevoles==NULL){
        tranche->ListBenevoles=nouvelleListe();
        tranche->ListBenevoles->premier=benevole;
        return 0;
    }
    if(tranche->ListBenevoles->premier->annee<benevole->annee){
        benevole->suivant=tranche->ListBenevoles->premier;
        tranche->ListBenevoles->premier=benevole;
        return 0;
    }
    Benevole *it=tranche->ListBenevoles->premier;
    if(it->CIN==benevole->CIN){
            printf("Benevole deja present!\n");
            return 1;
        }
    while(it->suivant!=NULL && it->suivant->annee>=benevole->annee && it->suivant->CIN!=benevole->CIN){
        if(it->suivant->CIN==benevole->CIN){
            printf("Benevole deja present!\n");
            return 1;
        }
        it=it->suivant;
    }
    if(it->suivant!=NULL && it->suivant->CIN==benevole->CIN){
            printf("Benevole deja present!\n");
            return 1;
    }
    benevole->suivant=it->suivant;
    it->suivant=benevole;
    return 0;

}



Tranche *chercherTranche(Tranche *racine, int borneSup){
     Tranche *it=racine;
    while(it!=NULL && it->borneSup!=borneSup){
        if(it->borneSup>borneSup){
            it=it->filsG;
        }
        else{
            it=it->filsD;
        }
    }
    if(it==NULL){
        return NULL;
    }
    return it;
}



int supprimerListBen(Tranche *t){
    if(t==NULL){
        return 1;
    }
    if(t->ListBenevoles==NULL){
        return 0;
    }
    Benevole *b=t->ListBenevoles->premier;
    while(b!=NULL){
        Benevole *tmp=b;
        b=b->suivant;
        free(tmp);
    }
    free(t->ListBenevoles);
    return 0;
}


void afficherBenDhonneur(ListBenevoles* l){
    Benevole *b=l->premier;
    printf("***********BENEVOLES D'HONNEUR***********\n\n");
    printf("Nombre de benevoles d'honneur : %d \n", l->NbreElements);
    printf("-----------------------------------------\n");
    printf("Nom\t  Prenom    Sexe  Annee  CIN\n");
    printf("-----------------------------------------\n");
    while(b!=NULL){
        printf("%-10s%-10s%c     %d  %d\n",b->nom,b->prenom,b->sexe,b->annee,b->CIN);
        printf("-----------------------------------------\n");
        b=b->suivant;
    }
    free(l);
}

Tranche* maximum(Tranche *racine){
    Tranche *droit=racine;
    while(droit->filsD!=NULL){
        droit=droit->filsD;
    }
    return droit;
}


ListBenevoles* sauvegarderListe(ListBenevoles *l){
    if(l==NULL){
        return NULL;
    }
    ListBenevoles *newL=nouvelleListe();
    newL->NbreElements=l->NbreElements;
    Benevole *b=l->premier;
    while(b!=NULL){
        Benevole* tmp2=nouveauBen(b->nom,b->prenom,b->CIN,b->sexe,b->annee);
        if (newL->premier==NULL){
            newL->premier=tmp2;
        }
        else{
            tmp2->suivant=newL->premier;
            newL->premier=tmp2;
        }
        b=b->suivant;
    }
    return newL;
}


void destructionArbre(Tranche** racine){
    int i;
    if((*racine)->filsD!=NULL)
        destructionArbre(&((*racine)->filsD));
    if((*racine)->filsG!=NULL)
        destructionArbre(&((*racine)->filsG));
    i=supprimerListBen((*racine));
    if(i==1){
        printf("Erreur\n");
        return;
    }
    free(*racine);
    *racine=NULL;
    return;

}







