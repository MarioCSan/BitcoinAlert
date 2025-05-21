#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

#define SOUND_FILE_NAME "You-Suffer.wav"

#ifdef _WIN32
#define SOUND_COMMAND SOUND_FILE_NAME
#else
#endif

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
    if (PlaySound(SOUND_COMMAND, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT) == 0) {
        printf("Error playing sound file '%s'. Windows Error Code: %lu\n", SOUND_FILE_NAME, GetLastError());
    } 
#elif __APPLE__
    char mac_command[256];
    sprintf(mac_command, "afplay \"%s\"", SOUND_FILE_NAME);
    int result = system(mac_command);
    if (result != 0) {
        printf("Error playing sound file '%s' using afplay. Exit code: %d\n", SOUND_FILE_NAME, result);
    }
#else // Linux
    char linux_command[256];
    sprintf(linux_command, "aplay \"%s\"", SOUND_FILE_NAME);
    int result = system(linux_command);
    if (result != 0) {
        printf("Error playing sound file '%s' using aplay. Exit code: %d\n", SOUND_FILE_NAME, result);
    }
#endif
}

int main() {
    double highest_price = PRICE_THRESHOLD;

    while (1) {
        double price = get_bitcoin_price();

        if (price > 0) {
            printf("Bitcoin price: $%.2f\n", price);
            if (price < PRICE_THRESHOLD) {
                printf("Alert! Bitcoin price is below $%d.\n", PRICE_THRESHOLD);
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
