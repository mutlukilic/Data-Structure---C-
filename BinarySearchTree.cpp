#include <stdio.h>
#include <stdlib.h>

struct dugum{
	int icerik;
	struct dugum *sol;
	struct dugum *sag;
};
typedef struct dugum Dugum;

struct agac{
	Dugum *kok;
};
typedef struct agac Agac;

void ikili_arama_agaci_olustur(Agac **agac){
	*agac = (Agac*)malloc(sizeof(Agac));
	if((*agac) == NULL){
		printf("Yeteri kadar alan yok"); return ;
	}
	(*agac)->kok = NULL;
}

int ikili_agac_bosmu(Agac *agac){
	if(agac->kok == NULL) return 1;
	return 0;
}

Dugum* dugum_olustur(int icerik){
	Dugum *yeni_dugum = (Dugum*)malloc(sizeof(Dugum));
	if(yeni_dugum == NULL){
		printf("Yeteri kadar alan yok");
	}
	yeni_dugum->icerik = icerik;
	yeni_dugum->sol = NULL;
	yeni_dugum->sag = NULL;
	return yeni_dugum;
}

void ekle(Agac *agac,int icerik){
	Dugum *yeni_dugum;
	Dugum *geri,*ileri;
	ileri = agac->kok;
	while(ileri != NULL){
		geri = ileri;
		if(ileri->icerik > icerik) ileri = ileri->sol;
		else if(ileri->icerik < icerik) ileri = ileri->sag;
		else return;
	}
	yeni_dugum = dugum_olustur(icerik);
	if(agac->kok == NULL){
		agac->kok = yeni_dugum;
		return;
	}
	if(geri->icerik > icerik) geri->sol = yeni_dugum;
	else geri->sag = yeni_dugum;
}

/*void sil(struct ikili_arama_agaci *agac, int silinen){
    
    struct dugum *d=agac->kok;
    struct dugum *parent=NULL;
    struct dugum *d1,*d2;
    int sol;
    while(d!=NULL){
        if(silinen < d->icerik){
            parent=d; d=d->sol; sol=1;
        }
        else if(silinen > d->icerik){
            parent=d; d=d->sag; sol = 0;
        }
        else break;
    }
    if(d==NULL) return;
    if(d->sol==NULL){ // silinen dugumun solu bos
        if(parent==NULL) agac->kok=d->sag;
        else{
            if(sol==1) parent->sol=d->sag;
            else parent->sag=d->sag;
        }
    }
    else if(d->sag==NULL){  // silinen dugumun sagi bos
        if(parent==NULL) agac->kok=d->sol;
        else {
            if(sol==1) parent->sol=d->sol;
            else parent->sag = d->sol;
        }
    }
  /*  else { // silinen dugumun hem sagi hem de solu dolu
           // silinencek dugumun solunun en sagina git
           // en sagdaki dugum silinen dugumun konumunu alir
        d1=d->sol;
        d2=NULL;
        while(d1->sag!=NULL){
            d2=d1;
            d1=d1->sag;
        }
        if(d2!=NULL){
            d2->sag= d1->sol;
            d1->sol=d->sol;
        }
        d1->sag = d->sag;
        if(parent==NULL) agac->kok=d1; // agacin koku degisti
        else {
            if(sol==1) parent->sol=d1;
            else parent->sag=d1;
        }
    } 
    
    else { // silinen dugumun hem sagi hem de solu dolu
           // silinencek dugumun saginin en soluna git
           // en soldaki dugum silinen dugumun konumunu alir
        d1=d->sag;
        d2=NULL;
        while(d1->sol!=NULL){
            d2=d1;
            d1=d1->sol;
        }
        if(d2!=NULL){
            d2->sol= d1->sag;
            d1->sag=d->sag;
        }
        d1->sol = d->sol;
        if(parent==NULL) agac->kok=d1; // agacin koku degisti
        else {
            if(sol==1) parent->sol=d1;
            else parent->sag=d1;
        }
    }
    free(d); 
}*/

void inorder_yardimci(Dugum *kok){
	if(kok != NULL){
		inorder_yardimci(kok->sol);
		printf("%4d ",kok->icerik);
		inorder_yardimci(kok->sag);
	}
	/*if(kok == NULL) return;
	inorder_yardimci(kok->sol);
	printf("%4d ",kok->icerik);
	inorder_yardimci(kok->sag);*/
}

void buyukten_kucuge(Dugum *kok){
	if(kok != NULL){
		buyukten_kucuge(kok->sag);
		printf("%4d ",kok->icerik);
		buyukten_kucuge(kok->sol);
	}
}

int eleman_sayisi(Dugum *kok){
	if(kok == NULL) return 0;
	else if(kok->icerik > 15){
		return 1+eleman_sayisi(kok->sol)+eleman_sayisi(kok->sag);
	}
	else return eleman_sayisi(kok->sol)+eleman_sayisi(kok->sag);
}

