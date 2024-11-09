#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>


// Umbral para el precio de Bitcoin
#define PRICE_THRESHOLD 66767

#define API_KEY "7350a73c-9677-4d06-bba3-665d50999607"

double get_bitcoin_price() {
   
    char command[512];
    sprintf(command, "curl -s -H \"X-CMC_PRO_API_KEY: %s\" \"https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?id=1&convert=USD\" > bitcoin_price.txt", API_KEY);

    system(command);

    FILE *fp = fopen("bitcoin_price.txt", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo temporal\n");
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
    const char* filename = "You-Suffer.wav"; 

    if (PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC) == 0) {
        
        printf("Cannot reproduce: %lu\n", GetLastError());
    } else {
        printf("Playing: %s\n", filename);
    }
}


int main()
{
    while (1) {
        double price = get_bitcoin_price();
        if (price > 0) {

            printf("Bitcoin price: $%.2f\n", price);
            if (price < PRICE_THRESHOLD) {
                printf("Alert! Bitcoin price is below $%d.\n", PRICE_THRESHOLD);
                //play_alert_song(); // Play song if price downs below last price
            } 
            else if ( price > PRICE_THRESHOLD)
            {
                printf("Alert! New ATH $%.2f\n", price);
                play_alert_song(); // Play song if price downs below last price
            }
        } else {
            printf("Cannot obtain BTC price\n");
        }
        
        sleep(60);
    }
    return 0;
}
