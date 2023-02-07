/*
	Submitted by:					Date Submitted: 24 May 2021
		Herrera, Arquiel
		Liao, Abrience
		Mayuga, Danessa

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap(int P[][4], int nRow2, int nCol2, int nRow3, int nCol3) 
{
	int temp;
	if(P[nRow3][nCol3] > 1)// if greater than 1 swap
	{
		temp = P[nRow2][nCol2];
		P[nRow2][nCol2] = P[nRow3][nCol3];
	  	P[nRow3][nCol3] = temp;
	  	
    	return 1;
  	} 
  	else 
    	return -1; 

  	return 0;    
}

void InitializeBoard(int P[][4]) 
{
	int i, j;

	printf("\n\t       C1 |  C2 |  C3 |  C4\n");
	printf("\t     ______________________\n");
	for (i = 0; i < 4; i++) 
  	{
		printf("\t R%d | ", i + 1); // dis works
		
		for (j = 0; j < 4; j++) 
    	{
			if (j < 3)
				printf(" %d  | ", P[i][j]);
			else
				printf(" %d", P[i][j]);
		}

		if (i < 3) 
    	{
			printf("\n");
			printf("\t   +-----------------------+\n");
		}
	}
	printf("\n\t    _______________________\n");
}

void Insert(int P[][4], int nIndex1, int nIndex2, int nTurn) 
{
	if (nTurn == 1)
		P[nIndex1][nIndex2] = 1;
	else if (nTurn == 0) 
		P[nIndex1][nIndex2] = 2;
}

int CheckFreeCHA(int P[][4], int nIndex1, int nIndex2)
{
	if ((nIndex1 <= 2 && nIndex2 == 0) || (nIndex1 == 0 && nIndex2 <= 2))
		return 0;
	else if (P[nIndex1][nIndex2] == '\0')
		return 1;

	return 0; // return 0 if not
}

// checks if the cell is free for ORD
int CheckFree(int P[][4], int nIndex1, int nIndex2) 
{
	if (P[nIndex1][nIndex2] == '\0')
		return 1; // returns 1 if it is empty

	return 0; // return 0 if not
}

int over(int P[][4]) 
{
	int i, j;
  	int nNum = 0; 
  	int nFlag = 0; 
	int nPing = 0;

	if((P[0][3] == 1 && P[1][3] == 1 && P[2][3] == 1) || 
	   (P[1][1] == 1 && P[2][2] == 1 && P[3][3] == 1) || 
	   (P[1][2] == 1 && P[2][1] == 1 && P[3][0] == 1) || 
	   (P[3][1] == 1 && P[3][2] == 1 && P[3][3] == 1))
  	{
		return 1;
	}
	 
	for(i = 3; i >= 0; i--)
   	{
     	for(j = nNum; j  <= 3; j++)
		{
       		if(P[i][j] != '\0')
          	nPing += 1; 
		}	
      	nFlag += 1; 
      	
      	if(nFlag == 1)
        	nNum += 1; 
        	
      	if(nFlag == 3)
        	nNum += 2; 
   	}
   	
	if (nPing == 11)
		return 2;

	return 0;
}

int main() 
{
	int P[4][4] = {}; // Game Board
	int nTurn = 1;	// True or False
	int nRow, nCol;
	int nRow2, nCol2;
  	int nRow3, nCol3;
  	int Ctr = 1;
  	int nSwap; 
	int nOver; // stores the value of the over function
	
	printf("\t------CCDSTRU MACHINE PROJECT-------\n");
  	printf("\n\tCHA's move represents as 1\n\t& ORD's move represents as 2\n\n");
  	InitializeBoard(P);

	do 
  	{
		while (nTurn != 0) 
    	{
			printf("\n\nCHA: Select a Row and a Column: \n");
     		printf("Choices: 1, 2, 3, 4\n");
     		printf("Enter two numbers: ");
      
      		do
      		{
        		scanf("%d %d", &nRow, &nCol);
        
        		if(nRow <= 4 && nCol <= 4 && nRow >= 1 && nCol >= 1)
        		{
          			printf("\n\tCHA Position:%d,%d \n", nRow, nCol);
		    		printf("\tCHA Row & Column: \n\n");

		    		nRow -= 1;
			    	nCol -= 1;
			    	if (CheckFreeCHA(P, nRow, nCol) == 1) 
          			{
			  	  		Insert(P, nRow, nCol, nTurn);   // insert to P to fill
				    	nTurn = 0;
			    	} 
          			else
				    	printf("INVALID ACTION!\n\n");
        		}
        		else
          			printf("INVALID COORDINATE\n\n");
       		} while(nRow > 4 && nCol > 4 && nRow < 1 && nCol < 1);
		}

    	nOver = over(P); 
		InitializeBoard(P);

		if (nTurn == 0 && nOver == 0) 
    	{
			while (nTurn != 1) 
      		{
				printf("\n\nORD:Select a Row and a Column \n");
        		printf("Choices: 1, 2, 3, 4\n");
        		printf("Enter two numbers: ");
        		do
        		{
          			scanf("%d %d", &nRow2, &nCol2);
          
          			if(nRow2 <= 4 && nCol2 <= 4 && nRow2 >= 1 && nCol2 >= 1)
          			{
            			printf("\n\tORD Position:%d,%d \n", nRow2, nCol2);
				    	printf("\tORD Row & Column: \n\n");

				    	nRow2 -= 1;
				    	nCol2 -= 1;
      
		  		  		if(CheckFree(P, nRow2, nCol2) == 1) 
            			{
              				if(Ctr <= 4) //Insert
              				{
                				Insert(P, nRow2, nCol2, nTurn); 
              				}
              				else if(Ctr > 4) //Swap
              				{
                				while(nSwap != 1)
                				{
                  					printf("ORD: Select a marked coordinate to remove: \n");
                  					do
                  					{
                    					scanf("%d %d", &nRow3, &nCol3);

                    					if(nRow3 <= 4 && nCol3 <= 4 && nRow3 >= 1 && nCol3 >= 1)
                    					{
                      						nRow3 -= 1;
                      						nCol3 -= 1;

                      						nSwap = swap(P, nRow2, nCol2, nRow3, nCol3);

                      						if (nSwap == -1)
                        						printf("NOT YOUR PIECE\n"); 
                    					}
                    					else
                      						printf("INVALID COORDINATE\n\n");
                  					} while(nRow3 > 4 && nCol3 > 4 && nRow3 < 1 && nCol3 < 1);
                				}
              				}
              				nSwap = 0;
              				Ctr++;
              				nTurn = 1; 
				    	} 
            			else
  					  		printf("INVALID ACTION!\n\n");
          			}
          			else
            			printf("INVALID COORDINATE\n\n");
          		} while(nRow2 > 4 && nCol2 > 4 && nRow2 < 1 && nCol2 < 1);
			}
		}
    	nOver = over(P);
		InitializeBoard(P); 
	} while (nOver == 0); // keeps going as long as it is not over
   
  	if(nOver == 1)
    	printf("\nCHA WON!");
  	else if (nOver == 2)
    	printf("\nORD WON!"); 

	return 0;
}
