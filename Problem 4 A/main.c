#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCE_LENGTH 150
#define MAX_NUM_WORDS 15

int main()
{
    char ignore[MAX_SENTENCE_LENGTH];
    char title[MAX_SENTENCE_LENGTH];
    char each_title[MAX_NUM_WORDS][MAX_SENTENCE_LENGTH];

    int i, j, var = 0, k = 0, m, w, l, num = 0;
    printf("Enter words to ignore: ");
    scanf("%[^\n]%*c", ignore);
    strlwr(ignore);
    printf("Enter titles, separated by '-': ");
    scanf("%[^\n]%*c", title);
    strlwr(title);

    char words_ignore[MAX_NUM_WORDS][MAX_SENTENCE_LENGTH];
    int number_words = 0;

    char *token = strtok(ignore, " ");

    while (token != NULL) {
        strcpy(words_ignore[number_words], token);
        number_words++;
        token = strtok(NULL, " ");
    }

    int number_words_2 = 0;
    char title_names[MAX_NUM_WORDS][MAX_SENTENCE_LENGTH];
    char *temp = strtok(title, "-");
    while (temp != NULL) {
        strcpy(title_names[number_words_2], temp);
        number_words_2++;
        temp = strtok(NULL, "-");
    }

    for (l = 0; l < number_words_2; l++) {
        char *temp_1 = strtok(title_names[l], " ");
        num = 0;

        while (temp_1 != NULL) {
            strcpy(each_title[num], temp_1);
            num++;
            temp_1 = strtok(NULL, " ");
        }

        for (i = 0; i < num; i++) {
            var = 0;
            for (j = 0; j < number_words; j++) {
                if (strcasecmp(each_title[i], words_ignore[j]) == 0) {
                    var = 1;
                    break;
                }
            }
            if (var == 0) {
                for (m = 0; m < num; m++) {
                    if (m == i) {
                        printf("%c", toupper(each_title[m][0]));
                        for (w = 1; w < strlen(each_title[m]); w++) {
                            printf("%c", tolower(each_title[m][w]));
                        }
                    } else {
                        printf("%s", each_title[m]);
                    }
                    if (m < num - 1) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}
