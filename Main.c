#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define max_size 300


void mainmenu (void);
void login (void);
void product (void);
void show (void);
void orders (void);
void exited (void);

FILE *s,*xx,*y;

int a,b,c;
int i,j,k,h;
int m,n,l,p;

int input,count;
int n = 0;	
int m = 0;	
int p = 0;	
int t[max_size] = {0};	
int idx;
int ch;
int t[];
int quantity;





struct list_product{
    char product_id[7];
	char product_name[100];
	int product_price;
	int product_quantity;
};
struct customer{
	char ID[15];
	char Name[20];
	char Phone[15];
	char Address[50];
};
struct Order{
	char ID_Order[15];
	char Name_Order[30];
	char Phone_Order[15];
	char Address_Order[50];
	bool State_Order;
	unsigned long long total_price;
	int discount;
	unsigned long long cost;
	struct list_product order_pr[50];
};
struct list_product pr[max_size];
struct customer cus[1];				
struct list_product cus_pr[500];	
struct Order order[max_size];	


char id_new[15];
char id_cus_pr[15];
char cus_pr_id[15]; 
char id[15];
char month[12];



int main()
{	
    login();
	load_data(pr,&n); 
	mainmenu();
	return 0;
}


void mainmenu()
{

    system("cls");
    time_t t;
	time(&t);
    printf("\n");
	printf("           Hello manager, have a good day!                                %s",ctime(&t));
	printf("\n\n\n");
	printf("                                              ORDER MANAGEMENT SYSTEM\n");
	printf(" \n\n\n");
	printf("\n 1. Product\n");
	printf("\n 2. Order\n");
	printf("\n 3. Show\n");
	printf("\n 0. Exit\n\n\n");
	
    printf(" Enter Your Choice : ");
    int ch;
    scanf("%d", &ch);
    
    switch(ch)
{
    case 1:
    	product ();
	case 2:			
		orders ();	
	case 3:		
		show();	
	case 0:
		printf("\n\n");
		printf ("Press yes to exit.(Y/N) ---> ");
	    char ch= 'y';
		getchar();
		scanf ("%c",&ch);
		while (ch == 'y' || ch == 'Y') {
			printf("\n\n");
		    printf ("Do you want to save.(Y/N) ---> ");
	        char ch= 'y';
		    getchar();
		    scanf ("%c",&ch);
		    while (ch == 'y' || ch == 'Y') {
		    	rewrite_data();
		    	write_bill(pr, order, m, n, t);
		    	system("cls");
		    	printf("\nSaved!");
			    printf("\n\n\n");
		        printf("                   See you again!  \n");
		        
	     	    printf("\n\n");
		        exit(0);
			}
			system("cls");
			printf("\n\n\n");
		    printf("                   See you again!  \n");
	     	printf("\n\n");
		    exit(0);
		} mainmenu();
}
	

}



void login()
{
	
    FILE* finp;
    if ((finp = fopen("login.txt","r")) == NULL){
        printf("Error!");
        exit(1);  
    }
    char User[100];
    char Pass[100];
    bool status = true;  
    fscanf(finp,"%s",&User);
    fscanf(finp,"%s",&Pass);
    fclose(finp);
    char c;
    char acc[100];
    char password[100];
    bool wrong = false;
    do{
        system("cls");
        time_t t;
	    time(&t);
     	printf("\n");
	    printf("      %s",ctime(&t));
	    printf("\n");
        printf("                                            _________________________________   \n");
	    printf("                                           |                                 |   \n");
		printf("                                           |     ORDER MANAGEMENT SYSTEM     |    \n");
		printf("                                           |_________________________________|     \n");
		printf("\n\n\n\n\n");
        
        
        printf("Username: ");
        scanf("%s",&acc);
        printf("Password: "); 
		fflush(stdin);
        int pos = 0;
        while(true){
            c = getch();
            if(c == 13) {break;}
            else if(c == 8){
                if(pos > 0){
                    pos--;
                    password[pos] = '\0';
                    printf("\b \b");
                }
            } else{
                password[pos] = c;
                pos++;
                printf("*");
            }
        }
        password[pos] = '\0';
        wrong = (strcmp(acc,User) != 0) || (strcmp(password,Pass) != 0);
        if(wrong){
		printf("\nAccount or password wrong. Please try again!\n");
		getch();
		} 
    } while( ((strcmp(acc,User) != 0) || (strcmp(password,Pass) != 0)) );

    system("cls");
}



void load_data(struct list_product pr[], int *n){ 
   
	FILE *fi = fopen("product.txt", "r");
	*n = 0;
	if (fi == NULL){
        printf("Error! Opening product file.");
        exit(1);
    }
	while(fscanf(fi,"%6s", &pr[*n].product_id) == 1)
	{
		fscanf(fi,"|%[^|]|", &pr[*n].product_id);
		fscanf(fi,"%[^|]|", &pr[*n].product_name);
		fscanf(fi,"%d", &pr[*n].product_price);
		fscanf(fi,"%d", &pr[*n].product_quantity);
		(*n)++;
	}
	fclose(fi);
	};

