/**----------------------------------------------------------*
 * first version: 2024/12/5                                  *
 * github: https://github.com/sanoesogood                    *
 *                                                           *
 * revised: 2024/12/13                                       *
 *----------------------------------------------------------**/

/**
 * 目標: 輸出一個「完美」的星星金字塔 (即三角形)
 * 
 * 推導: 
 * 每層擁有的星星數為 1, 3, 5, ..., 2n - 1，為一公差為 2 的等差數列
 * 當 n >= 1，n 為正整數時，輸入層數 n 後，將決定最後一層的字元總數 length 為 2n - 1，又每層的空格數 = 總長度 - 該層總星星數
 * 第 1 層會有 (2n - 1) - 1 = 2(n - 1) 格空格
 * 第 2 層會有 (2n - 1) - 3 = 2(n - 2) 格空格
 * .
 * .
 * 第 i 層會有 (2n - 1) - (2i - 1) = 2(n - i) 格空格
 * .
 * .
 * 第 n - 1 層會有 (2n - 1) - (2(n - 1) - 1) = 2(n - (n - 1)) = 2 格空格
 * 第 n 層會有 (2n - 1) - (2n - 1) = 2(n - n) = 0 格空格
 * 
 * 又此金字塔左右對稱，左側空格數 = 右側空格數，所以第 i 層的星星兩側皆有有 n - i 格空格
 * ***所以只要先輸出 n - i 格空格，再輸出 2i - 1 顆星星，最後再輸出 n - i 格空格就能得到一座完美對稱的星星金字塔了!***
 * 
 * 注意: 
 * 因為層數太多的話 console 會塞不下完整的金字塔，可以考慮使用 char 作為實作用的資料型態
 *   - 不過用 int 可以在電腦上輸出 20 億層的金字塔ㄟ !!!
 * 然後 layer 使用有號數 (e.g. int)，其他變數如 length 使用無號數 (e.g. unsigned int) 會比較好，因為
 *   - 若資料型態為 char (1 byte)，透過 length = 2*layer - 1 得知: 當 layer <= 128時，length <= 255，剛好不會溢位，又 layer 為 signed char，故最大層數為 2^7 - 1 = 127
 *     若用 int ，即 layer <= 2^31 - 1 時，其他變數皆不會溢位
 */
#include <stdio.h>

void method_1(int layer);
void method_2(int layer);

void clean_input_buffer();
void pause();

int main(){
    int method = 0;
    int layer = 0;
    
    printf("本程式提供兩種方法輸出金字塔，請輸入想使用的方法 (1 or 2): ");
    scanf("%d", &method);
    clean_input_buffer();

    printf("請輸入想要的金字塔層數: ");
    scanf("%d", &layer);
    clean_input_buffer();

    if(layer <= 0){
        printf("層數請輸入大於等於 1 的數 !\n");
        pause();
        return 0;
    } 

    switch(method){
    case 1:
        method_1(layer);
        break;
    
    case 2:
        method_2(layer);
        break;

    default:
        printf("方法請輸入數字 1 或 2 !\n");
        pause();
        return 0;
    }

    printf("此金字塔共有%d層\n", layer);
    pause();

    return 0;
}

/**
 * 方法一: 由左至右分別輸出 空格-星星-空格
 * 變數有: 
 *   - layer: 總層數
 *   - space: 第 n 層的空格數
 *   - length: 第 n 層的星星數量
 *   - n: 第 n 層，其中 1 <= n <= layer
 *   - ch: 第 n 層的第 ch 個字元，其中 0 <= ch < length
 * 
 *  優點: 直覺、易撰寫
 *  缺點: 要寫 3 個 for 迴圈
 */ 
void method_1(int layer){
    unsigned int space = 0,
                 length = 0,
                 n = 0,
                 ch = 0;

    for(n=1; n<=layer; n++){
        space = layer - n;
        length = 2*n - 1;

        for(ch=0; ch<space; ch++){
            printf(" ");
        }
        for(ch=0; ch<length; ch++){
            printf("*");
        }
        for(ch=0; ch<space; ch++){
            printf(" ");
        }
        printf("\n");
    }
}

/**
 * 方法二: 紀錄星星的起始與結束位置後，輸出 空格-星星-空格
 * 變數有: 
 *   - layer: 總層數
 *   - max_length: 最後一層的總字元數
 *   - star_i, star_f: 紀錄星星的起始與結束位置
 *   - n: 第 n 層，其中 1 <= n <= layer
 *   - ch: 第 n 層的第 ch 個字元，其中 0 <= ch < length
 * 
 * 優點: 不用很多個 for 迴圈
 * 缺點: 每次迴圈需要判斷 ch 的值是否在 0 <= ch < length 內，速度較慢
 */ 
void method_2(int layer){
    unsigned int max_length = 0,
                 star_i = 0, star_f = 0,
                 n = 0,
                 ch = 0;

    max_length = 2 * layer - 1;

    for(n=1; n<=layer; n++){
        star_i = layer - n;
        star_f = max_length - star_i - 1;

        for(ch=0; ch<max_length; ch++){
            if(ch >= star_i && ch <= star_f){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}

/**
 * 清空輸入緩衝區
 * 
 * 也可以使用以下方法: 
 *   scanf() 支援 regular expression
 *   使用 %[^\n] 查找除了 \n 以外的字串，再利用 * 丟棄此字串
 *   之後透過 getchar() 讀取到 \n，此時已清空緩衝區，能夠避免兩個連續的 scanf() 讀到上一個 scanf() 輸入按下的 Enter (即 \n)
 * 
 * Code:
 *   scanf("%*[^\n]");
 *   getchar();
 */
void clean_input_buffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

/**
 * 阻塞用，讓使用者看到輸出結果或錯誤訊息
 */
void pause(){
    printf("按 Enter 鍵退出...");
    getchar();
}