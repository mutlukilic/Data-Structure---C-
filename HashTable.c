#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SENTINEL -20000000

struct CELL{
	char *anahtar;
	struct CELL *next;
};

struct table_node{
	int counter;
	struct CELL *header;
};

struct hash_tablosu{
	struct table_node *tablo_basi;
	int tablo_uzunlugu;
	int multiplier;
};

int lookup(char *anahtar,struct CELL *l){
	if( l == NULL) return 0;
	else if(!strcmp(anahtar,l->anahtar)) return 1;
	else return lookup(anahtar,l->next);
}

void initialize_hash_table(struct hash_tablosu **hash_table,int multiplier,int table_size){
	int i;
	*hash_table = (struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
	if( *hash_table == NULL){
		printf("Hash tablosu icin yer ayrilamadi...HATA!!!");
		exit(1);
	}
	(*hash_table)->tablo_basi = (struct table_node*)malloc(table_size*sizeof(struct table_node));
	if( (*hash_table)->tablo_basi == NULL){
		printf("Hash tablosu icin yer ayrilamadi...HATA!!!");
		exit(1);
	}
	(*hash_table)->tablo_uzunlugu = table_size;
	(*hash_table)->multiplier = multiplier;
	for(i = 0;i < table_size;i++){
		((*hash_table)->tablo_basi+i)->counter = 0;
		((*hash_table)->tablo_basi+i)->header = NULL;
	}
}

void print_list(struct CELL *l){ //recursive
	if( l != NULL){
		printf("%s ",l->anahtar);//preorder
		print_list(l->next);
	}
}

void print_hash_table(struct hash_tablosu *hash_table){
	if( hash_table ){
		int index;
		printf("-----HASH TABLOSU-----\n");
		for(index = 0;index < hash_table->tablo_uzunlugu;index++){
			printf("%5d : (%2d ) ",index,(hash_table->tablo_basi+index)->counter);
			print_list((hash_table->tablo_basi+index)->header);
			//printf("-> NULL");
			printf("\n");
		}
	}
	else printf("Hash tablosu bos...\n");
}

unsigned hash(char *anahtar,int multiplier,int table_size){
	int i = 0;
	unsigned int value = 0;
	while(anahtar[i]){
		value = (anahtar[i++] + multiplier*value) % table_size; //ASCII Tablosu
	}
	return value;
}

int insert(char *anahtar,struct CELL **l){ //Özyinelemeli ( Recursive ) 
	if( (*l) == NULL){
		*l = (struct CELL*)malloc(sizeof(struct CELL));
		(*l)->anahtar = (char*)malloc((strlen(anahtar)+1)*sizeof(char));
		strcpy((*l)->anahtar,anahtar);
		(*l)->next = NULL;
		return 1;
	}
	else if(strcmp(anahtar,(*l)->anahtar)){
		return insert(anahtar,&((*l)->next));
	}
	else return 0;
}

void insert_hash_table(struct hash_tablosu *hash_table,char *anahtar){
	int hash_index = hash(anahtar,hash_table->multiplier,hash_table->tablo_uzunlugu);
	if(insert(anahtar,&((hash_table->tablo_basi+hash_index)->header))){
		(hash_table->tablo_basi + hash_index)->counter++;
	}
}

void liste_yok_et(struct CELL **liste_basi){
	struct CELL *onceki;
	while( *liste_basi ){
		onceki = *liste_basi;
		*liste_basi = (*liste_basi)->next;
		free(onceki->anahtar);
		free(onceki);
	}
}

void hash_table_yok_et(struct hash_tablosu **hash_table){
	int index;
	if(*hash_table){
		for(index = 0;index < (*hash_table)->tablo_uzunlugu;index++){
			liste_yok_et(&((*hash_table)->tablo_basi+index)->header);
		}
		free((*hash_table)->tablo_basi);
		free(*hash_table);
	}
	*hash_table = NULL;
}

void hash_table_buyut(struct hash_tablosu **htable,int multiplier,int tablo_uzunlugu){
	int i;
	struct CELL *liste_basi;
	struct hash_tablosu *yeni_tablo;
	if( *htable ){
		initialize_hash_table(&yeni_tablo,multiplier,tablo_uzunlugu);
		for(i = 0;i < (*htable)->tablo_uzunlugu;i++){
			liste_basi = ((*htable)->tablo_basi+i)->header;
			while( liste_basi != NULL ){
				insert_hash_table(yeni_tablo,liste_basi->anahtar);
				liste_basi = liste_basi->next;
			}
		}
		hash_table_yok_et(&(*htable));
		//hash_table_yok_et(htable);
		*htable = yeni_tablo;
	}
}

int delete_dugum_liste(struct CELL **header,char *anahtar){
	struct CELL *simdiki, *onceki;
	simdiki = *header;
	while(simdiki && strcmp(simdiki->anahtar,anahtar)){
		onceki = simdiki;
		simdiki = simdiki->next;
	}
	if(!simdiki) return 0;
	if(simdiki == *header){
		*header = (*header)->next;
	}
	else onceki->next = simdiki->next;
	free(simdiki->anahtar);
	free(simdiki);
	return 1;
}

void delete_hash_table(struct hash_tablosu *table,char *anahtar){
	int hash_index = hash(anahtar,table->multiplier,table->tablo_uzunlugu);
	if(delete_dugum_liste(&((table->tablo_basi+hash_index)->header),anahtar)){
		(table->tablo_basi+hash_index)->counter--;
	}
}

int indis_bul(struct hash_tablosu *htable,char *anahtar){
	int hash_index = hash(anahtar,htable->multiplier,htable->tablo_uzunlugu);
	struct CELL *root = (htable->tablo_basi+hash_index)->header;
	if(root == NULL) return SENTINEL;
	int index = 0;
	while(strcmp(root->anahtar,anahtar)){
		index++;
		root = root->next;
	}
	return index;
}

struct CELL* dugum_bul(struct hash_tablosu *htable,char *anahtar){
	int hash_index = hash(anahtar,htable->multiplier,htable->tablo_uzunlugu);
	struct CELL *root = (htable->tablo_basi+hash_index)->header;
	if( root == NULL ) return NULL;
	while(strcmp(root->anahtar,anahtar)){
		root = root->next;
	}
	return root;
}

struct CELL* indisteki_dugum(struct hash_tablosu *htable,int hash_index,int index){
	struct CELL *root = (htable->tablo_basi+hash_index)->header;
	int j = 0;
	while(j != index){
		j++; root = root->next;
	}
	/*while(strcmp(root->anahtar,anahtar)){
		root = root->next;
	}*/
	if(root == NULL) return NULL;
	return root;
}

int count(struct hash_tablosu *htable,char *anahtar){
	int hash_index = hash(anahtar,htable->multiplier,htable->tablo_uzunlugu);
	struct CELL *root = (htable->tablo_basi+hash_index)->header;
	if(root == NULL) return SENTINEL;
	int adet = 0;
	while(root != NULL){
		if(!strcmp(root->anahtar,anahtar)) adet++;
		root = root->next;
	}
	return adet;
}

int bas_harf_ile_baslayanlarin_sayisi(struct hash_tablosu *htable,char *anahtar){
	int index;
	int adet = 0; 
	struct CELL *root;
	if(htable){
		for(index = 0;index < htable->tablo_uzunlugu;index++){
			root = (htable->tablo_basi+index)->header;
			while(root != NULL){
				if(root->anahtar[0] == anahtar[0]){
					adet++;
				}
				root = root->next;
			}	
		}
	}
	else printf("Hash tablosu bostur\n");
	return adet;
}

int harf_sayisi(struct hash_tablosu *htable,char *anahtar){
	int adet = 0, i;
	struct CELL *root;
	if( htable ){
		int index;
		for(index = 0;index < htable->tablo_uzunlugu;index++){
			root = (htable->tablo_basi+index)->header;
			while(root != NULL){
				for(i = 0;i < strlen(root->anahtar)+1;i++){
					if(root->anahtar[i] == anahtar[0]){
						adet++;
					}
				}
				root = root->next;
			}
		}
	}
	else printf("tabloda eleman yoktur\n");
	return adet;
}

int harf_sayisi_2(struct hash_tablosu *htable,char *anahtar){
	int adet = 0, i;
	if( htable ){
		int index;
		for(index = 0;index < htable->tablo_uzunlugu;index++){
			while((htable->tablo_basi+index)->header != NULL){
				for(i = 0;i < strlen(((htable->tablo_basi+index)->header)->anahtar)+1;i++){
					if(((htable->tablo_basi+index)->header)->anahtar[i] == anahtar[0]){
						adet++;
					}
				}
				(htable->tablo_basi+index)->header = (htable->tablo_basi+index)->header->next;
			}
		}
	}
	else printf("tabloda eleman yoktur\n");
	return adet;
}

int count_2(struct hash_tablosu *htable,char *anahtar){
	int hash_index = hash(anahtar,htable->multiplier,htable->tablo_uzunlugu);
	return lookup(anahtar,(htable->tablo_basi+hash_index)->header);
}

/*int ilkini_sil(struct hash_tablosu *htable,char *anahtar){
	if( htable ){
		int index;
		struct CELL *root,**temp,*once;
		for(index = 0;index < htable->tablo_uzunlugu;index++){
			*temp = &(htable->tablo_basi+index)->header;
			root = *temp;
			while(root != NULL && root->anahtar[0] != anahtar[0]){
				once = root;
				root = root->next;
			}
			if(root == NULL) continue;
			if(root == temp) *temp = (*temp)->next;
			else once->next = root->next;
			free(root->anahtar);
			free(root);
		}
	}
	else printf("Hash tablosu bostur\n"); return;
}*/

void liste_ters_cevir(struct CELL **liste_basi){
	struct CELL *a = NULL , *b;
	while( (*liste_basi) != NULL){
		b = (*liste_basi);
		(*liste_basi) = (*liste_basi)->next;
		b->next = a;
		a = b;
	}
	*liste_basi = a;
}

void tablo_ters_cevir(struct hash_tablosu *htable){
	if( htable ){
		int index;
		for(index = 0;index < htable->tablo_uzunlugu;index++){
			liste_ters_cevir(&(htable->tablo_basi+index)->header);
		}
	}
	else printf("Hash table bostur");
}

/*void tablo_ters_cevir_2(struct hash_tablosu *htable){
	if( htable ){
		int index;
		struct CELL *a,*b;
		for(index = 0;index < htable->tablo_uzunlugu;index++){
			int **header = &(htable->tablo_basi+index)->header;
			while((*header) != NULL){
				b = (*header);
				(*header) = (*header)->next;
				b->next = a;
				a = b;
			}
			*header = a;
		}
	}
	else printf("Hash table bostur");
}*/

void hash_yable_buyut_2(struct hash_tablosu **htable,int multiplier,int table_size){
	if( *htable ){
		struct CELL *root;
		struct hash_tablosu *new_htable;
		initialize_hash_table(&new_htable,multiplier,table_size);
		for(int index = 0;index < (*htable)->tablo_uzunlugu;index++){
			root = ((*htable)->tablo_basi+index)->header;
			while(root != NULL){
				insert_hash_table(new_htable,root->anahtar);
				root = root->next;
			}
		}
		hash_table_yok_et(&(*htable));
		*htable = new_htable;
	}
	else printf("Hash table zaten bostur");
}

int main(int argc, char *argv[]){
	struct hash_tablosu *htable = NULL;
	initialize_hash_table(&htable,3,5);
	print_hash_table(htable);
	
	insert_hash_table(htable,"C");
	//insert_hash_table(htable,"C");
	insert_hash_table(htable,"Python");
	insert_hash_table(htable,"C++");
	insert_hash_table(htable,"Java");
	insert_hash_table(htable,"C#");
	insert_hash_table(htable,"Go");
	insert_hash_table(htable,"Ruby");
	insert_hash_table(htable,"Perl");
	insert_hash_table(htable,"HTML");
	insert_hash_table(htable,"PHP");
	insert_hash_table(htable,"CSS");
	insert_hash_table(htable,"SQL");
	insert_hash_table(htable,"MySQL");
	insert_hash_table(htable,"D");
	insert_hash_table(htable,"Pascal");
	print_hash_table(htable);
	tablo_ters_cevir(htable);
	print_hash_table(htable);
	tablo_ters_cevir(htable);
	print_hash_table(htable);
	tablo_ters_cevir_2(htable);
	print_hash_table(htable);
	//printf("Harf sayisi = %d",harf_sayisi(htable,"a"));
	//ilkini_sil(htable,"C");
	//print_hash_table(htable);
	//printf("aaaadet sayisi = %d"+count(htable,"Java"));
	//ilkini_sil(htable,"C");
	///print_hash_table(htable);
	//printf("Dugum = %s",dugum_bul(htable,"C")->anahtar);
	//printf("Java %d.indistedir",indis_bul(htable,"Java"));
	//printf("%s ",indisteki_dugum(htable,2,2)->anahtar);
	/*printf("C ile baslayanlarin sayisi = %d\n",bas_harf_ile_baslayanlarin_sayisi(htable,"C"));
	printf("# harfinden tabloda %d adet vardir.\n",harf_sayisi_2(htable,"#"));
	ilkini_sil(htable,"C");
	print_hash_table(htable);
	//printf("%s ",dugum_bul(htable,"Java")->anahtar);
	/*printf("Java %d. indistedir\n",indis_bul(htable,"Java"));
	printf("C %d.indistedir\n",indis_bul(htable,"C"));
	printf("Java anahtarindan %d adet vardir \n",count_2(htable,"Java"));
	//printf("\nC %d.indistedir",indis_bul(htable,"C1"));
	/*delete_hash_table(htable,"C#");
	print_hash_table(htable);
	delete_hash_table(htable,"Java");
	print_hash_table(htable);
	//hash_table_buyut(&htable,3,7);
	//print_hash_table(htable);
	//hash_table_yok_et(&htable);
	//print_hash_table(htable);
	//delete_hash_table(htable,"C#");
	/*insert_hash_table(htable,"CSS");
	insert_hash_table(htable,"+");
	insert_hash_table(htable,"#");
	insert_hash_table(htable,"-");
	insert_hash_table(htable,"HTML");*/
	//hash_table_yok_et(&htable);
	//print_hash_table(htable);
	//insert_hash_table(htable,"C#");
	//print_hash_table(htable);
	return 0;
}