void load_bill(){
	FILE *fa = fopen("bill.txt", "r");
	if (fa == NULL){
        printf("Error! Opening product file.");
        exit(1);
    }
}

void rewrite_data(){
	FILE *fo  = fopen("product.txt", "w");
	if (fo == NULL)
    	printf("Failed to open file!");
	else
	{
		for(i=0;i<n;i++)
				fprintf(fo, "|%s|%s|%d %d\n",  pr[i].product_id, pr[i].product_name, pr[i].product_price, pr[i].product_quantity);
    	fclose(fo);
	}	
}

void add_to_order(struct list_product pr[], int *m, struct customer cus[], struct Order order[], int t[], struct list_product cus_pr[], int p){
	strcpy(order[*m].ID_Order, cus[0].ID);
	strcpy(order[*m].Name_Order, cus[0].Name);
	strcpy(order[*m].Phone_Order, cus[0].Phone);
	strcpy(order[*m].Address_Order, cus[0].Address);
	
	for(i=0;i<p;i++){
		strcpy(order[*m].order_pr[t[*m]].product_id, cus_pr[i].product_id);
		strcpy(order[*m].order_pr[t[*m]].product_name, cus_pr[i].product_name);
		order[*m].order_pr[t[*m]].product_price = cus_pr[i].product_price;
		order[*m].order_pr[t[*m]].product_quantity = cus_pr[i].product_quantity;
		
		t[*m]++;
	}
	(*m)++;
}


void write_bill(){
	FILE *fa = NULL;	
	fa = fopen("bill.txt", "w");
	if (fa == NULL)
		printf("Failed to open file!");
	else
	{
	for(i=0 ; i<m ; i++)
	{
		fprintf(fa, "Id order: %s|Name customer: %s|Phone: %s|Address: %s", order[i].ID_Order,
																			order[i].Name_Order, 
																			order[i].Phone_Order, 
																			order[i].Address_Order);
		
		for(j=0 ; j<t[i] ; j++)
		{
			fprintf(fa, "|Product Id: %s|Product name: %s|Price: %d|Quantity:%d|",order[i].order_pr[j].product_id, 
																				order[i].order_pr[j].product_name, 
																				order[i].order_pr[j].product_price, 
																				order[i].order_pr[j].product_quantity);
		}
		
		fprintf(fa, "Total: %llu|Discount(%): %d|Cost: %llu\n", order[i].total_price, 
																order[i].discount, 
																order[i].cost);
	}
	fclose(fa);
	}
}



// ham kiem tra id san pham da co chua
bool check_id_add(struct list_product pr[], int n){
	if(n==0){
		return true;
	}
	else{
		for(i=0;i<n;i++){
			if(strcmp(pr[i].product_id,pr[n].product_id)==0){
				return false;
			}
		}	
	}
	return true;
}

// ham kiem tra nhap id san pham
bool check_id(char id[]){
	for(i=0;i<6;i++){
		if(i>=0 && i<3){
			if(id[i]<'A' || id[i]>'Z'){
				return false;
			}
		}
		else{
			if(id[i]<'0' || id[i]>'9'){
				return false;
			}
		}
	}
	return true;
}

// ham hien thi danh sach san pham
void display(struct list_product pr[], int n){
printf("\n___________________________List Of Products In The Store___________________________\n\n");

	printf("%15s", "Product ID");
	printf("%25s", "Product Name");
	printf("%25s", "Product Price");
	printf("%25s", "Product Quantity");
	printf("\n");
	for(h=0;h<n;h++){
		printf("%15s", pr[h].product_id);
		printf("%25s", pr[h].product_name);
		printf("%25d", pr[h].product_price);
		printf("%24d", pr[h].product_quantity);
		printf("\n");
	}
}

// ham them san pham
void add(struct list_product pr[], int* n){
	j = 0;			// id phai thoa man dinh dang id va khong dc trung voi id nao khac co san
	do{
		if(j>0){
			system("cls");
			if(*n>0)
				display(pr,*n);
			else{
				printf("\n\tItem list is empty!\n");
			}
			printf("\n\tInvalid ID!\n");
		}
		printf("\n\tProduct ID      : ");
		fflush(stdin); scanf("%s", &pr[*n].product_id);
		j++;
	}while(check_id_add(pr,*n)==false || check_id(pr[*n].product_id)==false || strlen(pr[*n].product_id)!=6);
	
	system("cls");
	if(*n>0)
		display(pr,*n);
	else{
		printf("\n\tItem list is empty!\n");
	}
	printf("\n\tID Acpect!\n");
	printf("\n\tProduct ID         : %s\n",pr[*n].product_id);
	
	printf("\tProduct Name       : ");
	fflush(stdin); scanf("%[^\n]", &pr[*n].product_name);
	
	printf("\tProduct Price      : ");
	scanf("%d", &pr[*n].product_price);
	
	j=0;    // so luong sp them vao phai > 0
	do{
		if(j>0){
			system("cls");	
			if(*n>0)
				display(pr,*n);
			else{
				printf("\n\tItem list is empty!\n");
			}
			printf("\n\tInvalid Quantity!\n");
			printf("\n\tProduct ID         : %s", pr[*n].product_id);
			printf("\n\tProduct Name       : %s", pr[*n].product_name);
			printf("\n\tProduct Price      : %d\n", pr[*n].product_price);
		}
		printf("\tProduct Quantity   : ");
		scanf("%d", &pr[*n].product_quantity);
		j++;
	}while(pr[*n].product_quantity<=0);
	
	system("cls");
	if(*n>0)
		display(pr,*n);
	else{
		printf("\n\tItem list is empty!\n");
	}
	printf("\n\tProduct ID		: %s\n", pr[*n].product_id);
	printf("\n\tProduct Name    : %s\n", pr[*n].product_name);
	printf("\n\tProduct Price   : %d\n", pr[*n].product_price);
	printf("\n\tProduct Quantity: %d\n", pr[*n].product_quantity);
	
	(*n)++;
}

