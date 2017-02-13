#include <stdio.h>
#include <stdlib.h>

struct yigin{
	int *dizi;
	int ust;
	int kapasite;
};
typedef struct yigin Yigin;

Yigin* kapasiteyi_arttir(Yigin**,int);

Yigin* yigin_olustur(int kapasite){
	if(kapasite <= 0){
		printf("kapasite negatif olamaz...");
		exit(1);
	}
	Yigin *yeni = (Yigin*)malloc(sizeof(Yigin));
	yeni->dizi = (int*)malloc(kapasite*sizeof(int));
	yeni->ust = -1;
	yeni->kapasite = kapasite;
	return yeni;
}

void yigin_olustur_parametre_ile(int kapasite,Yigin **yigin){
	if(kapasite <= 0){
		printf("kapasite negatif olamaz...");
		return;
	}
	(*yigin) = (Yigin*)malloc(sizeof(Yigin));
	(*yigin)->dizi = (int*)malloc(kapasite*sizeof(int));
	(*yigin)->ust = -1;
	(*yigin)->kapasite = kapasite;
}

int yigin_bosmu(Yigin *yigin){
	if(yigin->ust == -1) return 1;
	return 0;
}

int yigin_dolumu(Yigin *yigin){
	if(yigin->ust = yigin->kapasite-1) return 1;
	return 0;
}

void yigin_ekle(int eleman,Yigin **yigin){
	if(yigin_dolumu){
		*yigin = kapasiteyi_arttir(yigin,2);
	}
	(*yigin)->dizi[++(*yigin)->ust] = eleman;
}

void yigin_yaz(Yigin *yigin){
	if(yigin == NULL){
		printf("Yigin icin yer ayrilmamistir...\n");
		return;
	}
	printf("Yiginin kapasitesi        : %4d\n",yigin->kapasite);
	printf("Yigindaki eleman sayisi   : %4d\n",yigin->ust+1);
	int i;
	for(i=yigin->ust;i >= 0;i--){
		printf("%4d ",yigin->dizi[i]);
	}
	printf("\n");
}

int yigin_eleman_sil(Yigin **yigin){
	if(yigin_bosmu(*yigin)) return 0;
	return (*yigin)->dizi[(*yigin)->ust--];
}

void yigin_yok_et(Yigin **yigin){
	free((*yigin)->dizi);
	free(*yigin);
	*yigin = NULL;
}

Yigin* kapasiteyi_arttir(Yigin **yigin,int kackat){
	Yigin *yeni = yigin_olustur(kackat*(*yigin)->kapasite);
	int i;
	for(i=0;i<=(*yigin)->ust;i++){
		yeni->dizi[i] = (*yigin)->dizi[i];
	}
	yeni->ust = (*yigin)->ust;
	yigin_yok_et(&(*yigin));
	return yeni;
}

void kapasiteyi_arttir_yeni(Yigin **yigin,int kackat){
	Yigin *yeni = yigin_olustur(kackat*(*yigin)->kapasite);
	int i;
	for(i=0;i<=(*yigin)->kapasite;i++){
		yeni->dizi[i] = (*yigin)->dizi[i];
	}
	yeni->ust = (*yigin)->ust;
	yigin_yok_et(&(*yigin));
	(*yigin) = yeni;
}

int main(){
	Yigin *yigin = yigin_olustur(10);
	for(int i = 1;i <= 10;i++){
		yigin_ekle(2*i,&yigin);
	}
	yigin_yaz(yigin);
	yigin_eleman_sil(&yigin);
	yigin_yaz(yigin);
	yigin_yok_et(&yigin);
	yigin_yaz(yigin);
	yigin = yigin_olustur(4);
	for(int i = 1;i<=4;i++){
		yigin_ekle(2*i,&yigin);
	}
	yigin_yaz(yigin);
	kapasiteyi_arttir(&yigin,3);
	yigin_yaz(yigin);
}
