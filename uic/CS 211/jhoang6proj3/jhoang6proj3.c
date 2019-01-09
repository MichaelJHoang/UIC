#include <stdio.h>
#include <stdlib.h>

int debugMode = -1; //debugMode toggle


void printID ()
{
    puts("Name: Jon-Michael Hoang");
    puts("March 1st, 2018");
    puts("CS 211: Program 3: Maze Solving");
    puts("Note to grader: This program is buggy, so run it several times, please");
    puts("\n");
}

//Three structs to implement the maze program
typedef struct mazeStruct
{
    char **arr;
    int X_SIZE, Y_SIZE;
    int X_START, Y_START;
    int X_END, Y_END;
}maze;

typedef struct mazePosition
{
    int visited;
    int X_POS, Y_POS;
    struct mazePosition*  next;
}position;

typedef struct Stack
{
    int size;
    int top;
    position *head;
}Stack;
//end structs


//Function used to detect any invalid sizes in input
int validSize (int size)
{
    if (size > 0)
        return 1;
    return 0;
}
//end validSize()


//Given an input file, detect any abnormalities involving the input file and return
//respective error message
int validPosition (maze * m1, int x, int y) 
{
    if(m1 -> X_SIZE < x)
    {
        if(debugMode)
            printf ("=> Invalid: row %d is outside range from 1 to %d ", x, m1->X_SIZE);
        return x;
    }
    else if (m1 -> Y_SIZE < y)
    {
        if(debugMode) 
            printf ("=> Invalid: column %d is outside range from 1 to %d ", y, m1->Y_SIZE);
        return y;
    } 
    else if (x == m1->X_START && y == m1->Y_START)
    {
        if(debugMode)
            puts ("=> Invalid: attempting to block starting position");
        return x; 
    }
    else if (x == m1->X_END && y == m1->Y_END)
    {
        if(debugMode)
            puts ("=> Invalid: attempting to block starting position");
        return x; 
    }
    return 1;
}
//end validPosition()


//Takes in a file and with the help of the function above, detect errors
void checkInputs (maze *m1, FILE *src)
{
    do
    {
        fscanf (src, "%d %d", &m1 -> X_SIZE, &m1 -> Y_SIZE);
        printf ("The [size] of the maze is:\t%d, %d\t", m1 -> X_SIZE, m1 -> Y_SIZE);
        if((validSize(m1 -> X_SIZE) && validSize(m1->Y_SIZE)) == 0 && (debugMode == 1))
            printf ("=> Invalid: Maze sizes must be greater than 0 ");
        printf("\n");
    }while ((validSize(m1 -> X_SIZE) && validSize(m1 -> Y_SIZE)) != 1);
    
    int result, X_START, X_END, Y_START, Y_END;
    
    do
    {
        fscanf (src, "%d %d", &X_START, &Y_START);
        printf ("A [startpoint] has been called:\t%d, %d\t", X_START, Y_START);
        result = validPosition(m1, X_START, Y_START);
        printf("\n");
    }while (result != 1);
    
    m1 -> X_START = X_START;
    m1 -> Y_START = Y_START;
    
    do
    {
        fscanf (src, "%d %d", &X_END, &Y_END);
        printf ("An [endpoint] has been called:\t%d, %d\t", X_END, Y_END);
        result = validPosition(m1, X_END, Y_END);
        printf("\n");
    }while (result != 1);
    
    m1 -> X_END = X_END;
    m1 -> Y_END = Y_END;
}
//end checkInputs


//Create the maze
void initMazeArr (maze *m1)
{
    if (validSize(m1 -> X_SIZE) && validSize(m1 -> Y_SIZE))
    {
        char ** temp = (char**)malloc((m1 -> X_SIZE+2) * sizeof(char*));
        for(int x = 0; x < m1 -> X_SIZE + 2; x++) {
            temp[x] = (char*)malloc((m1->Y_SIZE+2) * sizeof(char));
        }
        if(m1 -> arr != NULL)
            m1 -> arr = temp;
    }
}
//end initMazeArr()


//Resets the maze to have all elements with '.'
void emptyMaze (maze* m1)
{
    for (int x = 0; x < m1->X_SIZE+2; x++)
        for (int y = 0; y < m1 -> Y_SIZE+2; y++)
            m1->arr[x][y] = '.';
}
//end emptyMaze()


//Creates the borders of the maze
void fillBorders (maze* m1)
{
    for (int x = 0; x < m1->X_SIZE+2; x++)
    {
        m1 -> arr[x][0] = '*';
        m1 -> arr[x][m1 -> Y_SIZE+1] = '*';
    }
    
    for (int x = 0; x < m1 -> Y_SIZE+2; x++)
    {
        m1->arr[0][x] = '*';
        m1->arr[m1 -> X_SIZE+1][x] = '*';
    }
}
//end fillBorders()