// ham tim san pham theo id
int find(struct list_product pr[], int n){
	int rc=-1;
	printf("Enter ID of the product you want to find: ");
	
	char pid[10];
    scanf("%s", &pid);
    fflush(stdin);
    
    for(i=0 ; i<n ; i++)
		if(strcmp(pid,pr[i].product_id) == 0)
			rc = i;
			
    return rc;
}

// ham chinh sua thuoc tinh san pham
void edit(struct list_product pr[], int idx){
	j = 0;
	printf("Enter new information item %d\n",idx+1);
	do{
		if(j>0)
			printf("\n\tInvalid ID!\n");
			
		printf("+ Enter new product ID  : ");
		fflush(stdin); scanf("%s", &pr[idx].product_id);
		j++;
	}while(check_id_add(pr,idx)==false || check_id(pr[idx].product_id)==false || strlen(pr[idx].product_id) != 6);
	
	printf("+ Enter new product name: ");
	fflush(stdin);
	scanf("%[^\n]", &pr[idx].product_name);
	
	printf("+ Enter new product price: ");
	scanf("%d", &pr[idx].product_price);
	
	printf("+ Enter product quantity: ");
	scanf("%d", &pr[idx].product_quantity);
}

// ham kiem tra id khi chinh sua xem co trung voi id nao co san khong
bool check_id_edit(struct list_product pr[], int n, int l, char id_new[]){
	for(h=0;h<n;h++){
		if(h!=l){
			if(strcmp(pr[h].product_id,id_new)==0){
				return false;
			}
		}
	}
	return true;
}

struct list_product pr[];
 int idx;
// ham xoa san pham
void del(int *n){
	for(i=idx ; i<*n ; i++)
		pr[i] = pr[i+1];
	(*n)--;
	printf("\n\nDelete success!");
}

// ham viet file danh sach san pham
void write(struct list_product pr[], int n){
	FILE *fo = NULL;
	fo = fopen("product_list.txt", "w");
	if (fo == NULL)
    	printf("Failed to open file!");
	else
	{
		fprintf(fo,"%10s%30s%20s%20s", "Product ID", "Product Name", "Product Price", "Product Quantity\n");
		fprintf(fo,"===============================================================================\n");
		for(i=0;i<n;i++)
			fprintf(fo,"%10s%30s%20d%19d\n", pr[i].product_id, pr[i].product_name, pr[i].product_price, pr[i].product_quantity);
    	fclose(fo);
	}
	
	FILE *fi = NULL;
	fi = fopen("product.txt", "w");
	if (fi == NULL)
    	printf("Failed to open file!");
	else
	{
		for(i=0;i<n;i++)
			fprintf(fi, "%s|%s|%s|%d %d\n", pr[i].product_id,pr[i].product_id, pr[i].product_name, pr[i].product_price, pr[i].product_quantity);
    	fclose(fi);
	}
}

// ham doc file danh sach san pham



void read(struct list_product pr[], int *n){
	FILE *fi = fopen("product.txt", "r");
	*n = 0;
	while(fscanf(fi,"%6s", &pr[*n].product_id) == 1)
	{
		fscanf(fi,"|%[^|]|", &pr[*n].product_id);
		fscanf(fi,"%[^|]|", &pr[*n].product_name);
		fscanf(fi,"%d", &pr[*n].product_price);
		fscanf(fi,"%d", &pr[*n].product_quantity);
		(*n)++;
	}
	fclose(fi);
}


// ham gan san pham tu gio hang vao bill

//viet bill don hang

// ham hien thi bill
void show_order(struct Order order[], int m, int t[]){
	printf("\n\tID Order      : %s\n", order[m-1].ID_Order);
	printf("\tCustomer Name   : %s\n", order[m-1].Name_Order);
	printf("\tCustomer Phone  : %s\n", order[m-1].Phone_Order);
	printf("\tCustomer Address: %s\n", order[m-1].Address_Order);
	
	printf("\n");
	printf("%15s", "Product ID");
	printf("%25s", "Product Name");
	printf("%25s", "Product Price");
	printf("%25s", "Product Quantity\n");
	
	for(i=0;i<t[m-1];i++){
		printf("%15s", order[m-1].order_pr[i].product_id);
		printf("%25s", order[m-1].order_pr[i].product_name);
		printf("%25d", order[m-1].order_pr[i].product_price);
		printf("%24d", order[m-1].order_pr[i].product_quantity);
		printf("\n");
	}
	order[m-1].total_price = 0;
	order[m-1].discount = 10;
	for(i=0;i<t[m-1];i++){
		order[m-1].total_price += order[m-1].order_pr[i].product_price * order[m-1].order_pr[i].product_quantity;
	}
	order[m-1].cost = order[m-1].total_price - order[m-1].total_price*order[m-1].discount/100;
	printf("\n\t+Total Price: %llu", order[m-1].total_price);
	printf("\n\t+Discount: %d%%",order[m-1].discount);
	printf("\n\t+The Cost: %llu\n",order[m-1].cost);
}