void inorder(Agac *agac){
	if(agac == NULL) return ;
	inorder_yardimci(agac->kok);
	printf("\n");
}

void preorder_yardimci(Dugum *kok){
	if(kok == NULL) return ;
	printf("%4d ",kok->icerik);
	preorder_yardimci(kok->sol);
	preorder_yardimci(kok->sag);
}

void preorder(Agac *agac){
	if(agac == NULL) return ;
	preorder_yardimci(agac->kok);
	printf("\n");
}

void postorder_yardimci(Dugum *kok){
	if(kok == NULL) return ;
	postorder_yardimci(kok->sol);
	postorder_yardimci(kok->sag);
	printf("%4d ",kok->icerik);
}

void postorder(Agac *agac){
	if(agac == NULL) return;
	postorder_yardimci(agac->kok);
	printf("\n");
}

void yoket(Dugum **kok){
	if(*kok != NULL){
		yoket(&(*kok)->sol);
		yoket(&(*kok)->sag);
		free(*kok);
		*kok = NULL;
	}
}

int foo(Dugum *kok){
	if(kok == NULL) return 0;
	else if(kok->sol != NULL || kok->sag != NULL)
		return 1+foo(kok->sol)+foo(kok->sag);
	else return 0;
}

int yaprak_sayisi(Dugum *kok){
	if(kok == NULL) return 0;
	else if(kok->sol == NULL && kok->sag == NULL) return 1;
	else return yaprak_sayisi(kok->sol)+yaprak_sayisi(kok->sag);
}

int tek_cocuklu_dugum_sayisi(Dugum *kok){
	/*if(kok == NULL) return 0;
	else return tek_cocuklu_dugum_sayisi(kok->sol)+tek_cocuklu_dugum_sayisi(kok->sag);
	if(kok->sol == NULL && kok->sag != NULL) return 1;
	else if(kok->sag == NULL && kok->sol != NULL) return 1;*/
	if(kok == NULL) return 0;
	else if((kok->sol == NULL && kok->sag != NULL) || (kok->sag == NULL && kok->sol != NULL))
		return 1+tek_cocuklu_dugum_sayisi(kok->sol)+tek_cocuklu_dugum_sayisi(kok->sag);
	else return tek_cocuklu_dugum_sayisi(kok->sol)+tek_cocuklu_dugum_sayisi(kok->sag);
	//else return 0;
}

Dugum* kardes_bul(Dugum *kok,Dugum *a){
	Dugum *once , *ileri = kok;
	while(ileri != NULL){
		once = ileri;
		if(ileri->icerik < a->icerik){
			ileri = ileri->sag;
		}else ileri = ileri->sol;
		if(ileri == a && once->icerik > ileri->icerik){
			return once->sag;
		}
		else if(once->icerik < ileri->icerik){
			return once->sol;
		}
	}
}

Dugum* en_buyuk_bul(Dugum *kok){
	while(kok->sag != NULL){
		kok = kok->sag;
	}
	return kok;
}

int agac_topla(Dugum *kok){
	int toplam = 0;
	if(kok != NULL){
		toplam += kok->icerik;
		toplam += agac_topla(kok->sol);
		toplam += agac_topla(kok->sag);
	}
	return toplam;
}

/*int foo(Dugum *kok){
	if(kok == NULL) return 0;
	else if(kok->sol != NULL || kok->sag != NULL)
		return 1+foo(kok->sol)+foo(kok->sag);
	else return 0;
}*/ 

int max(int a,int b){
	return a > b ? a : b;
}

int derinlik(Dugum *kok){
	if(kok == NULL) return 0;
	else return max(derinlik(kok->sol),derinlik(kok->sag))+1;
	return 0;
}

int toplam_derinlik(Dugum *kok){
	int toplam = 0;
	if(kok == NULL) return 0;
	toplam += max(derinlik(kok->sol),derinlik(kok->sag))+1;
	return toplam;
}

int iki_cocuklu_dugum_sayisi(Dugum *kok){
	if(kok == NULL) return 0;
	else if(kok->sol != NULL && kok->sag != NULL)
		return 1+iki_cocuklu_dugum_sayisi(kok->sol)+iki_cocuklu_dugum_sayisi(kok->sag);
	/*if(kok->sol == NULL || kok->sag == NULL)
		return iki_cocuklu_dugum_sayisi(kok->sol)+iki_cocuklu_dugum_sayisi(kok->sag);*/
	else return iki_cocuklu_dugum_sayisi(kok->sol)+iki_cocuklu_dugum_sayisi(kok->sag);
}

void agac_bosmu(Dugum *kok){
	if(kok == NULL)
		printf("Agac bostur");
	else printf("Agac bos degildir");
}

