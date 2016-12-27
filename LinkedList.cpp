#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct hucre{
	int icerik;
	struct hucre *sonraki;
};
typedef struct hucre Hucre;

Hucre* hucre_olustur(int icerik){
	Hucre *yeni = (Hucre*)malloc(sizeof(Hucre));
	if(yeni == NULL){
		printf("Yeteri kadar alan yok");
		exit(1);
	}
	yeni->icerik = icerik;
	yeni->sonraki = NULL;
	return yeni;
}

void listenin_basina_ekle(int icerik,Hucre **liste_basi){
	Hucre *yeni = hucre_olustur(icerik);
	yeni->sonraki = (*liste_basi);
	*liste_basi = yeni;
}

void listenin_sonuna_ekle(int icerik,Hucre **liste_basi){
	Hucre *yeni = hucre_olustur(icerik);
	if(*liste_basi == NULL)
		*liste_basi = yeni;
	else{
		Hucre *r = (*liste_basi);
		while(r->sonraki != NULL){
			r = r->sonraki;
		}
		r->sonraki = yeni;
	}
}

void liste_yaz(Hucre *liste_basi){
	while(liste_basi != NULL){
		printf("%d -> ",liste_basi->icerik);
		liste_basi = liste_basi->sonraki;
	}
	printf("NULL\n");
}

void liste_yaz_recursive(Hucre *liste_basi){
	if(liste_basi != NULL){
		printf("%d -> ",liste_basi->icerik);
		liste_yaz_recursive(liste_basi->sonraki);
	}
}

void tersten_liste_yaz_recursive(Hucre *liste_basi){
	if(liste_basi != NULL){
		tersten_liste_yaz_recursive(liste_basi->sonraki);
		printf("%d -> ",liste_basi->icerik);
	}
	else
		printf("NULL\n");
}

void liste_yok_et(Hucre **liste_basi){
	Hucre *temp;
	while(*liste_basi != NULL){
		temp = (*liste_basi);
		*liste_basi = (*liste_basi)->sonraki;
		free(temp);
	}
}

void liste_sirali_ekle(int icerik,Hucre **liste_basi){
	Hucre *once,*sonra,*eklenen;
	sonra = (*liste_basi);
	while(sonra != NULL && (sonra->icerik <= icerik)){
		if(sonra->icerik == icerik)return;
		once = sonra;
		sonra = sonra->sonraki;
	}
	eklenen = hucre_olustur(icerik);
	if(sonra == (*liste_basi)){
		eklenen->sonraki = (*liste_basi);
		*liste_basi = eklenen;
	}else{
		once->sonraki = eklenen;
		eklenen->sonraki = sonra;
	}
}

void liste_eleman_sil(int icerik,Hucre **liste_basi){
	Hucre *temp = (*liste_basi);
	Hucre *once;
	while(temp != NULL && temp->icerik != icerik){
		once = temp;
		temp = temp->sonraki;
	}
	if(temp == NULL)return;
	else{
		if(temp == (*liste_basi)) *liste_basi = (*liste_basi)->sonraki;
		else once->sonraki = temp->sonraki;
		free(temp);
	}
}

void liste_sirala(Hucre **liste_basi){
	if(*liste_basi == NULL || (*liste_basi)->sonraki == NULL)return;
	Hucre *a,*b,*c,*d;
	d = (*liste_basi)->sonraki;
	(*liste_basi)->sonraki = NULL;
	while(d != NULL){
		c = d;
		d = d->sonraki;
		b = (*liste_basi);
		while(b != NULL && b->icerik < c->icerik){
			a = b;
			b = b->sonraki;
		}
		if(b == (*liste_basi)){
			c->sonraki = (*liste_basi);
			*liste_basi = c;
		}else{
			a->sonraki = c;
			c->sonraki = b;
		}
	}
}

void liste_ters_cevir(Hucre **liste_basi){
	Hucre *a = NULL,*b;
	while((*liste_basi) != NULL){
		b = (*liste_basi);
		(*liste_basi) = (*liste_basi)->sonraki;
		b->sonraki = a;
		a = b;
	}
	*liste_basi = a;
}

/*Dugum* listede_enbuyuk_bul(Hucre *liste_basi){
	/*if(liste_basi == NULL){
		printf("Listede eleman yoktur...exit...");
		exit(1);
	}
	Hucre *temp = liste_basi;
	int enb = 0;
	enb = temp->icerik;
	printf("Listenin ilk elemani = %d",enb);
	while(temp != NULL){
		temp = temp->sonraki;
		if(temp->icerik > enb)
			enb = temp->icerik;
	}
	//return enb;
	liste_sirala(&liste_basi);
	Dugum *temp = liste_basi;
	while(temp->ileri != NULL)
		temp = temp->ileri;
	return temp;
}*/