// ham hien thi thong bao co chac chan muon thanh toan don hang hay khong?
void decide(struct Order order[], int m){
	printf("\n\tAre you want to buy? (1:Yes / 0:No): ");
	int decide_order;
	scanf("%d",&decide_order);
	if(decide_order == 1){
		order[m-1].State_Order = true;
	}
	else{
		order[m-1].State_Order = false;
	}
}

// ham tra lai sp tu gio hang ve kho hang khi khong muon mua nua
void return_product(struct Order order[], int* m, struct list_product pr[], int t[], int* p, int n){
	for(i=0;i<t[*m-1];i++){
		for(j=0;j<n;j++){
			if(strcmp(order[*m-1].order_pr[i].product_id,pr[j].product_id)==0){
				pr[j].product_quantity += order[*m-1].order_pr[i].product_quantity;
			}
		}
	}
	*p = 0;
	t[*m-1] = 0;
	(*m)--;
}

// ham kiem tra id sp khach hang co ton tai trong kho hang hay khong
bool check_id_cus_pr(struct list_product pr[], int n, char id_cus_pr[]){
	for(i=0;i<n;i++){
		if(strcmp(id_cus_pr,pr[i].product_id)==0){
			return true;
		}
	}
	return false;
}

// ham nhap vao thong tin khach hang
void Customer(struct customer cus[]){
	system("cls");
	int count = 0;
	do{
		if(count>0){
			system("cls");
			printf("\n\tInvalid ID!\n");
		}
		printf("\n\tID Order        : ");
		fflush(stdin);
		scanf("%s", &cus[0].ID);
		count++;
	}while(strlen(cus[0].ID)!=14);
	
	system("cls");
	printf("\n\tID Acpect!\n");
	printf("\n\tID Order        : %s\n", cus[0].ID);
	
	printf("\tCustomer Name   : ");
	fflush(stdin);
	scanf("%[^\n]", &cus[0].Name);
	
	printf("\tCustomer Phone  : ");
	fflush(stdin);
	scanf("%s", &cus[0].Phone);
	
	printf("\tShipping Address: ");
	fflush(stdin);
	scanf("%[^\n]", &cus[0].Address);
}

// ham hien thi thong tin khach hang
void show_cus(struct customer cus[]){
	printf("\n\tID Order        : %s\n", cus[0].ID);
	printf("\tCustomer Name   : %s\n", cus[0].Name);
	printf("\tCustomer Phone  : %s\n", cus[0].Phone);
	printf("\tCustomer Address: %s\n", cus[0].Address);
}

// ham hien thi danh sach cac san pham trong gio hang
void show_cus_pr(struct list_product cus_pr[], int p){
	printf("\n");
	printf("%15s", "Product ID");
	printf("%25s", "Product Name");
	printf("%25s", "Product Price");
	printf("%25s", "Product Quantity\n");
	
	for(i=0;i<p;i++){
		printf("%15s", cus_pr[i].product_id);
		printf("%25s", cus_pr[i].product_name);
		printf("%25d", cus_pr[i].product_price);
		if(cus_pr[i].product_quantity==0){
			printf("%24s","Out of stock");
		}
		else{
			printf("%24d", cus_pr[i].product_quantity);
		}
		printf("\n");
	}
}

// ham kiem tra san pham nay da co trong gio hang hay chua, neu co roi thi += so luong, con chua co thi them 1 sp
bool check_cus_pr(char cus_pr_id[], struct list_product cus_pr[], int p, int quantity){
	if(p==0){
		return true;
	}
	else{
		for(h=0;h<p;h++){
			if(strcmp(cus_pr_id, cus_pr[h].product_id)==0){
				return false;
			}
		}
	}
	return true;
}

// ham mua hang cua khach hang
void buy(struct list_product pr[], int x, struct list_product cus_pr[], int* p, int quantity, char cus_pr_id[]){
	if(quantity <= pr[x].product_quantity){
		if(check_cus_pr(cus_pr_id,pr,*p,quantity)==true){
			cus_pr[*p] = pr[x];
			cus_pr[*p].product_quantity = quantity;
			pr[x].product_quantity -= quantity;
			(*p)++;
		}
		else{
			for(k=0;k<=*p;k++){
				if(strcmp(cus_pr_id, cus_pr[k].product_id)==0){
					cus_pr[k].product_quantity += quantity;
					pr[x].product_quantity -= quantity;
				}
			}
		}
		j=2;		// neu tim thay dung id va thoa man so luong thi sp sp trong kho hang se bi tru
	}
	else{
		j=1;		// so luong san pham can mua khong du
	}
}

