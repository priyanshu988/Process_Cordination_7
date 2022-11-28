#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int geeks_arrived, nongeeks_arrived, singers_arrived;

void crossed_bridge()
{
    sleep(2);
    printf("They have crossed the bridge.\n");
}

void *GeekArrives(void *args)
{
    if (geeks_arrived == 3)
    {
        geeks_arrived -= 3;
        printf("4 Geeks have arrived.\n");
        crossed_bridge();
    }
    else if (geeks_arrived >= 1 && nongeeks_arrived >= 2)
    {
        geeks_arrived--;
        nongeeks_arrived -= 2;
        printf("2 Geeks and 2 Non Geeks have arrived.\n");
        crossed_bridge();
    }
    else
    {
        geeks_arrived++;
        return NULL;
    }
    return NULL;
}

void *NonGeekArrives(void *args)
{
    if (nongeeks_arrived == 3)
    {
        nongeeks_arrived -= 3;
        printf("4 Non Geeks have arrived.\n");
        crossed_bridge();
    }
    else if (geeks_arrived >= 2 && nongeeks_arrived >= 1)
    {
        geeks_arrived -= 2;
        nongeeks_arrived--;
        printf("2 Geeks and 2 Non Geeks have arrived.\n");
        crossed_bridge();
    }
    else
    {
        nongeeks_arrived++;
        return NULL;
    }
    return NULL;
}

void *SingerArrives(void *args)
{
    if (geeks_arrived >= 3)
    {
        geeks_arrived -= 3;
        printf("1 Singer and 3 Geeks have arrived.\n");
        crossed_bridge();
    }
    else if (nongeeks_arrived >= 3)
    {
        nongeeks_arrived -= 3;
        printf("1 Singer and 3 Non Geeks have arrived.\n");
        crossed_bridge();
    }
    else if (geeks_arrived >= 1 && nongeeks_arrived >= 2)
    {
        geeks_arrived--;
        nongeeks_arrived -= 2;
        printf("1 Singer, 1 Geeks and 2 Non Geeks have arrived.\n");
        crossed_bridge();
    }
    else if (geeks_arrived >= 2 && nongeeks_arrived >= 1)
    {
        geeks_arrived -= 2;
        nongeeks_arrived--;
        printf("1 Singer, 2 Geeks and 1 Non Geek have arrived.\n");
        crossed_bridge();
    }
    else
    {
        singers_arrived--;
        return NULL;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int no_of_geeks, no_of_nongeeks, no_of_singers;
    no_of_geeks = atoi(argv[1]);
    no_of_nongeeks = atoi(argv[2]);
    no_of_singers = atoi(argv[3]);

    pthread_t geeks, nongeeks, singers;

    while (1)
    {
        if ((no_of_singers == 0) && (no_of_geeks != 0 || no_of_nongeeks != 0))
        {
            if (no_of_geeks >= 4)
            {
                sleep(1);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_join(geeks, NULL);
                sleep(1);
                no_of_geeks -= 4;
            }
            else if (no_of_nongeeks >= 4)
            {
                sleep(1);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_join(nongeeks, NULL);
                sleep(1);
                no_of_nongeeks -= 4;
            }
            else if (((no_of_geeks == 3) && (no_of_nongeeks == 2 || no_of_nongeeks == 3)) || ((no_of_geeks == 2) && (no_of_nongeeks == 2 || no_of_nongeeks == 3)))
            {
                sleep(1);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_join(geeks, NULL);
                pthread_join(nongeeks, NULL);
                sleep(1);
                no_of_geeks -= 2;
                no_of_nongeeks -= 2;
            }
            else
            {
                sleep(4);
                printf("\n-----------------------\n");
                printf("Count of remaining people who could not cross the bridge:\n");
                printf("Geeks = %d \nNon Geeks = %d\nSingers = %d\n", no_of_geeks, no_of_nongeeks, no_of_singers);
                pthread_exit(NULL);
                exit(0);
                break;
            }
        }
        else if ((no_of_singers > 0) && (no_of_geeks != 0 || no_of_nongeeks != 0))
        {
            if (no_of_geeks >= 3)
            {
                sleep(1);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&singers, NULL, &SingerArrives, NULL);
                pthread_join(geeks, NULL);
                pthread_join(singers, NULL);
                sleep(1);
                no_of_geeks -= 3;
                no_of_singers--;
            }
            else if (no_of_nongeeks >= 3)
            {
                sleep(1);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&singers, NULL, &SingerArrives, NULL);
                pthread_join(nongeeks, NULL);
                pthread_join(singers, NULL);
                sleep(1);
                no_of_nongeeks -= 3;
                no_of_singers--;
            }
            else if (no_of_geeks == 1 && no_of_nongeeks == 2)
            {
                sleep(1);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&singers, NULL, &SingerArrives, NULL);
                pthread_join(geeks, NULL);
                pthread_join(nongeeks, NULL);
                pthread_join(singers, NULL);
                sleep(1);
                no_of_geeks--;
                no_of_nongeeks -= 2;
                no_of_singers--;
            }
            else if (no_of_geeks == 2 && no_of_nongeeks == 1)
            {
                sleep(1);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&geeks, NULL, &GeekArrives, NULL);
                pthread_create(&nongeeks, NULL, &NonGeekArrives, NULL);
                pthread_create(&singers, NULL, &SingerArrives, NULL);
                pthread_join(geeks, NULL);
                pthread_join(nongeeks, NULL);
                pthread_join(singers, NULL);
                sleep(1);
                no_of_geeks -= 2;
                no_of_nongeeks--;
                no_of_singers--;
            }
            else
            {
                sleep(4);
                printf("\n-----------------------\n");
                printf("Count of remaining people who could not cross the bridge:\n");
                printf("Geeks = %d \nNon Geeks = %d\nSingers = %d\n", no_of_geeks, no_of_nongeeks, no_of_singers);
                pthread_exit(NULL);
                exit(0);
                break;
            }
        }
        else
        {
            sleep(4);
            printf("\n-----------------------\n");
            printf("Count of remaining people who could not cross the bridge:\n");
            printf("Geeks = %d \nNon Geeks = %d\nSingers = %d\n", no_of_geeks, no_of_nongeeks, no_of_singers);
            pthread_exit(NULL);
            exit(0);
            break;
        }
    }
}