Hucre* i_indisteki_eleman(Hucre *liste_basi,int i){
	int j = 0;
	Hucre *temp = liste_basi;
	while(temp != NULL && j < i){
		temp = temp->sonraki;
		j++;
	}
	return temp;
}

Hucre* listedeki_enbuyuk_eleman(Hucre *liste_basi){
	Hucre *temp = liste_basi;
	Hucre *enbptr;
	int enb = temp->icerik;
	while(temp){
		if(temp->icerik > enb){
			enbptr = temp;
			enb = temp->icerik;
		}
		temp = temp->sonraki;
	}
	return enbptr;
}

Hucre* listedeki_enkucuk_eleman(Hucre *liste_basi){
	Hucre *temp = liste_basi;
	Hucre *enkptr;
	int enk = temp->icerik;
	while(temp){
		if(temp->icerik < enk){
			enkptr = temp;
			enk = temp->icerik;
		}
		temp = temp->sonraki;
	}
	return enkptr;
}

Hucre* liste_birlestir(Hucre *liste_basi1,Hucre *liste_basi2){
	Hucre *yeni_liste = liste_basi1;
	Hucre *temp = yeni_liste;
	while(temp->sonraki != NULL){
		temp = temp->sonraki;
	}
	temp->sonraki = liste_basi2;
	return yeni_liste;
}

int listedeki_eleman_sayisi(Hucre *liste_basi){
	//Hucre *temp = liste_basi;
	int eleman_sayisi = 0;
	while(liste_basi){
		eleman_sayisi++;
		liste_basi = liste_basi->sonraki;
	}
	return eleman_sayisi;
}

int listedeki_eleman_sayisi2(Hucre *liste_basi){
	Hucre *temp = liste_basi;
	int eleman_sayisi = 0;
	while(temp != NULL){
		eleman_sayisi++;
		temp = temp->sonraki;
	}
	return eleman_sayisi;
}

int listedeki_ciftlerin_sayisi(Hucre *liste_basi){
	int ciftlerin_sayisi = 0;
	while(liste_basi){
		if(liste_basi->icerik % 2 == 0)
			ciftlerin_sayisi++;
		liste_basi = liste_basi->sonraki;
	}
	return ciftlerin_sayisi;
}

int listedeki_teklerin_sayisi(Hucre *liste_basi){
	int teklerin_sayisi = 0;
	while(liste_basi){
		if(liste_basi->icerik %2 != 0)
			teklerin_sayisi++;
		liste_basi = liste_basi->sonraki;
	}
	return teklerin_sayisi;
}

void listedeki_ciftleri_sil(Hucre **liste_basi){
	Hucre *temp = (*liste_basi);
	Hucre *once,*cift;
	
	while(1){
		cift = temp;
		while(cift != NULL && cift->icerik % 2 != 0){
			once = cift;
			cift = cift->sonraki;
		}
		if(cift == NULL)break;
		else{
			if(cift == (*liste_basi)){
				*liste_basi = (*liste_basi)->sonraki;
				temp = (*liste_basi);
			}
			else{
				once->sonraki = cift->sonraki;
				temp = once->sonraki;
			}
			free(cift);
		}
		/*if(cift == (*liste_basi))
			*liste_basi = (*liste_basi)->sonraki;
		else
			once->sonraki = cift->sonraki;
		free(cift);*/
	}
}

void listedeki_tekleri_sil(Hucre **liste_basi){
	Hucre *temp = (*liste_basi);
	Hucre *once,*tek;
	while(1){
		tek = temp;
		while(tek != NULL && tek->icerik % 2 == 0){
			once = tek;
			tek = tek->sonraki;
		}
		if(tek == NULL)break;
		else{
			if(tek == (*liste_basi)){
				(*liste_basi) = (*liste_basi)->sonraki;
				temp = (*liste_basi);
			}else{
				once->sonraki = tek->sonraki;
				temp = once->sonraki;
			}
			free(tek);
		}
	}
}

int eleman_asalmi(Hucre *temp){
	int i;
	for(i = 2;i <= sqrt(temp->icerik);i++){
		if(temp->icerik % i == 0) return 0;
	}
	return 1;
}