int sayidan_buyuk_olan_sayilar(Dugum *kok,int sayi){
	if(kok == NULL) return 0;
	else if(kok->icerik > sayi)
		return 1+sayidan_buyuk_olan_sayilar(kok->sol,sayi)+sayidan_buyuk_olan_sayilar(kok->sag,sayi);
	else return sayidan_buyuk_olan_sayilar(kok->sol,sayi)+sayidan_buyuk_olan_sayilar(kok->sag,sayi);
}

void print_postorder(Dugum *kok){
	if(kok != NULL){
		print_postorder(kok->sag);
		printf("%d ",kok->icerik);
		print_postorder(kok->sol);
	}
}

/*int ilk n_dugumlu_degerlerin_toplami(Dugum *kok,n){
	if( kok!= NULL){
		ilk_n_dugumlu_degerlerin_toplami(kok->sag,n);
		
	}
}*/

int main(){
	Agac *root;
	ikili_arama_agaci_olustur(&root);
	ekle(root,100);
    ekle(root,50);
    ekle(root,200);
    ekle(root,25);
    ekle(root,75);
    ekle(root,20);
    ekle(root,35);
    ekle(root,98);
    ekle(root,99);
    ekle(root,500);
    ekle(root,400);
    ekle(root,300);
    ekle(root,210);
    ekle(root,375);
    ekle(root,30);
    ekle(root,173);
    print_postorder(root->kok);
    //preorder_yardimci(root->kok);
    //printf("42 den buyuk olan sayilar = %d",sayidan_buyuk_olan_sayilar(root->kok,42));
    /*preorder_yardimci(root->kok);
    yoket(&root->kok);
    preorder_yardimci(root->kok);
    agac_bosmu(root->kok);*/
    //preorder_yardimci(root->kok);
	/*ekle(root,20);
	//ekle(root,15);
	//ekle(root,10);
	ekle(root,40);
	ekle(root,30);
	ekle(root,45);*/
	//printf("iki cocuklu dugum sayisi = %d",iki_cocuklu_dugum_sayisi(root->kok));
	/*printf("%d\n",derinlik(root->kok));
	printf("Derinliklerin toplami = %d",toplam_derinlik(root->kok));
	/*ekle(root,35);
	ekle(root,3);
	ekle(root,7);
	ekle(root,48);
	ekle(root,50);
	ekle(root,65);
	printf("%d\n",derinlik(root->kok));
	/*ekle(root,91);
	ekle(root,9);
	ekle(root,24);
	ekle(root,94);
	ekle(root,59);
	ekle(root,33);
	ekle(root,49);*/
	//preorder_yardimci(root->kok);
	//printf("Agaclarin toplami = %d",agac_topla(root->kok));
	//printf("%d",root->kok->icerik);
	//printf("\n%d",tek_cocuklu_dugum_sayisi(root->kok));
	/*if(root->kok == NULL){
		printf("NULL");
	}
	else printf("NULL degil");*/
	//printf("En buyuk sayinin kardesinin icerigi = %d",kardes_bul(root->kok,en_buyuk_bul(root->kok))->icerik);
	//printf("Agactaki en buyuk eleman = %d",en_buyuk_bul(root->kok)->icerik);
	//printf("Tek cocuklu dugum sayisi = %d",tek_cocuklu_dugum_sayisi(root->kok));
	//ekle(root,65);
	//inorder_yardimci(root->kok);
	//preorder_yardimci(root->kok);
	/*ekle(root,40);
	ekle(root,20);
	ekle(root,10);
	ekle(root,30);
	ekle(root,50);
	ekle(root,45);
	ekle(root,65);*/
	/*ekle(root,8);
	ekle(root,4);
	ekle(root,12);
	ekle(root,2);
	ekle(root,6);
	ekle(root,1);
	ekle(root,3);
	ekle(root,5);
	ekle(root,7);
	ekle(root,10);
	ekle(root,14);
	ekle(root,9);
	ekle(root,11);
	ekle(root,13);
	ekle(root,15);
	ekle(root,9);
	ekle(root,5);
	ekle(root,18);
	ekle(root,2);
	ekle(root,6);
	ekle(root,15);
	ekle(root,19);
	ekle(root,13);
	ekle(root,17);
	buyukten_kucuge(root->kok);
	printf("\n");
	//ekle(root,1);
	//ekle(root,15);
	//ekle(root,13);
	//ekle(root,18);
	inorder_yardimci(root->kok);
	printf("\n");
	preorder_yardimci(root->kok);
	printf("\n");
	postorder_yardimci(root->kok);
	
	//printf("Eleman sayisi = %d",eleman_sayisi(root->kok));
	//inorder_yardimci(root->kok);
	//inorder(root);
	//printf("%d",foo(root->kok));
	//printf("Agactaki yaprak sayisi = %d",yaprak_sayisi(root->kok));
	//postorder_yardimci(root->kok);
	//inorder_yardimci(root->kok);
	/*preorder(root);
	postorder(root);
	//yoket(&(root->kok));
	inorder(root);*/
}
