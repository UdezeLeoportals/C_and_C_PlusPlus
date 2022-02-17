// C++ Program to print Magic square
// of Doubly even order
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Function for calculating Magic square
void doublyEven( int n )
{
    int arr[n][n], i, j;

    // filling matrix with its count value
    // starting from 1;
    for ( i = 0; i < n; i++)
        for ( j = 0; j < n; j++)
            arr[i][j] = (n*i) + j + 1;

    // change value of Array elements
    // at fix location as per rule
    // (n*n+1)-arr[i][j]
    // Top Left corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 0; i < n/4; i++)
        for ( j = 0; j < n/4; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];

    // Top Right corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 0; i < n/4; i++)
        for ( j = 3 * (n/4); j < n; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];

     // Bottom Left corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 3 * n/4; i < n; i++)
        for ( j = 0; j < n/4; j++)
            arr[i][j] = (n*n+1) - arr[i][j];

    // Bottom Right corner of Matrix
    // (order (n/4)*(n/4))
    for ( i = 3 * n/4; i < n; i++)
        for ( j = 3 * n/4; j < n; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];

    // Centre of Matrix (order (n/2)*(n/2))
    for ( i = n/4; i < 3 * n/4; i++)
        for ( j = n/4; j < 3 * n/4; j++)
            arr[i][j] = (n*n + 1) - arr[i][j];

    // Printing the magic-square
    printf("The Magic Square for n=%d:\nSum of "
           "each row or column %d:\n\n",
           n, n * (n * n + 1) / 2);
    for (i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
            printf(" %d ",arr[i][j]);
         printf("\n");
    }
}

// A function to generate odd sized magic squares
void generateSquare(int n)
{
    int magicSquare[n][n], num;

    // set all slots as 0
    memset(magicSquare, 0, sizeof(magicSquare));

    // Initialize position for 1
    int i = n / 2;
    int j = n - 1;

    // One by one put all values in magic square
    for (num = 1; num <= n * n;) {
        if (i == -1 && j == n) // 3rd condition
        {
            j = n - 2;
            i = 0;
        }
        else {
            // 1st condition helper if next number
            // goes to out of square's right side
            if (j == n)
                j = 0;

            // 1st condition helper if next number
            // is goes to out of square's upper side
            if (i < 0)
                i = n - 1;
        }
        if (magicSquare[i][j]) // 2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; // set number

        j++;
        i--; // 1st condition
    }

    // Print magic square
    printf("The Magic Square for n=%d:\nSum of "
           "each row or column %d:\n\n",
           n, n * (n * n + 1) / 2);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%3d ", magicSquare[i][j]);
        printf("\n");
    }
}


    void singlyEvenMagicSquare(int n) {
       // if (n < 6 || (n - 2) % 4 != 0)
            //return NULL;

        int size = n * n;
        int halfN = n / 2;
        int subGridSize = size / 4, i;

        //int** subGrid = oddMagicSquare(halfN);
        //////////////////////////
        int subGrid[halfN][halfN], num;

    // set all slots as 0
    memset(subGrid, 0, sizeof(subGrid));

    // Initialize position for 1
     i = halfN / 2;
    int j = halfN - 1;

    // One by one put all values in magic square
    for (num = 1; num <= halfN * halfN;) {
        if (i == -1 && j == halfN) // 3rd condition
        {
            j = halfN - 2;
            i = 0;
        }
        else {
            // 1st condition helper if next number
            // goes to out of square's right side
            if (j == halfN)
                j = 0;

            // 1st condition helper if next number
            // is goes to out of square's upper side
            if (i < 0)
                i = halfN - 1;
        }
        if (subGrid[i][j]) // 2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            subGrid[i][j] = num++; // set number

        j++;
        i--; // 1st condition
    }

        ///////////////////////////
        int gridFactors[] = {0, 2, 3, 1};
        //int** result = (int**)malloc(n*sizeof(int*));
        int result[n][n];
		//for(i=0;i<n;i++)
			//result[i] = (int*)malloc(n*sizeof(int));
        int r, c;
        for (r = 0; r < n; r++) {
            for (c = 0; c < n; c++) {
                int grid = (r / halfN) * 2 + (c / halfN);
                result[r][c] = subGrid[r % halfN][c % halfN];
                result[r][c] += gridFactors[grid] * subGridSize;
            }
        }

        int nColsLeft = halfN / 2;
        int nColsRight = nColsLeft - 1;

        for (r = 0; r < halfN; r++)
            for (c = 0; c < n; c++) {
                if (c < nColsLeft || c >= n - nColsRight
                        || (c == nColsLeft && r == nColsLeft)) {

                    if (c == 0 && r == nColsLeft)
                        continue;

                    int tmp = result[r][c];
                    result[r][c] = result[r + halfN][c];
                    result[r + halfN][c] = tmp;
                }
            }

         // Printing the magic-square
         printf("The Magic Square for n=%d:\nSum of "
           "each row or column %d:\n\n",
           n, n * (n * n + 1) / 2);
    for (i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
            printf(" %d ",result[i][j]);
         printf("\n");
    }
    }


	int main(int argC,char* argV[])
	{
		int n;

			n = atoi(argV[1]);
			if(n%2==1)
            generateSquare(n);
            else if(n%4==0)
			doublyEven(n);
			else
                singlyEvenMagicSquare(n);

     //Function call

		return 0;

	}


//https://rosettacode.org/wiki/Magic_squares_of_singly_even_order
//https://www.geeksforgeeks.org/magic-square-even-order/?ref=rp
