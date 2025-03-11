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

int main(){
    unsigned int game_code = 0;

    srand(time(NULL));

    printf("Hello! 今天想玩甚麼遊戲呢？ \
        \n1. Black Jack\n");
    scanf("%d", &game_code);

    switch (game_code){
    case 1:
        blackjack();
        break;
    }
    
	return 0;
}

card *newDeck(){
    card *deck = new card[52];
    int i;
    for(i=0;i<52;i++){
        deck[i].number = i%13+1;
        deck[i].symbol = i/13+1;
    }

    return deck;
}

void deleteDeck(card *deck){
    delete deck;
}

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

void blackjack(){
    card *deck = newDeck();
    unsigned int player = 1;

    printf("請輸入玩家人數：");
    scanf("%d", &player);
    shuffle(deck);

    // 遊戲開始發兩張牌
    for(int i=0;i<player;i++){
        printf("玩家%d的牌：\n", i+1);
        printf("%d %d\n", deck[i].number, deck[i].symbol);
        printf("%d %d\n", deck[player + i].number, deck[player + i].symbol);
    }

    // 遊戲結束就刪除牌組
    deleteDeck(deck);
}
