/***********************************************************************************
 * 放上github避免檔案出錯:                                                          *
 * My github: https://github.com/sanoesogood/Introduction-to-Computer-Science_113 *
 *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/* 上課時老師有說過，數字用1, 2, ..., 13(可用 4 bits 表示)，花色用1, 2, 3, 4(可用 2 bits 表示)，
   所以一張牌最少需要用6 bits表示。為了對齊一個byte，所以花色用4 bits，代表儲存一張牌的資訊要用1 byte
*/
typedef unsigned char uint8_t;  // 方便分別我的變數是要存字元還是數字(用<stdint.h>比較好)

/* 使用C語言中的 bit field，把數字和花色合併在1 byte中，減少記憶體的使用 */
typedef struct {
    uint8_t number: 4;
    uint8_t symbol: 4;
} card;

/**
 * 目標：模擬人的洗牌方式
 * 使用方法：上課說的第二種方法(像比倒愛心然後用兩手大拇指撥牌的那種)
 * 
 * 步驟：牌組從index 0開始算，切一半後，得到左半：0~25，右半：26~51
 * 假設牌面朝下，從左半邊開始洗，每次都剛好只撥到一張，則第25張會在最下面，然後是右半邊的第51張，
 * 再來是左邊的第24張，右邊的第50張，以此類推，一直交錯堆上去直到左右兩邊的牌都洗完
 * 不過現實中洗牌時，不可能每次都控制切一半的牌，所以我有設定maxOffset，即切牌時的誤差
 * 然後是洗牌時，每次撥牌最大的數量設定為maxBatch，模擬人的洗牌方式和手殘的情況
 */
int main() {
    card C[52], P[52];
    card *ptr1 = NULL;
    card *ptr2 = NULL;
    card *tmp = NULL;

    int LTop = 25, RTop = 25;
    int Top = -1;
    int r = 0;

    int maxBatch = 1;
    int maxOffset = 1;
    int times = 1;

    srand(time(NULL));

    /* 創建牌組 */
    for(int i=0; i<52; i++){
        C[i].number = i % 13 + 1;
        C[i].symbol = i / 13 + 1;
    }

    /* 輸入參數 
       說明：靈活程度決定maxBatch，第六感等級決定maxOffset，洗牌次數決定times
       不靈活的人可能撥牌都在3張以上；第六感不好的人可能切牌誤差都在10張以上；洗牌次數至少1次
    */
    printf("請輸入大拇指靈活程度(1最靈活)，第六感等級(1最高), 洗牌次數(至少1次): ");
    scanf("%d %d %d", &maxBatch, &maxOffset, &times);
    if(maxBatch < 1 || maxOffset < 1 || times < 1){
        printf("error. try again.\n");
        return 0;
    }

    /* ptr1指向的是欲洗牌的牌組，ptr2指向的是洗牌後的牌組 */
    ptr1 = C;
    ptr2 = P;

    while(times--){
        r = rand() % maxOffset; // 切牌誤差
        if(rand() % 2 == 0){
            r = -r;
        }

        LTop = 25 + r;
        RTop = 25 - r;
        Top = -1;

        while(LTop != -1 || RTop != -1){
            r = rand() % maxBatch + 1; // 撥牌數量
            while (r > 0 && LTop != -1){
                Top++;
                ptr2[Top] = ptr1[LTop];
                LTop--;
                r--;
            }

            r = rand() % maxBatch + 1;
            while(r > 0 && RTop != -1){
                Top++;
                ptr2[Top] = ptr1[51-RTop];
                RTop--;
                r--;
            }
        }

        /* 交換 C 和 P 牌組 */
        tmp = ptr1;
        ptr1 = ptr2;
        ptr2 = tmp;
    }

    /* 第一次洗牌時，ptr1 = C，ptr2 = P；洗完後變成ptr1 = P，ptr2 = C；
       第二次洗牌時，ptr1 = P，ptr2 = C，洗完後變成ptr1 = C，ptr2 = P，
       洗完後的牌會在ptr1中，所以要印出ptr1指向的內容
    */
    printf("您的洗牌結果：\n");
    for(int i = 0; i < 52; i++){
        printf("%d %d\n", ptr1[i].number, ptr1[i].symbol);
    }
    printf("----- top\n");

    return 0;
}