// ham hien thi danh sach cac sp theo thu tu tu A -> Z
void show_pr_az(struct list_product pr[], int n){
	system("cls");
	printf("\n\tList Of Products In Alphabetical Order From 'A' To 'Z'\n\n");
	
	printf("%15s", "Product ID");
	printf("%25s", "Product Name");
	printf("%25s", "Product Price");
	printf("%25s", "Product Quantity\n");
	
	struct list_product pr_cpy[max_size];
	
	for(h=0;h<n;h++){
		strcpy(pr_cpy[h].product_id, pr[h].product_id);
		strcpy(pr_cpy[h].product_name, pr[h].product_name);
		pr_cpy[h].product_price = pr[h].product_price;
		pr_cpy[h].product_quantity = pr[h].product_quantity;
	}
	
	for(h=0;h<n;h++){
		for(b=h+1;b<n;b++){
			if(pr_cpy[h].product_name[0] > pr_cpy[b].product_name[0]){
				struct list_product temp = pr_cpy[h];
				pr_cpy[h] = pr_cpy[b];
				pr_cpy[b] = temp;
			}
		}
	}
	
	for(h=0;h<n;h++){
		printf("%15s", pr_cpy[h].product_id);
		printf("%25s", pr_cpy[h].product_name);
		printf("%25d", pr_cpy[h].product_price);
		if(pr_cpy[h].product_quantity==0){
			printf("%24s","Out of stock");
		}
		else{
			printf("%24d", pr_cpy[h].product_quantity);
		}
		printf("\n");
	}
}

// ham hien thi danh sach cac sp theo gia tien
void show_pr_price(struct list_product pr[], int n){
	system("cls");
	printf("\n\tList Of Products In Ascending Order Of Price\n\n");
	
	printf("%15s", "Product ID");
	printf("%25s", "Product Name");
	printf("%25s", "Product Price");
	printf("%25s", "Product Quantity\n");
	
	struct list_product pr_cpy[max_size];
	
	for(h=0;h<n;h++){
		strcpy(pr_cpy[h].product_id, pr[h].product_id);
		strcpy(pr_cpy[h].product_name, pr[h].product_name);
		pr_cpy[h].product_price = pr[h].product_price;
		pr_cpy[h].product_quantity = pr[h].product_quantity;
	}
	
	for(h=0;h<n;h++){
		for(b=h+1;b<n;b++){
			if(pr_cpy[h].product_price > pr_cpy[b].product_price){
				struct list_product temp = pr_cpy[h];
				pr_cpy[h] = pr_cpy[b];
				pr_cpy[b] = temp;
			}
		}
	}
	
	for(h=0;h<n;h++){
		printf("%15s", pr_cpy[h].product_id);
		printf("%25s", pr_cpy[h].product_name);
		printf("%25d", pr_cpy[h].product_price);
		if(pr_cpy[h].product_quantity==0){
			printf("%24s","Out of stock");
		}
		else{
			printf("%24d", pr_cpy[h].product_quantity);
		}
		printf("\n");
	}
}

// ham check month
bool check_show_order_month(char month[]){
	if(strlen(month)!=2)
		return false;
	if(month[0]>'1' || month[0]<'0'){
		return false;
	}
	if(month[1]>'9' || month[0]<'0'){
		return false;
	}
	if(month[0]=='1'){
		if(month[1]>'2'){
			return false;
		}
	}
	return true;
}

// hien thi don hang trong 1 thang nhat dinh
void show_order_month(struct Order order[], int m, int t[]){
	system("cls");
	if(m==0){
		printf("\n\tNo Orders Yet\n");
	}
	else{
		char month[3];
		count = 0;
		do{
			if(count>0){
				system("cls");
				printf("\n\tInvalid Month!\n");
			}
			printf("\n\tMonth: ");
			fflush(stdin); scanf("%s",month);
			count++;
		}while(check_show_order_month(month)==false);
		
		system("cls");
		printf("\n\tMonth Acpect!\n");
		printf("\n\tMonth: %s\n", month);
		
		count = 0;
		
		for(h=0;h<m;h++){
			if(order[h].ID_Order[2]==month[0] && order[h].ID_Order[3]==month[1]){
				show_order(order,h+1,t);
				count++;
			}
		}
		if(count==0){
			system("cls");
			printf("\n\tMonth: %s",month);
			printf("\n\n\tNo Orders Satisfied!\n");
		}
	}
}

// ham check id khi su dung chuc nang hien thi don hang bang cach nhap id
bool check_show_order_id(struct Order order[], int m, char id[]){
	if(strlen(id)!=14)
		return false;
	for(b=0;b<strlen(id);b++){
		if(id[b]<'0'||id[b]>'9'){
			return false;
		}
	}
	return true;
}

