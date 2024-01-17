#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>

// Stack
typedef struct Node{
    char jenis[30];
    char noKendaraan[10];
    int tahun, bulan, tanggal;
    float jamMasuk, jamKeluar;
    int harga;

    struct Node *next;
}Node;

// Linked List untuk hashTable daftar membership
typedef struct LL{
    char nama[50];
    int tahun, bulan, tanggal;

    struct LL *next;
}LL;

//Tree Tahun
typedef struct tree
{
    int bulan;
    int tanggal;
    int tahun;
    char jenis[30];
    char noKendaraan[10];
    float jamMasuk, jamKeluar;
    int harga;
    struct tree *next, *left, *right;

}Tree;

//Initialization awal dari File dan Sebagian Proses Opsi 1, 2, dan 4
//Salin Data ke Node pada Tree
Tree *new(char type[], char number[], int date, int month, int year, float hourIn, float hourOut, int price)
{
    Tree *cTree = (Tree*)malloc(sizeof(Tree));
    cTree->bulan = month;
    cTree->tanggal = date;
    cTree->tahun = year;
    strcpy(cTree->jenis, type);
    strcpy(cTree->noKendaraan, number);
    cTree->bulan = month;
    cTree->tanggal = date;
    cTree->tahun = year;
    cTree->jamMasuk = hourIn;
    cTree->jamKeluar = hourOut;
    cTree->harga = price;
    cTree->left = NULL;
    cTree->right = NULL;
    cTree->next = NULL;
    return cTree;
}

//Mencari Node pada Tree untuk diinput dari File atau data Baru pada Tree
Tree *pushToTree(Tree **node, char type[], char number[], int date, int month, int year, float hourIn, float hourOut, int price)
{
    if(*node == NULL){
        //Masukkan data ke Node Kosong
        return new(type, number, date, month, year, hourIn, hourOut, price);
    }
    else
    {
        if((*node)->bulan == month && (*node)->tanggal == date)
        {
            //Geser ke Node bawah
            (*node)->next = pushToTree(&(*node)->next, type, number, date, month, year, hourIn, hourOut, price);
        }
        else if((*node)->bulan > month && (*node)->tanggal > date)
        {
            //Geser ke Node Kiri
            (*node)->left = pushToTree(&(*node)->left, type, number, date, month, year, hourIn, hourOut, price);
        }
        else if((*node)->bulan < month && (*node)->tanggal < date)
        {
            //Geser ke Node Kanan
            (*node)->right = pushToTree(&(*node)->right, type, number, date, month, year, hourIn, hourOut, price);
        }
    }
    return *node;
}

// Insert LL untuk Hash Table
void insert(LL **HEAD, char nama[], int tanggal, int bulan, int tahun){
    LL *ptr = *HEAD;
    LL *temp = (LL*)malloc(sizeof(LL));
    strcpy(temp->nama, nama);
    temp->tanggal = tanggal;
    temp->bulan = bulan;
    temp->tahun = tahun;
    temp->next = NULL;
    if(*HEAD == NULL){
        *HEAD = temp;
    }else{
        while(ptr->next != NULL){
            (*HEAD) = (*HEAD)->next;
        }
        (*HEAD)->next = temp;
    }
}