void listedeki_asal_sayilari_sil(Hucre **liste_basi){
	Hucre *once;
	Hucre *asal = (*liste_basi);
	while(1){
		if(asal == NULL) break;
		if(eleman_asalmi(asal) && asal == (*liste_basi)){
			(*liste_basi) = (*liste_basi)->sonraki;
			free(asal);
			asal = (*liste_basi);
		}else if(eleman_asalmi(asal)){
			once->sonraki = asal->sonraki;
			free(asal);
			asal = once->sonraki;
		}else{
			once = asal;
			asal = asal->sonraki;
		}
	}
}

int icerik_ciftmi(Hucre *hucre){
	if(hucre->icerik % 2 == 0) return 1;
	return 0;
}

int ciftleri_tekleri_ayir(Hucre **cift_liste,Hucre **tek_liste,Hucre *liste_basi){
	while(liste_basi != NULL){
		if(icerik_ciftmi(liste_basi)){
			listenin_basina_ekle(liste_basi->icerik,&(*cift_liste));
		}else{
			listenin_basina_ekle(liste_basi->icerik,&(*tek_liste));
		}
		liste_basi = liste_basi->sonraki;
	}
}

int main(){
	Hucre *root = NULL;
	/*Hucre *root2 = NULL;
	Hucre *root3 = NULL;
	listenin_basina_ekle(1,&root);
	listenin_basina_ekle(2,&root);
	listenin_basina_ekle(3,&root);
	listenin_basina_ekle(4,&root);
	listenin_basina_ekle(5,&root);
	listenin_basina_ekle(1,&root2);
	listenin_basina_ekle(2,&root2);
	listenin_basina_ekle(3,&root2);
	//root3 = liste_birlestir(root,root2);
	listenin_basina_ekle(3,&root3);
	listenin_basina_ekle(4,&root3);
	listenin_basina_ekle(5,&root3);
	listenin_basina_ekle(7,&root3);
	listenin_basina_ekle(3,&root3);
	liste_yaz(root3);
	Hucre *cift_listesi = NULL;
	Hucre *tek_listesi = NULL;
	ciftleri_tekleri_ayir(&cift_listesi,&tek_listesi,root3);
	liste_yaz(cift_listesi);
	liste_yaz(tek_listesi);
	//listedeki_asal_sayilari_sil(&root3);
	//liste_yaz(root3);
	/*printf("listebasinin asallik degeri = %d",eleman_asalmi(root3));
	printf("Liste basinin degeri = %d",root3->icerik);*/
	//listedeki_tekleri_sil(&root3);
	//liste_yaz(root3);
	//listedeki_ciftleri_sil(&root3);
	//liste_yaz(root3);
	/*printf("Listedeki eleman sayisi = %d\n",listedeki_eleman_sayisi(root3));
	liste_yaz(root3);
	printf("Listedeki ciftlerin eleman sayisi = %d\n",listedeki_ciftlerin_sayisi(root3));
	printf("Listedeki teklerin eleman sayisi = %d",listedeki_teklerin_sayisi(root3));*/
	/*listenin_sonuna_ekle(2,&root);
	listenin_sonuna_ekle(3,&root);
	listenin_sonuna_ekle(4,&root);
	listenin_sonuna_ekle(5,&root);*/
	//listenin_sonuna_ekle(7,&root);
	//liste_sirala(&root);
	/*liste_sirali_ekle(6,&root);	
	liste_sirali_ekle(5,&root);	
	liste_sirali_ekle(12,&root);	
	liste_sirali_ekle(2,&root);	
	liste_sirali_ekle(3,&root);	
	liste_sirali_ekle(42,&root);*/	
	//liste_yaz(root);
	//liste_ters_cevir(&root);
	//liste_eleman_sil(12,&root);
	/*printf("listenin en buyuk elemani = %d\n",listedeki_enbuyuk_eleman(root)->icerik);
	printf("Listenin 4.indisindeki elemani = %d\n",i_indisteki_eleman(root,4)->icerik);
	printf("Listenin en kucuk elemani = %d\n",listedeki_enkucuk_eleman(root)->icerik);
	liste_yaz(root);*/
	//printf("Listede enbuyuk eleman = %d",listede_enbuyuk_bul(*root)->icerik);
	//printf("Listedeki enbuyuk sayi = %d",listede_enbuyuk_bul(root));
	//liste_yaz_recursive(root);
	//tersten_liste_yaz_recursive(root);
	//liste_yok_et(&root);
	//liste_yaz(root);*/
	liste_sirali_ekle(4,&root);
	liste_sirali_ekle(3,&root);
	liste_yaz(root);
	liste_sirali_ekle(2,&root);
	liste_yaz(root);
	printf("%d \n",i_indisteki_eleman(root,2)->icerik);
	printf("Listedeki eleman sayisi = %d",listedeki_eleman_sayisi2(root));
	return 0;
}