// hien thi chi tiet 1 don hang khi co id
void show_order_id(struct Order order[], int m, int t[]){
	system("cls");
	if(m==0){
		printf("\n\tNo Orders Yet\n");
	}
	else{
		char check_id[15];
		count = 0;
		
		do{
			if(count>0){
				system("cls");
				printf("\n\tInvalid ID!\n");
			}
			printf("\n\tOrder ID: ");
			fflush(stdin); scanf("%s",&check_id);
			count++;
		}while(check_show_order_id(order,m,check_id)==false);
		
		system("cls");
		printf("\n\tID Acpect!\n");
		printf("\n\tID: %s\n", check_id);
		
		j=0;
		for(h=0;h<m;h++){
			if(strcmp(check_id,order[h].ID_Order)==0){
				show_order(order,h+1,t);
				j++;
			}
		}
		if(j==0){
			system("cls");
			printf("\n\tOrder ID: %s",check_id);
			printf("\n\n\tNo Orders Satisfied!\n");
		}
	}
}

// ham hien thi so luong sp ban ra, nhom theo tung loai sp
void show_pr_quanlity(struct Order order[], int m, int t[]){
	system("cls");
	if(m==0){
		printf("\n\tNo orders yet!\n");
	}
	else{
		char month[3];
		count = 0;
		do{
			if(count>0){
				system("cls");
				printf("\n\tInvalid Month!\n");
			}
			printf("\n\tMonth: ");
			fflush(stdin); scanf("%s",month);
			count++;
		}while(check_show_order_month(month)==false);
		
		system("cls");
		printf("\n\tMonth Acpect!\n");
		printf("\n\tMonth: %s\n\n", month);
		
		bool a = false;
		for(b=0;b<m;b++){
			if(order[b].ID_Order[2]==month[0] && order[b].ID_Order[3]==month[1]){
				a = true;
			}
		}
		if(a==true){
			printf("%15s", "Product ID");
			printf("%25s", "Product Name");
			printf("%25s", "Product Price");
			printf("%25s", "Product Quantity\n");
			
			int y = 0;
			struct list_product Sum_Pr[max_size];	
				
			for(h=0;h<m;h++){
				if(order[h].ID_Order[2]==month[0] && order[h].ID_Order[3]==month[1]){
					for(k=0;k<t[h];k++){
						strcpy(Sum_Pr[y].product_id, order[h].order_pr[k].product_id);
						strcpy(Sum_Pr[y].product_name, order[h].order_pr[k].product_name);
						Sum_Pr[y].product_price = order[h].order_pr[k].product_price;
						Sum_Pr[y].product_quantity = order[h].order_pr[k].product_quantity;
						y++;
					}
				}
			}
			
			for(h=0;h<y;h++){
				for(k=h+1;k<y;k++){
					if(strcmp(Sum_Pr[h].product_id,Sum_Pr[k].product_id)==0){
						Sum_Pr[h].product_quantity += Sum_Pr[k].product_quantity;
						for(l=k;l<y;l++){
							Sum_Pr[l] = Sum_Pr[l+1];
						}
						y--;
					}
				}
			}
			
			for(h=0;h<y;h++){
				printf("%15s",Sum_Pr[h].product_id);
				printf("%25s",Sum_Pr[h].product_name);
				printf("%25d",Sum_Pr[h].product_price);
				printf("%24d\n",Sum_Pr[h].product_quantity);
			}
		}
		else{
			printf("\n\tNo orders this month!\n");
		}
	}
}

// ham hien thi 5 san pham ban chay nhat trong 1 thoi gian cu the
void show_5_pr_quanlity(struct Order order[], int m, int t[]){
	system("cls");
	if(m==0){
		printf("\n\tNo orders yet!\n");
	}
	else{
		char month[3];
		count = 0;
		do{
			if(count>0){
				system("cls");
				printf("\n\tInvalid Month!\n");
			}
			printf("\n\tMonth: ");
			fflush(stdin); scanf("%s",month);
			count++;
		}while(check_show_order_month(month)==false);
		
		system("cls");
		printf("\n\tMonth Acpect!\n");
		printf("\n\tMonth: %s\n\n", month);
		
		bool a = false;
		for(b=0;b<m;b++){
			if(order[b].ID_Order[2]==month[0] && order[b].ID_Order[3]==month[1]){
				a = true;
			}
		}
		if(a==true){
			printf("%15s", "Product ID");
			printf("%25s", "Product Name");
			printf("%25s", "Product Price");
			printf("%25s", "Product Quantity\n");
			
			int y = 0;
			struct list_product Sum_Pr[max_size];	
				
			for(h=0;h<m;h++){
				if(order[h].ID_Order[2]==month[0] && order[h].ID_Order[3]==month[1]){
					for(k=0;k<t[h];k++){
						strcpy(Sum_Pr[y].product_id, order[h].order_pr[k].product_id);
						strcpy(Sum_Pr[y].product_name, order[h].order_pr[k].product_name);
						Sum_Pr[y].product_price = order[h].order_pr[k].product_price;
						Sum_Pr[y].product_quantity = order[h].order_pr[k].product_quantity;
						y++;
					}
				}
			}
			
			for(h=0;h<y;h++){
				for(k=h+1;k<y;k++){
					if(strcmp(Sum_Pr[h].product_id,Sum_Pr[k].product_id)==0){
						Sum_Pr[h].product_quantity += Sum_Pr[k].product_quantity;
						for(l=k;l<y;l++){
							Sum_Pr[l] = Sum_Pr[l+1];
						}
						y--;
					}
				}
			}
			
			for(h=0;h<y;h++){
				for(k=h+1;k<y;k++){
					if(Sum_Pr[h].product_quantity < Sum_Pr[k].product_quantity){
						struct list_product temp = Sum_Pr[h];
						Sum_Pr[h] = Sum_Pr[k];
						Sum_Pr[k] = temp;
					}
				}
			}
			
			for(h=0;h<5;h++){
				printf("%15s",Sum_Pr[h].product_id);
				printf("%25s",Sum_Pr[h].product_name);
				printf("%25d",Sum_Pr[h].product_price);
				printf("%24d\n",Sum_Pr[h].product_quantity);
			}
		}
		else{
			printf("\n\tNo orders this month!\n");
		}
	}
}


