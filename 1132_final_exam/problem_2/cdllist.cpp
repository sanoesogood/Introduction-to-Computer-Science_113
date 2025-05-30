/**  
 * If Chinese text is not displayed, please go to (very important!): 
 * https://github.com/sanoesogood/Introduction-to-Computer-Science_113/tree/main/1132_final_exam/problem_2/cdllist.cpp

 * 在壓縮檔中，有我畫圖來解決雙向環狀鏈結串列的筆記 (不用畫的很難想出來)
 * 
 * 這是我用「老師給的程式」改的，在原程式的基礎上，我改動了: 
 * 
 * 1. 透過 if(fscanf(fp, "%s %d %d %d", x->name, &x->no, &x->mid, &x->final) != 4)
 *    來判斷資料是否讀到最後一行，而不是用 feof() (在 cplusplus 上學到的)
 * 
 * 2. 判斷 top 是否為空，並印出錯誤訊息 
 *
 * 3. insert() 可以在 top == NULL 時加入資料
 * 
 * 4. 因為雙向環狀鏈結串列如果用 while(temp->next != temp){temp = temp->next} 
 *    時，會讀不到最一開始的資料，所以我都用 do-while 迴圈。首先讓 temp = top，
 *    先印出資料然後將 temp = temp->next，直到 while == top，可以避免讀不到最一
 *    開始的資料的問題
 * 
 * 5. 把 free() 改成 delete[] (用 new[] 新增，用 delete[] 刪除感覺比較合理)
 * 
 * 6. 增加 debug mode 跟用 show_memory() 來印出記 list 內的記憶體的功能
 *    (不然我不知道雙向環狀陣列有沒有成功寫出來)
 * 
 * 7. 增加兩種印出方式 (升序: ascending order & 降序: descending order)
 * 
 * 8. create() 中關掉了 student.txt
 * 
 * 9. 排版改了一下
 */

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>

struct student{
	char name[10];
	int no;
	int mid;
	int final;
	struct student *next;
	struct student *prev;
};
struct student *top = NULL;

void create();
void query();
void insert();
void delete_data();
void show();
void show_inverse();

#if DEBUG
void show_memory();
#endif

int main(){
  	int choice = 0;

  	while(1){
		printf("1: create list\n");
		printf("2: query\n");
		printf("3: insert\n");
		printf("4: delete\n");
		printf("5: show list by ascending order\n");
		printf("6: show list by descending order\n");
		printf("7: quit\n");
		#if DEBUG
		printf("#debug\n");
		printf("8: show memory\n\n");
		#endif
		printf("\nchoice: ");

		scanf("%d", &choice);

		switch(choice){
		case 1:	
			printf("=======1: create\n");
			create();
			break;
		case 2:	
			printf("========2: query\n");
			query();
			break;
		case 3:	
			printf("========3: insert\n");
			insert();
			break;
		case 4:	
			printf("========4: delete\n");
			delete_data();
			break;
		case 5:	
			printf("========5: show by ascending order\n");
			show();
			break;
		case 6:
			printf("========6: show by descending order\n");
			show_inverse();
			break;
		case 7: 
			printf("========7: quit\n");
			return 0;
		#if DEBUG
		case 8:
			printf("========8: show memeory\n");
			show_memory();
			break;
		#endif
		default:
			printf("========-1: choice not found.\n");
			return 0;				
		}
		printf("========\n");
    }
	return 0;	
}

void create(){ 	
	struct student *x = NULL;
	FILE *fp = NULL;

	fp = fopen("student.txt", "r");
	if(fp == NULL){
		printf("========-1: error opening file.");
		return;
	}

	while(1){
		x = new struct student[1];

		if(fscanf(fp, "%s %d %d %d", x->name, &x->no, &x->mid, &x->final) != 4){
			break;
		}

		#if DEBUG
		printf("read: %s %d %d %d\n", x->name, x->no, x->mid, x->final);
		#endif

		if(top == NULL){
			x->next = x;
			x->prev = x;
			top = x;
		}
		else{
			x->next = top;
			x->prev = top->prev;
			top->prev->next = x;
			top->prev = x;
			top = x;
		}
	}

	printf("created successfully.\n");
	fclose(fp);

	return;
}

void query(){
	int key;
	struct student *temp = top;

	if(top == NULL){
		printf("no data in the list.\n");
		return;
	}

	scanf("%d", &key);

	do{
		if(temp->no == key){
			printf("%s %d %d %d\n", temp->name, temp->no, temp->mid, temp->final);
			return;	
		}
		temp = temp->next;
	}while(temp != top);

	printf("key = %d not found.\n", key);

	return;
}

void insert(){
	struct student *x = NULL;

	x = new struct student[1];

	printf("format: name no mid final\n");
	scanf("%s %d %d %d", x->name, &x->no, &x->mid, &x->final);
	if(top == NULL){
		x->next = x;
		x->prev = x;
		top = x;
	}
	else{
		x->next = top;
		x->prev = top->prev;
		top->prev->next = x;
		top->prev = x;
		top = x;
	}

	return;
}

void delete_data(){
	if(top == NULL){
		printf("no data in the list.\n");
		return;
	}

	int key;
	struct student *temp = top, *prev = top;

	scanf("%d", &key);
	
	do{
		if(temp->no == key){
			if(temp->next == temp){
				delete[] temp;
				top = NULL;
			}
			// // 後來發現不需要特別為刪除開頭寫一個方法
			// else if(temp == top){
			// 	top->prev->next = top->next;
			// 	top->next->prev = top->prev;
			// 	top = top->next;
			// 	delete[] temp;
			// }
			else{
				prev = temp->prev;
				prev->next = temp->next;
				temp->next->prev = prev;
				if(temp == top){
					top = temp->next;
				}
				delete[] temp;
			}

			printf("delete key = %d\n", key);
			return;	
		}
		temp=temp->next;
	}while(temp != top);

	printf("key = %d not found.\n", key);
	
	return;
}

// 按插入時間顯示 (最新插入的在最前面)
void show(){
	if(top == NULL){
		printf("no data in the list.\n");
		return;
	}

	struct student *temp = top;

	do{
		printf("%s %d %d %d\n", temp->name, temp->no, temp->mid, temp->final);
		temp = temp->next;
	}while(temp != top);

	return;
}

// 按插入時間顯示 (最早插入的在最前面)
void show_inverse(){
	if(top == NULL){
		printf("no data in the list.\n");
		return;
	}

	struct student *temp = top->prev;

    do{
        printf("%s %d %d %d\n", temp->name, temp->no, temp->mid, temp->final);
        temp = temp->prev;
    }while(temp != top->prev);

	return;
}

#if DEBUG
void show_memory(){
	struct student *temp = top;

	if(temp == NULL){
		printf("no data in the list.\n");
		return;
	}

	do{
		printf("x_name: %s, x_no: %d, x_mem: %p, p: %p, n: %p\n", \
			    temp->name, temp->no, temp, temp->prev, temp->next);
		temp = temp->next;
	}while(temp != top);

	return;
}
#endif
