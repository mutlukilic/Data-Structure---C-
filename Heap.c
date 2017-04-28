#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct dugum{
	int key;
};

struct heap{
	struct dugum *dizi;
	int kapasite;
	int eleman_sayisi;
};

struct heap* heap_olustur(int kapasite){
	struct heap *gecici;
	gecici = (struct heap*)malloc(sizeof(struct heap));
	if( !gecici ){
		printf("Dinamik alan ayirma basarisiz...exit..\n");
		exit(1);
	}
	gecici->dizi = (struct dugum*)malloc(kapasite*sizeof(struct dugum));
	if( !gecici->dizi ){
		printf("Dinamik alan ayirma basarisiz...exit...\n");
		exit(1);
	}
	gecici->kapasite = kapasite;
	gecici->eleman_sayisi = 0;
	return gecici;
}

void create_heap(struct heap **heap,int kapasite){
	*heap = (struct heap*)malloc(sizeof(struct heap));
	if( !(*heap) ){
		printf("Dinamik alan ayirma basarisiz...exit...\n");
		exit(1);
	}
	(*heap)->dizi = (struct dugum*)malloc(kapasite*sizeof(struct dugum));
	if( !(*heap)->dizi ){
		printf("Dinamik alan ayirma basarisiz...exit...\n");
		exit(1);
	}
	(*heap)->kapasite = kapasite;
	(*heap)->eleman_sayisi = 0;
}

void initialize_heap(struct heap *heap,int eleman_sayisi,int aralik){
	int i,j;
	int yeni,cik;
	
	if(eleman_sayisi > heap->kapasite){
		printf("Heap gerekli kapasiteye sahip degil...exit...\n");
		exit(1);
	}
	
	srand(time(NULL));
	heap->dizi[0].key = rand() % aralik;
	for(i = 1;i < eleman_sayisi;i++){
		while(1){
			cik = 1;
			yeni = rand() % aralik;
			for(j = 0;j < i;j++){
				if(heap->dizi[j].key == yeni){
					cik = 0; break;
				}
			}
			if( cik == 0 ) continue;
			heap->dizi[i].key = yeni;
			break;
		}
	}
	heap->eleman_sayisi = eleman_sayisi;
}

void print_heap(struct heap *heap){
	int i;
	for(i = 0;i < heap->eleman_sayisi;i++){
		printf("%4d",heap->dizi[i].key);
	}
	printf("\n");
}

int heap_mi(struct heap *h){
	int i;
	if( !h ) return 1;
	for(i = 0;i < h->eleman_sayisi/2 ; i++){
		if(h->dizi[i].key < h->dizi[2*i+1].key || (2*i+2 < h->eleman_sayisi && h->dizi[i].key < h->dizi[2*i+2].key)){
			return 0;
		}
	}
	return 1;
}

void buble_down(struct heap *heap,int index){
	int sol , sag;
	sol = 2*index+1;
	sag = 2*index+2;
	int temp_key;
	while((sol < heap->eleman_sayisi && heap->dizi[index].key < heap->dizi[sol].key) || (sag < heap->eleman_sayisi && heap->dizi[index].key < heap->dizi[sag].key)){
		if(sag >= heap->eleman_sayisi || heap->dizi[sol].key > heap->dizi[sag].key){
			temp_key = heap->dizi[sol].key;
			heap->dizi[sol].key = heap->dizi[index].key;
			heap->dizi[index].key = temp_key;
			index = 2*index+1;
		}
		else{
			temp_key = heap->dizi[sag].key;
			heap->dizi[sag].key = heap->dizi[index].key;
			heap->dizi[index].key = temp_key;
			index = 2*index+2;
		}
		sol = 2*index+1;
		sag = 2*index+2;
	}
}

void heapify(struct heap *heap){
	int i;
	for(i = heap->eleman_sayisi/2-1;i >= 0;i--){
		buble_down(heap,i);
	}
}

void delete_max(struct heap *heap){
	int temp_key;
	if(heap->eleman_sayisi > 1){
		temp_key = heap->dizi[0].key;
		heap->dizi[0].key = heap->dizi[heap->eleman_sayisi-1].key;
		heap->dizi[heap->eleman_sayisi-1].key = temp_key;
		heap->eleman_sayisi--;
		buble_down(heap,0);
	}
}

void heap_sort(struct heap *heap){
	int i;
	int temp = heap->eleman_sayisi;
	for(i = 1;i < temp;i++) delete_max(heap);
	heap->eleman_sayisi = temp;
}