void readd(){
		 system("cls");
		add(pr,&n);
		printf ("\n\n");
		printf ("Do you want to continue.(Y/N) ---> ");
	    
	    char bh= 'y';
		getchar();
		scanf ("%c",&bh);
		while (bh == 'y' || bh == 'Y') {
			system("cls");
			readd();
		} product();
}


void product (void) {
    	system("cls");
	printf("\n        Please select function: \n");
	printf("___________________________________________________________________\n\n\n");
		
		printf("\n  1. Add New Product\n");
		printf("\n  2. List all Products\n");
		printf("\n  3. Search for Product\n");
		printf("\n  4. Edit a Product\n");
		printf("\n  5. Delete a Product\n");
		printf("\n  0. Return\n");
    	printf("\n\nEnter Your Choice: ");
    	
    	int choice;
	    scanf("%d",&choice);
    		if(choice==0){
    			system("cls");
    			mainmenu();
				}	
    		else if(choice==1){
			    system("cls");
			    add(pr,&n);
		printf ("\n\n");
		printf ("Do you want to continue.(Y/N) ---> ");
	    
	    char bh= 'y';
		getchar();
		scanf ("%c",&bh);
		while (bh == 'y' || bh == 'Y') {
			system("cls");
			readd();
		} product();
			    }
			else if(choice==2){
			    system("cls");
				display(pr,n);
     	        getch();
	            product();
			     }   
		    else if(choice==3){
			    system("cls");
			    idx = find(pr, n);
			    if (idx == -1)
			        printf("\n\nNo item found.\n\n");
			    else
			    {
			    	printf("\n%15s%25s%25s%25s", "Product ID", "Product Name", "Product Price", "Product Quantity\n");
					printf("==========================================================================================\n");
					printf("%15s%25s%25d%24d\n", pr[idx].product_id, pr[idx].product_name, pr[idx].product_price, pr[idx].product_quantity);
				}
           getch();
	       product();
  }
    		else if(choice==4){
	system("cls");
			    idx = find(pr, n);
			    if (idx == -1)
			        printf("\n\nNo item found.\n\n");
			    else
			    	edit(pr,idx);
	       getch();
	       product();
}
			else if(choice==5){
			    system("cls");
			    idx = find(pr, n);
			    if (idx == -1)
			        printf("\n\nNo item found.\n\n");
			    else
			    	del(&n);
		   getch();
	       product();
			   } 
			else{
				printf("\n\tInvalid choice\n");
				getch();    
		        product ();
			}
		
}

void show (void){
	
	system("cls");
	printf("\n        Please select function: \n");
	printf("___________________________________________________________________\n\n\n");
	printf("\n    1. List all products in alphabetical order from 'A' to 'Z'\n");
	printf("\n    2. List all orders in a given month\n");
	printf("\n    3. Show Details Of An Order With Its Id\n");
	printf("\n    4. List Of Products In Ascending Order Of Price\n");
	printf("\n    5. Number Of Products Sold In The Month, Grouped By Product\n");
	printf("\n    6. Show 5 Best Selling Products In A Specific Time Period\n");
	printf("\n    0. Return");
	
	printf("\n\n\tEnter Your Choice: ");
		    int choice;
	        scanf("%d",&choice);
			
			if(choice==1)			
				{
					if(n==0){
						system("cls");
						printf("\n\tEmpty\n");
					}
					else{
						show_pr_az(pr,n);
					}
				
					printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						show ();
					}
				}
				else if(choice==2)			
				{
					show_order_month(order,m,t);
					printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						show ();
					}
				}
				else if(choice==3)		
				{
					show_order_id(order,m,t);
					printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						show ();
					}

				}
				else if(choice==4)		
				{
					if(n==0){
						system("cls");
						printf("\n\tItem list is empty!\n");
					}
					else{
						show_pr_price(pr,n);
					}
					printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						show ();
					}
					
				
				}
				else if(choice==5)				
				{
					show_pr_quanlity(order,m,t);
					
					printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						show ();
					}
					
				}
				else if(choice==6)		
				{
					show_5_pr_quanlity(order,m,t);
					
					printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						show ();
					}
					
				
				}
				else if(choice==0)			
				{
				mainmenu();
				}
				else
				{
					 show();
				}
	}
			
