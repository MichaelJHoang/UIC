/**************************************************
 * 
 * Author: Jon-Michael Hoang
 * Class: CS 211
 * Lab: Fridays at 10:00 AM
 * Project: Learning how to use malloc and dynamic arrays (Programming Project 1)
 * 
 * ***********************************************/
 
 
//C libraries used for the program
#include <stdio.h>
#include <stdlib.h>


/**************************************************
 * 
 * Prints out identifying information
 * 
 * ***********************************************/
void printID ()
{
    printf ("Author: Jon-Michael Hoang\n");
    printf ("Class: CS 211\n");
    printf ("Lab: Fridays at 10:00 AM\n");
    printf ("Project: Learning how to use malloc and dynamic arrays (Programming Project 1)\n\n");
}
//end printID()


/**************************************************
 * 
 * Creates a duplicate of the array
 * 
 * ***********************************************/
void arrayCopy (int source[], int destination[], int size)
{
    for (int x = 0; x < size; x++)
        destination[x] = source[x];
    
    printf ("\nCopied input:\n");
    
    for (int x = 0; x < size; x++)
    {
        printf ("%d ", destination[x]);
    }
    
    return;
}
//end arrayCopy()


/**************************************************
 * 
 * Scans through the given array from the beginning
 * until it reaches the target. Returns the index
 * of the target value and returns the numComparisons
 * via dereferencing
 * 
 * ***********************************************/
int linearSearch (int array[], int size, int target, int* numComparisons)
{
    for (int index = 0; index < size; index++)
    {
        (*numComparisons)++;
        
        if (array[index] == target)
            return index;
    }
    
    return -1;
}
//end linearSearch()


/**************************************************
 * 
 * Searches for the target by restricting the domain
 * and "squeezing" out the answer and returns its
 * index and the numComparisons via dereferencing
 * 
 * ***********************************************/
int binarySearch (int array[], int n, int m, int target, int* numComparisons)
{
    if (m >= 1)
    {
        (*numComparisons)++;
        
        int index = n + (m - n) / 2;
    
        if (array[index] == target)
        return index;
        
        if (array[index] > target)
            return binarySearch(array, n, m-1, target, numComparisons);
        return binarySearch(array, n, m-1, target, numComparisons);
    }
    
    return -1;
}
//end binarySearch()

/**************************************************
 * 
 * repeatedly steps through the list to be sorted by
 * comparing adjacent pairs and reorganizes them
 * 
 * ***********************************************/
void sinkSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
//end bubbleSort()

/**************************************************
 * 
 * main() function in which the program runs through.
 * Here, input is taken and it sorts them through
 * the works, etc.
 * 
 * ***********************************************/
int main() 
{
    printID();
    
    //Variables to track positions and sizes of the arrays
    int index = 0;
    int size = 2;
    
    //Initialize dynamic arrays to please the professor
    int *userInput;
    int *copyArray;
    int input = 0;
    
    userInput = (int*) malloc(size * sizeof(int));
    copyArray = (int*) malloc(size * sizeof(int));
    
    //Variable to catch the user's input on what integer they want to look for
    //in the arrays
    int target;
    
    //Variables to store the returned values of linearSearh() and binarySearch()
    //respectively
    int linearResult = 0;
    int binaryResult = 0;
    
    //Initialize variables to track the amount of comparisons linearSearch()
    //and binarySearch() take and to later dereferencing it, giving it the "two
    //return types" function
    int *linearNumComparisons;
    int *binaryNumComparisons;
    
    int linearInitComp = 0;
    int binaryInitComp = 0;
    
    linearNumComparisons = &linearInitComp;
    binaryNumComparisons = &binaryInitComp;
    
    //Asks for userInput
    printf("Please enter in integers separated by spaces and end in -999:\n");
    scanf("%d", &input);
    
    
    /*****
     * 
     * If there exists input size larger than the given array, expand the array
     * by doubling its size.
     * 
     ****/
    while (input != -999)
    {
        
        if (index > size)
        {
            int *temp;
            
            temp = (int*) malloc(size * 2 * sizeof(int));
            copyArray = (int*) malloc(size * 2 * sizeof(int));
            
            for (int x = 0; x < size; x++)
                temp[x] = userInput[x];
                
            free(userInput);
            userInput = temp;
            size *= 2;
        }
        
        userInput [index] = input;
        index++;
        scanf("%d", &input);
    }
    
    /*****
     * 
     * SANITY CHECK
     * 
     ****/
    arrayCopy(userInput, copyArray, index);
    putchar('\n');
    
    
    /*****
     * 
     * RUNNING IT THROUGH WITH LINEAR
     * 
     ****/
    printf("\nThe unsorted input:\n");
    for (int x = 0; x < index; x++)
        printf("%d ", userInput[x]);
        
    printf("\n\nWhat integer are you looking for in the arrays: ");
    scanf("%d", &target);
    
    linearResult = linearSearch(userInput, index, target, linearNumComparisons);
    
    if (linearResult == -1)
        printf("The value you entered, [ %d ], was not found\n", target);
    else
        printf("The value you entered, [ %d ], was found at index [ %d ] with [ %d ] comparisons through linear search\n", target, linearResult, *linearNumComparisons);
    /*****
     * 
     * END LINEAR
     * 
     ****/
    
    
    /*****
     * 
     * RUNNING IT THROUGH WITH BINARY
     * 
     ****/
    sinkSort(userInput, index);
    
    printf("\nThe elements within the array after the bubble sort are:\n");
    
    for (int x = 0; x < index; x++)
        printf("%d ", userInput[x]);
        
    putchar('\n');
    
    binaryResult = binarySearch(userInput, 0, index, target, binaryNumComparisons);
    
    if (binaryResult == -1)
        printf("\nThe value you entered, [ %d ], was not found\n", target);
    else
        printf("The value you entered, [ %d ], was found at index [ %d ] with [ %d ] comparisons through binary search", target, binaryResult, *binaryNumComparisons);
    /*****
     * 
     * END BINARY
     * 
     ****/
    
    
    return 0;
}
//end main()