void heap_sort_2(struct heap *heap){
	int temp = heap->eleman_sayisi;
	int temp_key;
	for(int i = 1;i < temp ; i++){
		if(heap->eleman_sayisi > 1){
			temp_key = heap->dizi[0].key;
			heap->dizi[0].key = heap->dizi[heap->eleman_sayisi-1].key;
			heap->dizi[heap->eleman_sayisi-1].key = temp_key;
			heap->eleman_sayisi--;
			buble_down(heap,0);
		}
	}
	heap->eleman_sayisi = temp;
}

int sirali_mi(struct heap *heap){
	int sayac = 0;
	for(int i = 0;i < heap->eleman_sayisi;i++){
		if(heap->dizi[i].key < heap->dizi[i+1].key){
			sayac++;
		}
	}
	if(sayac == heap->eleman_sayisi-1) return 1;
	return 0;
}

void buble_up(struct heap *heap,int index){
	int parent , temp_key;
	parent = (index-1)/2;
	
	while(parent >= 0 && heap->dizi[parent].key < heap->dizi[index].key){
		temp_key = heap->dizi[parent].key;
		heap->dizi[parent].key = heap->dizi[index].key;
		heap->dizi[index].key = temp_key;
		index = parent;
		parent = (index-1)/2;
	}
}

void heap_insert(struct heap *heap,int key){
	if(heap->eleman_sayisi < heap->kapasite){
		heap->eleman_sayisi++;
		heap->dizi[heap->eleman_sayisi-1].key = key;
		buble_up(heap,heap->eleman_sayisi-1);
	}
}

void heap_birlestir(struct heap *heap,struct heap *heap2){
	for(int i = 0;i < heap2->eleman_sayisi;i++){
		heap_insert(heap,heap2->dizi[i].key);
	}
}

void yok_et_heap(struct heap **heap){
	int i;
	/*for(i = 0;i < (*heap)->eleman_sayisi;i++){
		free((*heap)->dizi[i]);
	}*/
	free(*heap);
	(*heap) = NULL;
}

struct heap* heap_buyut(struct heap *heap,int kapasite){
	struct heap *new_heap;
	new_heap = heap_olustur(kapasite);
	for(int i = 0;i < heap->eleman_sayisi;i++){
		heap_insert(new_heap,heap->dizi[i].key);
	}
	return new_heap;
}

void heap_buyut_yeni(struct heap **heap,int kapasite){
	struct heap *new_heap;
	new_heap = heap_olustur(kapasite);
	for(int i = 0;i < (*heap)->eleman_sayisi;i++){
		heap_insert(new_heap,(*heap)->dizi[i].key);
	}
	
	yok_et_heap(&(*heap));
	(*heap) = new_heap;
}

int main(){
	struct heap *heap = NULL;
	heap = heap_olustur(5);
	heap_insert(heap,32);
	heap_insert(heap,21);
	heap_insert(heap,43);
	heap_insert(heap,42);
	heap_insert(heap,61);
	print_heap(heap);
	heap_buyut_yeni(&heap,7);
	//heap = heap_buyut(heap,7);
	//heap_insert(heap,100);
	heap_insert(heap,100);
	heap_insert(heap,91);
	print_heap(heap);
	//yok_et_heap(&heap);
	/*if( !heap ){
		printf("heap is NULL");
	}else{
		printf("heap isn't NULL");
	}
	//print_heap(heap);
	//struct heap *heap2 = NULL;
	//heap = heap_olustur(4);
	/*create_heap(&heap,7);
	create_heap(&heap2,7);
	initialize_heap(heap2,7,101);
	print_heap(heap2);
	heap_insert(heap,34);
	heap_insert(heap,91);
	heap_insert(heap,74);
	heap_insert(heap,76);
	heap_insert(heap,80);
	heap_insert(heap,100);
	print_heap(heap);
	printf("is heap = %d",heap_mi(heap));
	heap_birlestir(heap,heap2);
	print_heap(heap);
	//heap_sort_2(heap);
	//print_heap(heap);
	/*initialize_heap(heap,7,101);
	print_heap(heap);
	printf("is heap = %d\n",heap_mi(heap));
	heapify(heap);
	print_heap(heap);
	printf("is heap = %d\n",heap_mi(heap));
	/*heap_sort(heap);
	printf("is heap = %d\n",heap_mi(heap));
	//print_heap(heap);
	//printf("is sort = %d\n",sirali_mi(heap));
	heap_insert(heap,12);
	heap_insert(heap,32);
	heap_insert(heap,23);
	print_heap(heap);
	printf("is heap = %d\n",heap_mi(heap));
	/*if( !heap ){
		printf("heap is NULL'");
	}else{
		printf("heap isn't NULL");
	}
	printf("heap->kapasite = %d",heap->kapasite);
	printf("heap->eleman_sayisi = %d",heap->eleman_sayisi);*/
}