void orders (void){
	Customer(cus);
			system("cls");
			if(n>0){		// neu trong kho co sp thi ban co the mua hang
				while(true){
					show_cus(cus);
					display(pr,n);
					if(p==0){
						printf("\n\tYour Cart Is Empty!\n");
					}
					else{
						printf("\n\tYour Cart\n");
						show_cus_pr(cus_pr, p);
					}
					f:
					j=0;
					char input_3[7];
					int count = 0;
					do{
						if(count>0){
							system("cls");
							show_cus(cus);
							display(pr,n);
							if(p==0){
								printf("\n\tYour Cart Is Empty!\n");
							}
							else{
								printf("\n\tYour Cart\n");
								show_cus_pr(cus_pr, p);
							}
							printf("\n\tInvalid ID!\n");
						}
						printf("\n\tEnter Product ID To Buy: ");
						scanf("%s", &input_3);
						count++;
					}while(check_id(input_3)==false || check_id_cus_pr(pr,n,input_3)==false);
					
					system("cls");
					show_cus(cus);
					display(pr,n);
					if(p==0){
						printf("\n\tYour Cart Is Empty!\n");
					}
					else{
						printf("\n\tYour Cart\n");
						show_cus_pr(cus_pr, p);
					}
					printf("\n\tAcpect ID!\n");
					printf("\n\tEnter Product ID To Buy: %s", input_3);
					printf("\n\tEnter Quantity To Buy  : ");
					int input_4;
					scanf("%d", &input_4);
					for(i=0;i<n;i++){
						if(strcmp(input_3, pr[i].product_id)==0){
							buy(pr,i,cus_pr,&p,input_4,input_3);
						}
					}
					if(j==1){
						system("cls");
						show_cus(cus);
						display(pr,n);
						if(p==0){
							printf("\n\tYour Cart Is Empty!\n");
						}
						else{
							printf("\n\tYour Cart\n");
							show_cus_pr(cus_pr, p);
						}
						printf("\n\tProduct quantity is not enough!\n");
						goto f;
					}
					else if(j==2){
						system("cls");
						show_cus(cus);
						display(pr,n);
					}
					if(p>0){
						printf("\n\tYour Cart\n");
						show_cus_pr(cus_pr, p);
					}
					printf("\n\t1.Continue Buying");
					printf("\n\t2.Pay");
					printf("\n\t0.Return\n\n");
					printf("\tEnter Your Choice: ");
					int input_5;
					scanf("%d", &input_5);
					if(input_5==0){
						system("cls");
						mainmenu();
					}
					if(input_5==1)
						system("cls");
					if(input_5==2){
						break;
					}
				}
			}
			else{	// neu trong kho khong co sp thi ban se nhan duoc thong bao va khong the mua hang
				show_cus(cus);
				printf("\n\tItem list is empty!\n");
				printf("\n\t1.Return\n\n");
				printf("\tEnter Your Choice: ");
				int input_2;
				scanf("%d", &input_2);
				if(input_2==1){
					system("cls");
					mainmenu();
				}
			}
			system("cls");
			add_to_order(pr,&m,cus,order,t,cus_pr,p); // luu thong tin trong gio hang vao bill
			show_order(order,m,t);		// hien thi bill
			decide(order,m);			// hien thi thong bao co muon thanh toan hay khong
			if(order[m-1].State_Order == true){ // neu dong y thanh toan
				system("cls");
				show_order(order,m,t);
				p = 0;
				printf("\n\tOrder State: Successful\n");		// trang thai dat hang: thanh cong
				printf("\n\tThank You For Purchasing Our Product!\n");
				printf("\n\t1.Back To Menu\n");
				printf("\t0.Exit\n");
				printf("\n\tEnter Your Choice: ");
				int input_6;
				scanf("%d",&input_6);
				if(input_6==1){
					mainmenu();
				}
			}
			else{		// neu khong muon dat hang
				system("cls");
				return_product(order,&m,pr,t,&p,n);		// tra lai sp trong gio hang ve kho
				printf("\n\tOrder State: Unsuccessful\n");		// trang thai dat hang: that bai
				printf("\n\tThank You For Coming To Our Store\n");
				printf("\n\t1.Back To Menu\n");
				printf("\t0.Exit\n");
				printf("\n\tEnter Your Choice: ");
				int input_6;
				scanf("%d",&input_6);			
				if(input_6==1){
					mainmenu();
				}
			}
			printf("\n   Press to return\n\n");
					getchar();
					if(getchar()){
						orders ();
					}
	
}		

void exited (void){
	
		printf("\nEnter the Choice:\n\n 1. xxx 0. yyy\n");
	    scanf("%d",&ch);
	
	    switch (ch)
	    {
	    case 1:
	        mainmenu();
	    case 0:
	 	    read(pr,&n);
	        break;
	    default:
	        printf("Invalid choice");
	        exited ();
	        break;
	    }
}

void conti (void){
     	printf ("\n\n");
		printf ("Do you want to continue.(Y/N) ---> ");
	    
	    char bh= 'y';
		getchar();
		scanf ("%c",&bh);
		while (bh == 'y' || bh == 'Y') {
			///xxx
		} ///yyy
}

