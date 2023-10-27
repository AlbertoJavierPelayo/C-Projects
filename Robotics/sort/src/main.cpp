#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>

void printList(float *numbers_list, int list_size);
void sortList(float *numbers_list, int list_size);
void quicksort(float *list, int first_p, int last_p);
void sortList_homework(float *numbers_list, int list_size);

int main()
{
    const int klist_size = 1000;//change value to test - initial = 1000
    float numbers[klist_size]; //array for random numbers
    float numbers_homework[klist_size]; //array for random numbers
    //const float bound_limit = 1.0;
    int number_of_experiments = 2000;//fix value = 2000
    float time_experiments = 0.0;
    float time_experiments_homework = 0.0;
    clock_t begin; // gets current state of clock
    clock_t end;
    srand(time(NULL));
    for(int idy=0; idy < number_of_experiments;idy++)
    {
        for( int idx =0; idx < klist_size;idx++)
        {
            numbers[idx] = (float)rand()/(float)RAND_MAX;
            numbers_homework[idx] = numbers[idx];
        }
        begin = clock();
        sortList(numbers, klist_size);
        end = clock();
        time_experiments += (float)(end - begin) / CLOCKS_PER_SEC; //acumulador
        //printList(numbers_homework,klist_size);
        begin = clock();
        sortList_homework(numbers_homework, klist_size);
        end = clock();
        time_experiments_homework=+(float)(end - begin) / CLOCKS_PER_SEC; //acumulador
        //printList(numbers_homework,klist_size);
        }
    std::cout <<"Time: " <<time_experiments / number_of_experiments << "\n";
    std::cout <<"Homework: "<< time_experiments_homework / number_of_experiments << "\n";
    return 0;
}

void quicksort(float *list, int first_p, int last_p)
{
    //información y código insppirado de https://www.genbeta.com/desarrollo/implementando-el-algoritmo-quicksort
    int idx=first_p;
    int idy=last_p;
    int mitad=(int)((idx+idy)/2);
    float pivote=list[mitad];
    float aux;

    while(idx<idy)
    {
        while(list[idx]<pivote)
        {
            idx++;
        }
        while(list[idy]>pivote)
        {
            idy--;
        }
        if(idx<=idy)
        {
            aux=list[idy];
            list[idy]=list[idx];
            list[idx]=aux;
            idx++;
            idy--;

        }
    }
    if(first_p<idy)
    {
        quicksort(list,first_p,idy);
    }
    if(last_p>idx)
    {
        quicksort(list,idx,last_p);
    }

}

void sortList_homework(float *numbers_list, int list_size)
{
    //Metodo Quicksort
    quicksort(numbers_list,0,list_size-1);
    // fill!!!
}
void sortList(float *numbers_list, int list_size)
{
    for(int idx=0; idx < list_size;idx++)
    {
        for(int idy = idx + 1; idy < list_size; idy++)
        {
            if(numbers_list[idx] > numbers_list[idy])
            {
                float temporal = numbers_list[idx];
                numbers_list[idx] = numbers_list[idy];
                numbers_list[idy] = temporal;
            }
        }
    }
}
void printList(float *numbers_list, int list_size)
{
    for(int idx=0;idx < list_size; idx++)
    {
        std::cout << numbers_list[idx] << " ";
    }
    std::cout << std::endl;
}