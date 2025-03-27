/*************************************************************************
 * format: UTF-8                                                         *
 * source:                                                               *
 * https://github.com/sanoesogood/Introduction-to-Computer-Science_113/  *
 * tree/main/shuffle/game.cpp                                            *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int number;
    int symbol;
} card;

card *newDeck();
void deleteDeck(card *deck);
void shuffle(card *deck);
void blackjack();
void bigtwo();

int main(){
    unsigned int game_code = 0;

    srand(time(NULL));

    printf("Hello! Which game do you want to play today?\n");
    printf("1. Black Jack\n2. Big Two\n");

    scanf("%d", &game_code);

    switch (game_code){
    case 1:
        blackjack();
        break;
    case 2:
        bigtwo();
        break;
    default:
        printf("This game code does not exist.\n");
        break;
    }
    
	return 0;
}

card *newDeck(){
    card *deck = new card[52];
    for(int i=0; i<52; i++){
        deck[i].number = i%13+1;
        deck[i].symbol = i/13+1;
    }

    return deck;
}

void deleteDeck(card *deck){
    delete deck;
}

// 洗牌方法: by 課輔系統上的 [shuffle] aa.cpp
void shuffle(card *deck){
    int i, k1, k2;
    card temp;
    for(i=0;i<1000;i++){
        k1 = rand()%52;
        k2 = rand()%52;

        temp = deck[k1];
        deck[k1] = deck[k2];
        deck[k2] = temp;
    }
}

/**
 * 二十一點可以很多人玩，一開始每人先發兩張牌
 */
void blackjack(){
    card *deck = newDeck();
    unsigned int n = 1;

    printf("請輸入玩家人數(1~10)：");
    scanf("%d", &n);
    if(n < 1 || n > 10){
        printf("%d個人不能玩這個遊戲哦！\n", n);
    }
    shuffle(deck);

    // 遊戲開始發兩張牌
    printf("-----Round 0-----\n");

    // 第k張==>player==>number symbol
    for(int i=0; i<2*n; i++){
        printf("%d==>player%d==>%d %d\n", i + 1, i % n + 1, deck[i].number, deck[i].symbol);
    }

    // 遊戲結束就刪除牌組
    deleteDeck(deck);
}

/**
 * 大老二~二四個人玩，每人發13張
 */
void bigtwo(){
    card *deck = newDeck();
    unsigned int n = 2;
    
    printf("請輸入玩家人數(2~4)：");
    scanf("%d", &n);
    if (n < 2 || n > 4){
        printf("%d個人不能玩這個遊戲哦！\n", n);
    }
    shuffle(deck);

    // 第k張==>player==>number symbol
    printf("-----Round 0-----\n");
    for(int i=0; i<13*n; i++){
        printf("%d==>player%d==>%d %d\n", i + 1, i % n + 1, deck[i].number, deck[i].symbol);
    }

    // 遊戲結束就刪除牌組
    deleteDeck(deck);
}
