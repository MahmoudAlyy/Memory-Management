#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int a;
    scanf("%d", &a);
    int array[a];
    int i ;
    for (i = 0 ; i<a ; i++)
        array[i]=-1;

    char method[20];
    scanf("%s", method);

    printf("Replacement Policy = %s\n", method);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int p; /// page
    scanf("%d", &p);

    /////////////////////////////////////////////////////////////////////
    /// FIFO
    if (strcmp(method,"FIFO") == 0 )
    {

        int ai = 0; /// array index
        int fc = 0; /// fault counter
        int f = 0; /// fault boolean
        int intf = 0; /// initial fault counter

        while(p != -1)
        {

            f = 1;
            for(i = 0 ; i < a ; i++)
            {
                if (array[i] == p)
                {
                    f = 0;
                }
            }
            printf("%02d ",p);
            if (f)
            {
                array[ai%a]= p;
                ai ++;

                ///initial fault
                if (intf < a)
                {
                    printf("    ");
                }
                else
                {
                    printf("F   ");
                    fc++;
                }
                intf ++;
            }
            else
            {
                printf("    ");
            }


            for(i = 0 ; i < a ; i++)
            {
                if (array[i] != -1)
                {
                    printf("%02d ",array[i]);
                }
            }

            printf("\n");
            scanf("%d", &p);
        }

        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fc);

    }



/// LRU
    if (strcmp(method,"LRU") == 0 )
    {
        int time[a];
        for (i = 0 ; i<a ; i++)
            time[i]=-1;
        int tc = 0;/// time counter
        int ai = 0; /// array index
        int fc = 0; /// fault counter
        int f = 0; /// fault boolean
        int intf = 0; /// initial fault counter
        int min = -1;
        int imin = -1; /// min index
        int nfi = 0 ; /// no fault index

        while(p != -1)
        {

            f = 1;
            for(i = 0 ; i < a ; i++)
            {
                if (array[i] == p)
                {
                    f = 0;
                    nfi = i;
                }
            }
            printf("%02d ",p);
            if (f)
            {
                ///check first if first fault
                if (intf < a)
                {
                    array[ai] = p;
                    time[ai] = tc;
                    ai++;
                    printf("    ");
                    intf ++;
                }
                else
                {
                    printf("F   ");
                    fc++;

                    /// pick index with smallest time number
                    min = tc +1 ;

                    for (i = 0 ; i < a ; i++)
                    {
                        //printf(" time[%d] = %d ",i , time[i]);
                        if (time[i] < min)
                        {
                            min = time[i];
                            imin = i;
                        }
                    }
                    ///printf(" imin = %d ",imin);
                    array[imin]= p;
                    time[imin] = tc;

                    ///initial fault
                }
            }
            else
            {
                printf("    ");
                time[nfi] = tc;
            }


            for(i = 0 ; i < a ; i++)
            {
                if (array[i] != -1)
                {
                    printf("%02d ",array[i]);
                }
            }

            printf("\n");
            scanf("%d", &p);
            tc++;
        }

        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fc);

    }


/// CLOCK
    if (strcmp(method,"CLOCK") == 0 )
    {
        int use[a];
        for (i = 0 ; i<a ; i++)
            use[i]=-1;
        int clock = 0;
        int ai = 0; /// array index
        int fc = 0; /// fault counter
        int f = 0; /// fault boolean
        int intf = 0; /// initial fault counter
        int nfi = 0 ; /// no fault index

        while(p != -1)
        {

            f = 1;
            for(i = 0 ; i < a ; i++)
            {
                if (array[i] == p)
                {
                    f = 0;
                    nfi = i;
                }
            }
            printf("%02d ",p);
            if (f)
            {
                ///check first if first fault
                if (intf < a)
                {
                    array[ai] = p;
                    use[ai] = 1;
                    clock++;
                    clock = clock % a;
                    ai++;
                    printf("    ");
                    intf ++;
                }
                else
                {
                    printf("F   ");
                    fc++;

                    while(use[clock] == 1)
                    {
                        use[clock] = 0;
                        clock++;
                        clock = clock % a;
                    }
                    array[clock] = p;
                    use[clock] = 1;
                    clock++;
                    clock = clock % a;
                }
            }
            else
            {
                printf("    ");
                use[nfi] = 1;
            }

            /// printing
            for(i = 0 ; i < a ; i++)
            {
                if (array[i] != -1)
                {
                    printf("%02d ",array[i]);
                }
            }

            printf("\n");
            scanf("%d", &p);
        }

        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fc);

    }


/// OPTIMAL
    if (strcmp(method,"OPTIMAL") == 0 )
    {
        int index = 0;
        int oarray[1000];
        int f;
        int intf=0;
        int ai=0;
        int fc = 0;
        int ref[a];
        int max;
        int imax;
        int found;

        while( p != -1 )
        {
            oarray[index] = p;
            index++;
            scanf("%d", &p);
        }

        for (int c = 0 ; c < index; c++)
        {
            /// reset ref
            for (i = 0 ; i <a ; i++)
            {
            ref[i]=-1;
            }

            f = 1;
            for(i = 0 ; i < a ; i++)
            {
                if (array[i] == oarray[c])
                {
                    f = 0;
                }
            }

            printf("%02d ",oarray[c]);

            if (f)
            {
                ///check first if first fault
                if (intf < a)
                {
                    array[ai] = oarray[c];
                    ai++;
                    printf("    ");
                    intf ++;
                }
                else
                {
                    printf("F   ");
                    fc++;

                    for(i=c+1 ; i<index ; i++)
                        {
                        for (int j = 0 ; j< a; j++)
                            {
                            if(oarray[i] ==array[j])
                                {
                                if (ref[j] == -1)
                                ref[j] = i;
                                }
                            }
                        }

                 found = 0;
                 for (i = 0 ; i<a ;i++)
                 {
                 if (ref[i] == -1 )
                    {
                    array[i] = oarray[c];
                    //printf("\n2replaced\n");
                    found = 1;
                    break;
                    }

                 }

                 if (found==0)
                 {
                 max = -1 ;

                    for (i = 0 ; i < a ; i++)
                    {
                        if (ref[i] > max)
                        {
                            max = ref[i];
                            imax = i;
                        }
                    }
                    ///printf(" imin = %d ",imin);
                    array[imax]= oarray[c];
                    //printf(" \n REPLACED \n");

                    }
                }

            }
            else
            {
                printf("    ");
            }

            /// printing
            for(i = 0 ; i < a ; i++)
            {
                if (array[i] != -1)
                {
                    printf("%02d ",array[i]);
                }
            }

            printf("\n");

            } ///end of loop on indexes
            printf("-------------------------------------\n");
            printf("Number of page faults = %d\n",fc);

            } /// end of optima;
            return 0;
        }
