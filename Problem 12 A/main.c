#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main()
{
    int i = 0, j = 1,k,stars ,diff, diff_1,diff_2,day_swamp, month_swamp,importance_swamp;
    char kind_swamp,temp_event[150], temp_2[150];
    int year,year_2,year_3;
    int month[50];
    int importance[50];
    int day[50];
    char kind[50];
    char events[150][150];
    // input the year
    printf("Enter the year: ");
    scanf("%d", &year);
    // input the date and its imporatnce
    while (j) {
        scanf(" %c", &kind[i]);
        if (kind[i] != '#') {
            scanf("%d %d %d %[^\n]%*c", &day[i],&month[i],&importance[i],&events[i]);
            i++;
        }
       else if (kind[i]=='D'){
            scanf("%d %d",&day[i],&month[i]);
        }
        else {
            j = 0;
        }
    }

    //get the date of today to the beginning of the array

    for (k=0;k<=i;k++){
            if (kind[k]=='D'){
                     day_swamp=day[0];
                     month_swamp= month[0];
                     importance_swamp=importance[0];
                     strcpy(temp_event, events[0]);
                     kind_swamp=kind[0];
                     day[0]=day[k];
                     month[0]=month[k];
                     importance[0]=importance[k];
                     day[k]=day_swamp;
                     month[k]=month_swamp;
                     importance[k]=importance_swamp;
                     strcpy(events[k], temp_event);
                     break;


            }



    }
    // sorting dates using Unix timestamp format

   for (k = 2; k < i; k++) {
    for (j = k; j > 1; j--) {
            if ((month[j]-month[0])<0){
                year_2=year+1;
            }
            else{
                year_2=year;
            }
              if ((month[j-1]-month[0])<0){
                year_3=year+1;
            }
            else{
                year_3=year;
            }
            if (month[j]-month[0]==0 && day[j]<day[0]){
                year_2=year+1;

            }
              if (month[j-1]-month[0]==0 && day[j-1]<day[0]){
                year_3=year+1;

            }
        time_t timestamp = mktime(&((struct tm) {
        .tm_year = year - 1900,
        .tm_mon = month[0] - 1,
        .tm_mday = day[0],
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
        .tm_isdst = -1
    }));
        time_t timestamp_2 = mktime(&((struct tm) {
        .tm_year = year_2 - 1900,
        .tm_mon = month[j] - 1,
        .tm_mday = day[j],
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
        .tm_isdst = -1
    }));
       time_t timestamp_3 = mktime(&((struct tm) {
        .tm_year = year_3 - 1900,
        .tm_mon = month[j-1] - 1,
        .tm_mday = day[j-1],
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
        .tm_isdst = -1
    }));
     double a= difftime(timestamp_2 , timestamp)/(60*60*24);
     double b= difftime(timestamp_3 , timestamp)/(60*60*24);
     diff_1= (int) a;
     diff_2= (int) b;



       ///////////////////////////////////////////////////
       if (diff_1<diff_2){
            kind_swamp = kind[j - 1];
            day_swamp = day[j - 1];
            month_swamp = month[j - 1];
            importance_swamp = importance[j - 1];
            strcpy(temp_event, events[j - 1]);

            kind[j - 1] = kind[j];
            day[j - 1] = day[j];
            month[j - 1] = month[j];
            importance[j - 1] = importance[j];
            strcpy(events[j - 1], events[j]);

            kind[j] =kind_swamp;
            day[j] = day_swamp;
            month[j] =month_swamp;
            importance[j] = importance_swamp;
            strcpy(events[j], temp_event);





        }
        else if (diff_1 == diff_2){
            if (importance[j]>importance[j-1]){
            kind_swamp = kind[j - 1];
            day_swamp = day[j - 1];
            month_swamp = month[j - 1];
            importance_swamp = importance[j - 1];
            strcpy(temp_event, events[j - 1]);

            kind[j - 1] = kind[j];
            day[j - 1] = day[j];
            month[j - 1] = month[j];
            importance[j - 1] = importance[j];
            strcpy(events[j - 1], events[j]);

            kind[j] =kind_swamp;
            day[j] = day_swamp;
            month[j] =month_swamp;
            importance[j] = importance_swamp;
            strcpy(events[j], temp_event);

            }
        }
    }
   }



    printf("Today is: %d %d \n",day[0],month[0]);
    for (k=1;k<=(i-1);k++){
            if ((month[k]-month[0])<0){
                year_2=year+1;
            }
            else{
                year_2=year;
            }
             if (month[k]-month[0]==0 && day[k]<day[0]){
                year_2=year+1;

            }
         time_t timestamp = mktime(&((struct tm) {
        .tm_year = year - 1900,
        .tm_mon = month[0] - 1,
        .tm_mday = day[0],
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
        .tm_isdst = -1
    }));
        time_t timestamp_2 = mktime(&((struct tm) {
        .tm_year = year_2 - 1900,
        .tm_mon = month[k] - 1,
        .tm_mday = day[k],
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
        .tm_isdst = -1
    }));
     double a= difftime(timestamp_2 , timestamp)/(60*60*24);
     diff=(int) a ;

        if (diff==0){
            printf("%d %d *TODAY* %s",day[k],month[k],events[k]);
            printf("\n");
        }
        else {
                stars=importance[k]-diff;
                if (stars>0){
                    printf ("%d %d ",day[k],month[k]);
                    for (int n=0 ;n<=stars;n++){
                        printf("*");
                    }
                    printf(" %s",events[k]);
                    printf("\n");
                }

        }

    }
    return 0;


}
