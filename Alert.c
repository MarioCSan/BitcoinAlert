#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#define SOUND_COMMAND "You-Suffer.wav"  // Archivo de sonido para Windows
#else
#define SOUND_COMMAND "afplay You-Suffer.wav"  // Comando para macOS
#endif

// Umbral para el precio de Bitcoin
#define PRICE_THRESHOLD 66767

#define API_KEY "7350a73c-9677-4d06-bba3-665d50999607"

double get_bitcoin_price() {
    char command[512];
    sprintf(command, "curl -s -H \"X-CMC_PRO_API_KEY: %s\" \"https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?id=1&convert=USD\" > bitcoin_price.txt", API_KEY);

    system(command);

    FILE *fp = fopen("bitcoin_price.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return -1;
    }

    char buffer[1024];
    double price = -1;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *price_ptr = strstr(buffer, "\"price\":");
        if (price_ptr != NULL) {
            price = atof(price_ptr + 8);
            break;
        }
    }

    fclose(fp);
    return price;
}

void play_alert_song() {
#ifdef _WIN32
    if (PlaySound(SOUND_COMMAND, NULL, SND_FILENAME | SND_ASYNC) == 0) {
        printf("Cannot reproduce sound: %lu\n", GetLastError());
    } else {
        printf("Playing sound on Windows\n");
    }
#elif __APPLE__
    int result = system(SOUND_COMMAND);  // afplay para macOS
    if (result != 0) {
        printf("Cannot reproduce sound on macOS.\n");
    } else {
        printf("Playing sound on macOS\n");
    }
#else
    int result = system("aplay You-Suffer.wav");  // aplay para Linux
    if (result != 0) {
        printf("Cannot reproduce sound on Linux.\n");
    } else {
        printf("Playing sound on Linux\n");
    }
#endif
}

int main() {
    while (1) {
        double price = get_bitcoin_price();
        double highest_price = PRICE_THRESHOLD; 
        if (price > 0) {
            printf("Bitcoin price: $%.2f\n", price);
            if (price < PRICE_THRESHOLD) {
                printf("Alert! Bitcoin price is below $%d.\n", PRICE_THRESHOLD);
                //play_alert_song();
            } else if (price > highest_price) {
                printf("Alert! New ATH $%.2f\n", price);
                play_alert_song();
                highest_price = price; 
            }
        } else {
            printf("Cannot obtain BTC price\n");
        }
        
        sleep(60);
    }
    return 0;
}
