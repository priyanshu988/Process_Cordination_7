#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int Hydrogen, Oxygen, sites, threshold, operableSite, energy;
int current_reaction, count1;
int current_site = 1;
pthread_mutex_t lock1, lock2, lockH, lockO;

void* update_Hydrogen(void* p)
{
    pthread_mutex_lock(&lockH);
    Hydrogen--;
    count1++;
    if(count1 == 1)
        pthread_mutex_unlock(&lockH);
    else
        pthread_mutex_unlock(&lockO);
        
    return NULL;
}

void* update_Oxygen(void* p)
{
    pthread_mutex_lock(&lockO);
    count1=0;
    Oxygen--;
    pthread_mutex_unlock(&lockH);
    return NULL;
}

void* reaction(void* p)
{
    pthread_mutex_lock(&lock2);    
    while(current_reaction >= operableSite);
    pthread_mutex_unlock(&lock2);

    current_reaction++;
    sleep(3);
    pthread_mutex_lock(&lock1);
    pthread_t createAtom[3];
    pthread_mutex_init(&lockH, NULL);
    pthread_mutex_init(&lockO, NULL);

    for(int i=0; i<3; i++)
    {
        if(i==0)
            pthread_create(&createAtom[i], NULL, update_Oxygen, NULL);
        else 
            pthread_create(&createAtom[i], NULL, update_Hydrogen, NULL);
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_join(createAtom[i], NULL);
    }
    energy++;
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("Site Number: %d\t Energy: %d\t H2O Molecules: %d\t Remaining Hydrogen: %d\t Remaining Oxygen: %d\n", current_site, energy, energy, Hydrogen, Oxygen);

    if(sites % 2 == 0)
    {
        if ((sites - current_site) == 1)
            current_site = 2; 
    }
    if (current_site == sites)
        current_site = 1;
    
    else if((current_site + 2) % sites == 0)
        current_site = sites;
    
    else
        current_site = (current_site+2)%sites;
    
    pthread_mutex_unlock(&lock1);
    current_reaction--;
    return NULL;
}

int main(int argc, char** argv)
{
    if(argc < 5)
    {
        printf("Invalid Number of arguments! \n");
        exit(1);
    }
    
    Hydrogen = atoi(argv[1]);
    Oxygen = atoi(argv[2]);
    sites = atoi(argv[3]);
    threshold = atoi(argv[4]);

    int tempSite = sites/2;
    
    if(sites%2 == 1)
    {
        tempSite++;
        if(tempSite > threshold)
            operableSite = threshold;
        else
            operableSite = tempSite;
    }
    else
    {
        if(tempSite > threshold)
            operableSite = threshold;
        else
            operableSite = tempSite;
    }
   
    int l1 = pthread_mutex_init(&lock1, NULL);
    int l2 = pthread_mutex_init(&lock2, NULL);

    if(l1 != 0)
        return 1;
    
    if(l2 != 0)
        return 1;
    
    int used_oxygen = Oxygen;
    int temp_hydrogen = Hydrogen;

    if((temp_hydrogen % 2) == 1)
    {
        temp_hydrogen--;
    }

    if(temp_hydrogen < (2*used_oxygen))
        used_oxygen = temp_hydrogen/2;
        
    pthread_t creation[used_oxygen];

    for (int i = 0; i < used_oxygen; i++)
    {
        pthread_create(&creation[i], NULL, reaction, NULL);
    }
    
    for (int i = 0; i < used_oxygen; i++)
    {
        pthread_join(creation[i], NULL);
    }

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    printf("----------------------------------------------------------------------------------------------------------\n");

    return 0;
}