//Print Data from HashTable
LL *memberData(LL *HEAD){
    LL *ptr = HEAD;
    char valid;

    while(ptr != NULL){
        system("cls");
        printf("---------------------------------------\n"
               "Member Details\n");
        printf("Nama : %s\n",ptr->nama);
        printf("Batas aktif membership : %02d/%02d/%04d\n",ptr->tanggal, ptr->bulan, ptr->tahun);
        printf(".......................................\n\n");
        printf("Is this correct? (y/n): "); scanf(" %c", &valid);
        fflush(stdin);
        if(valid == 'y')
        {
            return ptr;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return NULL;
}

// HashTable Print
void printHash(LL *HEAD[26][26]){
    int i = 1, j, k;

    for(j = 0; j<26; j++)
    {
        for(k = 0; k<26; k++)
        {
            LL *ptr = HEAD[j][k];
            while(ptr != NULL){
                printf("Member #%d\n",i);
                printf("Nama : %s\n",ptr->nama);
                printf("Tanggal akhir membership : %d/%d/%d\n", ptr->tanggal, (ptr->bulan), ptr->tahun);
                printf(".......................\n");
                ptr = ptr->next;
                i++;
            }
        }
    }
}

//Cek apakah Stack kosong
int isEmpty(Node *head){
    if(head == NULL)
        return 1;
    return 0;
}

//Proses Opsi 1
//Masukkan Input ke Stack
void pushInput(Node **head, char type[], char number[], int year, int month, int date, float hourIn){
    Node *node = (Node*) malloc(sizeof(Node));
    strcpy(node->jenis, type);
    strcpy(node->noKendaraan, number);
    node->tahun = year;
    node->bulan = month;
    node->tanggal = date;
    node->jamMasuk = hourIn;
    node->next = NULL;

    if(!isEmpty(*head))
        node->next = *head;
    *head = node;
}

//Memasukkan input data Baru
void scanInput(Node **head, char type[], char number[], int *year, int *month, int *date, float *hourIn, float *hourOut){
    //Input Tipe Kendaraan dengan Kata
    fflush(stdin);
    printf("Jenis kendaraan (Mobil/Motor/Box) : ");
    scanf(" %[^\n]", type);

    if(type[0] >= 97 && type[0] <= 122)
    {
        type[0] = type[0]-32;
    }
    int key;
    for(key = 1; type[key] != '\0'; key++)
    {
        if(type[key] >= 65 && type[key] <= 90)
        {
            type[key] = type[key]+32;
        }
    }
    fflush(stdin);

    //Input Nomor Plat Kendaraan
    printf("\nNo kendaraan (A0123BCD) : ");
    scanf(" %[^\n]", number);
    int kode;
    for(kode = 0;number[kode] != '\0'; kode++)
    {
        if(number[kode] >= 97 && number[kode] <= 122)
        {
            number[kode] = number[kode]-32;
        }
    }

    //Input Tanggal Masuk
    fflush(stdin);
    printf("\nTanggal masuk (dd/mm/yyyy) : ");
    scanf(" %d/%d/%d", date, month, year);

    //Input Jam Masuk
    fflush(stdin);
    printf("\nJam Masuk (hh.mm): ");
    scanf("%f", hourIn);

    //Push ke Stack dan File
    pushInput(head, type, number, *year, *month, *date, *hourIn);
    FILE *fin = fopen("dataParkir.txt","a+");
    fprintf(fin, "%s#%s#%d/%d/%d#%.2f#0.00#0\n", type, number, *date, *month, *year, *hourIn);
    fclose(fin);
}

//Proses Opsi 3
//print Daftar Parkir (keseluruhan) pada Stack
void printHistory(Node *head)
{
    Node *curr = head;
    int li;
    printf("                                       History\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| No. | Jenis Kendaraan | Nomor Plat Kendaraan | Tanggal    | Jam Masuk | Jam Keluar |  Harga  |\n");
    if (isEmpty(curr))
    {
    printf("|                                     Data Unavailable                                         |\n");
    }
    else
    {
        for(li=1;curr != NULL; curr = curr->next)
        {
            printf("| %03d | %-15s | %-20s | %02d/%02d/%04d | %-9.2f | %-10.2f |  %-6d |\n", li, curr->jenis, curr->noKendaraan,
                   curr->tanggal, curr->bulan, curr->tahun, curr->jamMasuk, curr->jamKeluar, curr->harga);
            li++;
        }
    }
    printf("------------------------------------------------------------------------------------------------\n");
}

//Print Tree
void printTree(Tree *cTree, int li)
{
    if(cTree == NULL)
        return;
    else
    {
        //Print menggunakan Inorder berdasar Tanggal. Namun Waktu tidak teratur
        printTree(cTree->left, li);
        printf("| %03d | %-15s | %-20s | %02d/%02d/%04d | %-9.2f | %-10.2f |  %-6d |\n", li, cTree->jenis, cTree->noKendaraan,
            cTree->tanggal, cTree->bulan, cTree->tahun, cTree->jamMasuk, cTree->jamKeluar, cTree->harga);
        li++;
        printTree(cTree->next, li);
        printTree(cTree->right, li);
    }
}

//Memilih Tree
void chooseTree(Tree *yTree[100])
{
    system("cls");
    int treeChoice, li = 1;
    int mod, i;

    //Menanyakan Tahun Tree yang diinginkan
    printf("Year: ");
    scanf("%d", &treeChoice);
    mod = treeChoice % 100;
    //Print Tree yang diminta
    printf("                                       History\n");
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| No. | Jenis Kendaraan | Nomor Plat Kendaraan | Tanggal    | Jam Masuk | Jam Keluar |  Harga  |\n");
    printTree(yTree[mod], li);
    printf("------------------------------------------------------------------------------------------------\n");
}

//Proses No. 2
//Mencari Node pada Tree untuk melengkapi data pada new Input
Tree *searchTree(Tree **node, char type[], char number[], int date, int month, int year, float hourIn, float hourOut, int price)
{
    if(((*node)->bulan == month) && ((*node)->tanggal == date) &&(strcmp((*node)->jenis, type) == 0) &&
       (strcmp((*node)->noKendaraan, number) == 0) && ((*node)->jamMasuk == hourIn)){
        //Memasukkan data ke Node yang dimaksud
        return new(type, number, date, month, year, hourIn, hourOut, price);
    }
    else
    {
        if((*node)->bulan == month && (*node)->tanggal == date)
        {
            //Geser Node bawah
            (*node)->next = pushToTree(&(*node)->next, type, number, date, month, year, hourIn, hourOut, price);
        }
        else if((*node)->bulan > month && (*node)->tanggal > date)
        {
            //Geser Node kiri
            (*node)->left = pushToTree(&(*node)->left, type, number, date, month, year, hourIn, hourOut, price);
        }
        else if((*node)->bulan < month && (*node)->tanggal < date)
        {
            //Geser Node Kanan
            (*node)->right = pushToTree(&(*node)->right, type, number, date, month, year, hourIn, hourOut, price);
        }
    }
    return *node;
}

//Masukkan pembayaran ke Stack
void pushOutput(Node **pay, float hourOut, int price)
{
    Node *node = *pay;
    node->jamKeluar = hourOut;
    node->harga = price;
    //Menyalin ke node
    *pay = node;
}

//Menentukan Harga
void checkPrice(Node **pay, float hourOut, int *price){

    Node *curr = *pay;

    //Perhitungan bayaran berdasarkan Jenis Kendaraan dan Lama Parkir
    if(strcmp(curr->jenis, "Mobil") == 0)*price = ceil(hourOut - curr->jamMasuk) * 3000;
    if(strcmp(curr->jenis, "Motor") == 0)*price = ceil(hourOut - curr->jamMasuk) * 2000;
    if(strcmp(curr->jenis,"Box") == 0)*price = ceil(hourOut - curr->jamMasuk) * 4000;
}

//Mencari Data pada Stack
Node *findData(Node *head, char number[], int *year, int *month, int *date, float *hourIn)
{
    //Mancari dengan Detil Parkir
    Node *curr = head;
    printf("\nNo Kendaraan: ");
    scanf(" %[^\n]", number);
    fflush(stdin);
    int kode;
    //Standarisasi input
    for(kode = 0;number[kode] != '\0'; kode++)
    {
        if(number[kode] >= 97 && number[kode] <= 122)
        {
            number[kode] = number[kode]-32;
        }
    }
    printf("\nJam masuk (hh.mm): ");
    scanf(" %f", hourIn);
    fflush(stdin);

    //search menggunakan linear
    for(curr = head; curr != NULL; curr = curr->next)
    {
        if(strcmp(curr->noKendaraan, number) == 0 &&
           curr->tanggal == *date && curr->bulan == *month
           && curr->tahun == *year && curr->jamMasuk == *hourIn){
            return curr;
        }
    }
    return NULL;
}

//Opsi No. 2
//Pengecekan membership
bool membershipPay(LL *hash[26][26], int *date, int *month, int *year) {
    char huruf[2];
    int mod1, mod2, i;
    LL *pick;

    //Mencari data membership dari HashTable dengan 2 huruf pertama yang menjadi penentu array pada hashTable
	printf("Cari member dengan memasukkan 2 huruf pertama: ");
    scanf(" %s", huruf);
    fflush(stdin);
    //Menyamakan uppercase dan lowercase
    if(huruf[0] >= 97 && huruf[0] <= 122)
    {
        huruf[0] = huruf[0]-32;
    }
    if(huruf[1] >= 65 && huruf[1] <= 90)
    {
        huruf[1] = huruf[1]+32;
    }
    mod1 = huruf[0] % 65;
    mod2 = huruf[1] % 97;
    if(hash[mod1][mod2] == NULL){
        //Error Control
        printf("\nData tidak ditemukan\n");
        return 0;
    }
    else{
        //Mencari Member
        pick = memberData(hash[mod1][mod2]);
        if(pick != NULL)
        {
            //Validasi Member
            printf("Tanggal Hari ini: "); scanf("%d/%d/%d", date, month, year);
            if(*year > pick->tahun)
            {
                printf("Membership Invalid\n");
                return 0;
            }
            else if(*year >= pick->tahun)
            {
                if(*month > pick->bulan)
                {
                    printf("Membership Invalid\n");
                    return 0;
                }
                else if(*month >= pick->bulan)
                {
                    if(*date > pick->tanggal)
                    {
                        printf("Membership Invalid\n");
                        return 0;
                    }
                    else
                    {
                        printf("Membership Valid\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Membership Valid\n");
                    return 1;
                }
            }
            else
            {
                printf("Membership Valid\n");
                return 1;
            }
        }
        else
        {
            //Error Control
            printf("Membership Not Found\n");
            return 0;
        }
    }
}

//Masukkan data member ke database
void saveMemberData(char nama[], int tanggal, int bulan, int tahun)
{
    FILE *fim = fopen("dataMember.txt", "a+");
    fprintf(fim, "%s#%d/%d/%d\n", nama, tanggal, bulan, tahun);
    fclose(fim);
}

//Proses Pembayaran
void payment(LL *hash[26][26], Node **pay, Node *head, char number[], int year, int month, int date, float *hourIn, float *hourOut, int *price)
{
    //Inisialisasi Variable untuk ya/tidak
    char choice;
    printf("Apakah anda member parkir?(y/n): ");
    fflush(stdin);
    scanf(" %c", &choice);
    fflush(stdin);
    //Cek apakah pengguna member atau bukan
    if(choice == 'y'){
        bool valid = 0;
        valid = membershipPay(hash, &date, &month, &year);
        if (valid == 1)
        {
            //Menyocokkan pada data pemarkiran
            system("cls");
            printHistory(head);
            printf("Search\n\nTanggal masuk: %02d/%02d/%04d", date, month, year);
            *pay = findData(head, number, &year, &month, &date, hourIn);
            if(*pay != NULL && (*pay)->jamKeluar == 0)
            {
                printf("\nJam keluar (hh.mm): ");
                scanf(" %f", hourOut);
                fflush(stdin);
                *price = 0;
                printf("\nPrice: Rp. 0\n");
                pushOutput(pay, *hourOut, *price);
            }
            else printf("Kendaraan sudah keluar\n");
        }
    }
    else if(choice == 'n')
    {
        printHistory(head);
        printf("Search\n\nTanggal masuk: ");
        scanf(" %d/%d/%d", &date, &month, &year);
        fflush(stdin);
        *pay = findData(head, number, &year, &month, &date, hourIn);
        if(*pay != NULL && (*pay)->jamKeluar == 0)
        {
            printf("\nJam keluar (hh.mm): ");
            scanf(" %f", hourOut);
            fflush(stdin);
            checkPrice(pay, *hourOut, price);
            printf("\nPrice: Rp. %d\n", *price);
            pushOutput(pay, *hourOut, *price);
        }
        else
        {
            //Error Control
            if(*pay == NULL) printf("\nData tidak ditemukan\n");
            else if ((*pay)->jamKeluar != 0) printf("Kendaraan sudah keluar\n");
        }
    }

}

//Proses Penukaran Node
void swap(Node *a, Node *b)
{
    Node temp[1];
    strcpy(temp->jenis,a->jenis);
    strcpy(temp->noKendaraan,a->noKendaraan);
    temp->tanggal = a->tanggal;
    temp->bulan = a->bulan;
    temp->tahun = a->tahun;
    temp->jamMasuk = a->jamMasuk;
    temp->jamKeluar = a->jamKeluar;
    temp->harga = a->harga;

    strcpy(a->jenis,b->jenis);
    strcpy(a->noKendaraan,b->noKendaraan);
    a->tanggal = b->tanggal;
    a->bulan = b->bulan;
    a->tahun = b->tahun;
    a->jamMasuk = b->jamMasuk;
    a->jamKeluar = b->jamKeluar;
    a->harga = b->harga;

    strcpy(b->jenis,temp->jenis);
    strcpy(b->noKendaraan,temp->noKendaraan);
    b->tanggal= temp->tanggal;
    b->bulan = temp->bulan;
    b->tahun = temp->tahun;
    b->jamMasuk= temp->jamMasuk;
    b->jamKeluar = temp->jamKeluar;
    b->harga = temp->harga;
}

//Proses Bubble Sort
void bubbleSort(Node *head)
{
    int swapped;
    Node *ptr;
    Node *ptrEnd = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr = head;

        while (ptr->next != ptrEnd)
        {
            if (ptr->harga > ptr->next->harga)
            {
                swap(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        ptrEnd = ptr;
    }while (swapped);
}

//Proses Opsi 4
//Daftar sebagai member
void regMember(LL *HashT[26][26]){
    //Inisialisasi Variable yang dibutuhkan
    int i,j, lama, tanggal, bulan, tahun, key1, key2;
    char nama[50];

    //Input Data
    printf("Masukkan nama anda : ");
    scanf(" %[^\n]", nama);
    fflush(stdin);
    for(i = 0; nama[i] != '\0'; i++)
    {
        if (i == 0 || nama[i-1] == ' ')
		{
			if(nama[i]>=97 && nama[i]<=122)
			{
				nama[i] = nama[i]-32;
			}
		}
		else if(nama[i]>=65 && nama[i]<=90)
			{
				nama[i] = nama[i]+32;
			}
    }

    key1 = nama[0] % 65;
    key2 = nama[1] % 97;

    printf("Masukkan tanggal mendaftar : ");
    scanf(" %d/%d/%d", &tanggal, &bulan, &tahun);

    printf("Berapa bulan anda ingin menjadi member (Rp. 100.000/bulan): ");
    scanf(" %d", &lama);

    //Menghitung Batas Berlaku Membership
    bulan += lama;

    if(bulan > 12)
    {
        if(!(bulan % 12))
        {
            tahun += ((bulan / 12) - 1);
            bulan = 12;
        }
        else
        {
            tahun += (bulan / 12);
            bulan = bulan % 12;
        }
    }
    //Informasi Membership yang baru didaftarkan
    printf("Total Pembayaran: Rp. %d.000\n", lama * 100);
    printf("Batas Akhir Membership : %d/%d/%d\n", tanggal, bulan, tahun);

    //Push ke Hash Table
    insert(&HashT[key1][key2], nama, tanggal, bulan, tahun);

    //Input ke File database
    saveMemberData(nama, tanggal, bulan, tahun);
}


int main(){
    //Inisialisasi Node
    Node *head = NULL;
    Node *pay;
    Node *temp;

    //Inisialisasi Hash Table
    int i, j, k, key1, key2;
    LL *HashT[26][26];
    for(i = 0; i < 26; i++){
        for(j = 0; j < 26; j++){
            HashT[i][j] = NULL;
        }
    }

    //Inisialisasi Tree
    Tree *yTree[100];

    for(i=0;i<100;i++){
        yTree[i] = NULL;
    }

    //Variable untuk Tree
    int mod;

    //Variabel untuk daftar member
    char namaMember[50], huruf[2];
    int tanggalMember, bulanMember, tahunMember;

    //Variable untuk menu utama
    int pilihan;

    //Variable untuk printing count
    int li = 1;

    //Variable untuk data input
    char type[30];
    int year;
    int month;
    int date;
    char number[10];
    float hourIn;
    float hourOut;
    int price;

    //Proses Input dari File ke Stack dan Tree
    FILE *fin = fopen("dataParkir.txt","r");
    while(!feof(fin)){
        fscanf(fin,"%[^#]#%[^#]#%d/%d/%d#%f#%f#%d\n", type, number, &date, &month, &year, &hourIn, &hourOut, &price);
        pushInput(&head, type, number, year, month, date, hourIn);
        pushOutput(&head, hourOut, price);
        mod = year % 100;
        yTree[mod] = pushToTree(&yTree[mod], type, number, date, month, year, hourIn, hourOut, price);
    }
    fclose(fin);

    //Proses Input dari File ke Hash Table
    FILE *fim = fopen("dataMember.txt", "a+");
    while(!feof(fim))
    {
        fscanf(fim, "%[^#]#%d/%d/%d\n", namaMember, &tanggalMember, &bulanMember, &tahunMember);
        key1 = namaMember[0] % 65;
        key2 = namaMember[1] % 97;
        insert(&HashT[key1][key2], namaMember, tanggalMember, bulanMember, tahunMember);
    }
    fclose(fim);

    do{
        //Main Menu
        system("cls");
        printf("Aplikasi Pembayaran Parkir\n\n");
        printf("1. Masukkan data baru\n");
        printf("2. Bayar parkir\n");
        printf("3. Tampilkan data\n");
        printf("4. Mendaftar sebagai member\n");
        printf("0. Keluar\n\n");

        //Memilih opsi menu
        printf("Pilih : ");scanf("%d", &pilihan);
        fflush(stdin);

        //Proses setiap menu
        switch(pilihan){
            case 1 :
                //Input data baru
                scanInput(&head, type, number, &year, &month, &date, &hourIn, &hourOut);
                //Masukkan data baru ke Tree
                mod = year % 100;
                hourOut = 0;
                price = 0;
                yTree[mod] = pushToTree(&yTree[mod], type, number, date, month, year, hourIn, hourOut, price);
                printf("Press any key to continue\n");
                getch();
                break;

            case 2 :
                //Sorting Berdasar Harga (karena akan ditampilkan)
                bubbleSort(head);
                //Melengkapi info pada Inout saat membayar
                payment(HashT, &pay, head, number, year, month, date, &hourIn, &hourOut, &price);
                //Input to Tree
                mod = year % 100;
                yTree[mod] = searchTree(&yTree[mod], type, number, date, month, year, hourIn, hourOut, price);
                //Rewrite ke File
                temp = head;
                FILE *fout = fopen("dataParkir.txt","w");
                while(temp != NULL){
                    fprintf(fout, "%s#%s#%d/%d/%d#%.2f#%.2f#%d\n", temp->jenis, temp->noKendaraan, temp->tanggal, temp->bulan, temp->tahun, temp->jamMasuk, temp->jamKeluar, temp->harga);
                    temp = temp->next;
                }
                fclose(fout);
                printf("Press any key to continue\n");
                getch();
                break;

            case 3 :
                //Opsi Print ada dua, print data Parkir (1) atau data Membership (2)
                printf("Print\n1. Parking History\n2. Membership List\n\nChoice: ");
                int printOpt;
                scanf("%d", &printOpt);
                //Print Data Parkir
                if(printOpt == 1)
                {
                    //Opsi Print ada dua, print keseluruhan (Opsi 1) atau berdasarkan Tahun (Opsi 2)
                    int viewChoice;
                    printf("1. All-Time\n2. Specific Year\n\nChoice: ");
                    scanf("%d", &viewChoice);
                    if(viewChoice == 1)
                    {
                        //Sortir daftar
                        bubbleSort(head);
                        //Print Seluruh daftar
                        printHistory(head);
                    }
                    //Print berdasar Tahun
                    else if(viewChoice == 2) chooseTree(yTree);
                }
                //Print Data Member
                else if(printOpt == 2) printHash(HashT);
                printf("Press any key to Continue\n");
                getch();
                break;

            case 4 :
                //Menambahkan anggota member baru
                regMember(HashT);
                printf("Press any key to continue\n");
                getch();
                break;
        }
    }while(pilihan != 0);

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
