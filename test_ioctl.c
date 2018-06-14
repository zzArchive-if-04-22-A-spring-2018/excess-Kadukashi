#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void NextPage(FILE *file, struct winsize *ws, int page);


int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    struct winsize ws;

    if (ioctl(0, TIOCGWINSZ, &ws) != 0) {
        fprintf(stderr, "TIOCGWINSZ:%s\n", strerror(errno));
        exit(-1);
    }
    NextPage(file, &ws, 0);
    printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
           ws.ws_row, ws.ws_col, ws.ws_xpixel, ws.ws_ypixel);
    fclose(file);
    printf("%s\n",argv[1]);
    return 0;
}

void NextPage(FILE *file, struct winsize *ws, int page) {
    rewind(file);
    if (file == 0)return;
    char c;
    int count = 0;
    while (count <= page) {
      system("clear");
        char *string  = malloc(sizeof(char) * (ws->ws_col + 1));
        for (int i = 0; i < ws->ws_row && !feof(file); i++) {
            fgets(string , ws->ws_col, file);
            printf("%s", string );
        }
        free(string );

        count++;
    }
    c = getchar();
    if (c == '\n' && !feof(file)) {

        NextPage(file, ws, page + 1);

    }
    else if (c == 'b' && page > 0) {

        while (c != '\n') c = getchar();
        NextPage(file, ws, page - 1);

    }
    else if (c != '\n') {

        while (c != '\n') c = getchar();
        NextPage(file, ws, page);
    }

}
