#include <stdio.h>
#include "config.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int error(int* x, int* y){
    char* suradnica;

    if (strchr(optarg,',') != NULL){
        int len1 = strlen(optarg);
        int len2 = strlen(strchr(optarg,','));

        for (int i=0; i < len2-1; i++) {
            if (!isdigit((strchr(optarg, ',') + 1)[i])) {
                printf("E1");
                return 0;
            }
        }

        if (len1 - len2 == 0){
            printf("E1");
            return 0;
        }
        else if (len2-1 == 0){
            printf("E1");
            return 0;
        }
        suradnica = strtok(optarg, ",");
        suradnica = strtok(NULL, ",");
        *y = atoi(suradnica);

        for (int i=0; i < len1-len2; i++) {
            if (!isdigit(strtok(optarg, ",")[i])) {
                printf("E1");
                return 0;
            }
        }
        *x = atoi(strtok(optarg, ","));

        return 1;
    }
    else{
        printf("E1");
        return 0;
    }
}

void vypisData(){
    for (int i=0; i<DB_NUM; i++) {
        printf("%s\n%d,%d\n%d\n", db[i].name, db[i].pos.x, db[i].pos.y, db[i].n);
        for (int j=0; j<db[i].n; j++)
            printf("%d. %s,%d\n", j+1, db[i].menu[j].name, db[i].menu[j].price);
        printf("\n");
    }
}

void prepinacP(int* x, int* y){
    char nazovJedla[MAX_NAME];
    int vyhladaneRest[41];
    int dm,cv2;
    int cv1 = -1;
    int zhoda = 0;
    int poradie = 0;
    int control = 0;

    scanf("%[^\n]s",nazovJedla);
    for (int i=0; i<DB_NUM; i++) {
        for (int j=0; j<db[i].n; j++){
            if (strcmp(nazovJedla, db[i].menu[j].name) == 0){
                zhoda++;
                dm = abs(*x - db[i].pos.x) + abs(*y - db[i].pos.y);
                cv2 = 10*dm + 100*db[i].menu[j].price;
                vyhladaneRest[poradie] = cv2;
                vyhladaneRest[poradie+1] = i;
                vyhladaneRest[poradie+2] = j;
                vyhladaneRest[poradie+3] = dm;
                poradie += 4;
                if (cv1 == -1)
                    cv1 = cv2;
                else if (cv2 < cv1)
                    cv1 = cv2;
            }
        }
    }
    vyhladaneRest[poradie] = -1;

    for (int i=0; vyhladaneRest[i]!=-1; i+=4) {
        if (cv1 == vyhladaneRest[i]) {
            printf("%s: %d %d *\n", db[vyhladaneRest[i+1]].name, vyhladaneRest[i+3], db[vyhladaneRest[i+1]].menu[vyhladaneRest[i+2]].price);
            zhoda--;
        }
    }

    while (zhoda != 0) {
        for (int i = 0; vyhladaneRest[i] != -1; i += 4) {
            if (cv1 < vyhladaneRest[i] && control == 0) {
                cv2 = vyhladaneRest[i];
                poradie = i;
                control = 1;
            }
            else if (cv2 > vyhladaneRest[i] && cv1 < vyhladaneRest[i]) { //?
                cv2 = vyhladaneRest[i];
                poradie = i;
            }
        }
        printf("%s: %d %d\n", db[vyhladaneRest[poradie + 1]].name, vyhladaneRest[poradie + 3],db[vyhladaneRest[poradie + 1]].menu[vyhladaneRest[poradie + 2]].price);
        cv1 = cv2;
        control = 0;
        zhoda--;
    }
}

void prepinacPN(int* x, int* y){
    char nazovJedla[MAX_NAME];
    char nazovRest1[30];
    char nazovRest2[30];
    char nazovRest3[30];
    int vyhladaneRest[21];
    int dm,cv2;
    int cv1 = -1;
    int poradie = 0;
    int control = 0;

    scanf("%[^\n]s", nazovJedla);
    for (int i=0; i<DB_NUM; i++) {
        for (int j=0; j<db[i].n; j++){
            if (strcmp(nazovJedla, db[i].menu[j].name) == 0){
                dm = abs(*x - db[i].pos.x) + abs(*y - db[i].pos.y);
                cv2 = 10*dm + 100*db[i].menu[j].price;
                vyhladaneRest[poradie] = i;
                vyhladaneRest[poradie+1] = j;
                poradie += 2;
                if (cv1 == -1)
                    cv1 = cv2;
                else if (cv2 < cv1)
                    cv1 = cv2;
            }
        }
    }
    vyhladaneRest[poradie] = -1;
    if (poradie > 4)
        strcpy(nazovRest1,db[vyhladaneRest[4]].name);
    else
        strcpy(nazovRest1,db[vyhladaneRest[poradie-2]].name);

    for (int i=0; vyhladaneRest[i] != -1; i += 2) {
        for (int j = 0; vyhladaneRest[j] != -1; j += 2) {
            if (strcmp(nazovRest1, db[vyhladaneRest[j]].name) > 0 && control == 0) {
                strcpy(nazovRest1, db[vyhladaneRest[j]].name);
                control = 1;
                poradie = j;
                break;
            }

            else if (vyhladaneRest[i+2] == -1){
                strcpy(nazovRest2, db[vyhladaneRest[j]].name);
                for (int k=0; vyhladaneRest[k] != -1; k += 2) {
                    if (strcmp(nazovRest2, db[vyhladaneRest[k]].name) < 0) {
                        strcpy(nazovRest2, db[vyhladaneRest[k]].name);
                        poradie = k;
                    }
                }
                strcpy(nazovRest1,nazovRest2);
            }
            else if (strcmp(nazovRest1, db[vyhladaneRest[j]].name) < 0 && control == 1) {
                strcpy(nazovRest2, db[vyhladaneRest[j]].name);
                for (int k=0; vyhladaneRest[k] != -1; k += 2) {
                    if (strcmp(nazovRest2, db[vyhladaneRest[k]].name) > 0 && strcmp(nazovRest3, db[vyhladaneRest[k]].name) < 0) {
                        strcpy(nazovRest1, db[vyhladaneRest[k]].name);
                        poradie = k;
                    }
                }
            }
        }
        dm = abs(*x - db[vyhladaneRest[poradie]].pos.x) + abs(*y - db[vyhladaneRest[poradie]].pos.y);
        cv2 = 10*dm + 100*db[vyhladaneRest[poradie]].menu[vyhladaneRest[poradie+1]].price;
        if (cv2 == cv1)
            printf("%s: %d %d *\n", nazovRest1, dm, db[vyhladaneRest[poradie]].menu[vyhladaneRest[poradie+1]].price);
        else
            printf("%s: %d %d\n", nazovRest1, dm, db[vyhladaneRest[poradie]].menu[vyhladaneRest[poradie+1]].price);
        strcpy(nazovRest3, nazovRest1);
    }
}

int main(int argc, char *argv[]) {
    int opt, e1;
    int x, y;
    char *optstring = ":p:n";
    int prepinac = 0;

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'p':
                e1 = error(&x, &y);
                if (e1 == 0)
                    return 0;
                prepinac = 1;
                break;
            case 'n':
                prepinac = 2;
                break;
        }
    }
    if (prepinac == 0){
        vypisData();
    }
    else if (prepinac == 1){
        prepinacP(&x, &y);
    }
    else {
        prepinacPN(&x, &y);
    }

	return 0;
}