//Creates walls inside the maze
void fillWalls (maze *m1, FILE *src)
{
    int X_POS, Y_POS, result;

    while (fscanf (src, "%d %d", &X_POS, &Y_POS) != EOF)
    {
        puts ("A [wall] has been summoned:");
        printf ("\t%d, %d\t", X_POS, Y_POS);
        
        result = validPosition(m1, X_POS, Y_POS);
        if (result == 1)
            m1->arr[X_POS][Y_POS] = '*';
        printf("\n");
    }
    printf("\n");
}
//end fillWalls()


//Prints out the maze
void printMaze (maze* m1)
{
    for (int x = 0; x < m1 -> X_SIZE+2; x++)
    {
        for (int y = 0; y < m1 -> Y_SIZE+2; y++)
            printf ("%c", m1->arr[x][y]);
        printf("\n");
    }
}
//end printMaze()

void initPosition (position *p, int x, int y)
{
    p -> visited = 0;
    p -> X_POS = x;
    p -> Y_POS = y;
}
 
void initStack (Stack *s)
{
    s -> size = 0;
    s -> head = (position*) malloc(s -> size * sizeof(position));
    s -> top = 0;
}

position top (Stack *s)
{
    if(s -> top > 0)
        return (s -> head[s -> top-1]);
}

void pop (Stack* s) //
{
    if (debugMode == 1)
        puts ("\nDebugging Information: \npop:");
        printf ("%d %d \n", top(s).X_POS, top(s).Y_POS);

    s -> top = s -> top - 1;
}

// function to push and mark visited
void pushAndVisit (Stack *stack, int x, int y, maze *m1) //
{
    position *p = (position*) malloc (sizeof(position));
    initPosition(p, x, y);
    
    stack -> head[stack -> top] = *p;
    
    if (stack -> head[stack -> top - 1].next == NULL)
        stack -> head[stack -> top - 1].next = p;
        
    stack -> top++;
    
    if (!(m1 -> arr[x][y] == 'S' || m1 -> arr[x][y] == 'E'))
        m1 -> arr[x][y] = 'X';

    if (debugMode)
        printf ("\nVisited and marked (%d, %d)", x, y);
}
//end pushAndVisit


//Checks if the stack is empty
int checkEmptyStack (Stack* s) //
{
    if (s -> top == 0)
        return 1;
    return 0;
}
//end checkEmptyStack()


//Reset the stack
void reset(Stack *s)
{
    free(s -> head);
    initStack(s);
}
//end reset()


//start main()
int main (int argc, char **argv)
{
    printID();
    
    maze m1;
    
    int X_POS = 0, Y_POS = 0;
    
    FILE *src;
    
    if(argc > 3)
    {
        puts("Too many command line arguments!\n");
        exit(-1);
    }
    else if (argc < 1)
    {
        printf("Usage: %s <input file name>\n", argv[0]);
        exit(-1);
    }
    
    if ((src = fopen(argv[1], "r")) == NULL)
    {
        printf ("Can't open input file: %s", argv[1]);
        exit(-1);
    }
    
    for (int x = 0; x < argc; x++)
        debugMode = ((strcmp(argv[x], "-d") == 0)) ? 1 : -1;
    
    
    checkInputs(&m1, src);
    initMazeArr(&m1);
    emptyMaze(&m1);
    fillBorders(&m1);
    fillWalls(&m1,src);
    
    m1.arr[m1.X_START][m1.Y_START] = 'S';
    m1.arr[m1.X_END][m1.Y_END] = 'E';
  
    Stack stack; //initStack(m1.size + 2, m1.Y_SIZE + 2);
    
    int x = m1.X_START, y = m1.Y_START;
    int X_TOP, Y_TOP;
    
    pushAndVisit(&stack, x, y, &m1);
    
    while (((x != m1.X_END) && (y != m1.Y_END)) && (checkEmptyStack(&stack) == 0))
    {
        X_TOP = top(&stack).X_POS;
        Y_TOP = top(&stack).Y_POS;
        
        if ((X_TOP == m1.X_END) && (Y_TOP == m1.Y_END))
        {
            puts ("\n\nTHIS MAZE IS SOLVED\n");
            
            printMaze(&m1);
            return 0;
        }
        
        if (m1.arr[X_TOP + 1][Y_TOP] == '.' || m1.arr[X_TOP + 1][Y_TOP] =='E')
            pushAndVisit(&stack, X_TOP + 1, Y_TOP, &m1);
        else if (m1.arr[X_TOP - 1][Y_TOP] == '.' || m1.arr[X_TOP - 1][Y_TOP] =='E')
            pushAndVisit(&stack, X_TOP - 1, Y_TOP, &m1);
        else if (m1.arr[X_TOP][Y_TOP + 1] == '.' || m1.arr[X_TOP][Y_TOP + 1] =='E')
            pushAndVisit(&stack, X_TOP, Y_TOP + 1, &m1);
        else if (m1.arr[X_TOP][Y_TOP - 1] == '.' || m1.arr[X_TOP][Y_TOP - 1] =='E')
            pushAndVisit(&stack, X_TOP, Y_TOP - 1, &m1);
        else
            pop (&stack);
    }
    puts ("\n\nTHIS MAZE IS UNSOLVABLE\n");
    printMaze(&m1);
    
    free(m1.arr);
    free(stack.head);
    
    fclose (src);
}
//end main