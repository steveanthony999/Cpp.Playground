#include <stdio.h>
/*
    General Dynamics #NEM puzzle auto-solver
        github.com/glennlopez
*/

//solver routines
void popWithSum(int [], int [], int *);
int findFrqSum(int [], int);
int updateNumTracker();

//sorting algorythms
void insertion_sort(int [], int);
void swap(int *, int *);


//parametric var
#define CALC_VAL 730                      // (MATRIX_SIZE*MATRIX_SIZE)^MATRIX_SIZE + 1
const int MATRIX_SIZE = 3;                // size of matrix (ie: 3 = 3x3)
const int MAX_Y = CALC_VAL/4;             // 1/4 of possible sum combination
const int MAX_X = MATRIX_SIZE;
int sums[CALC_VAL] = {};
int givens[] = {
    //35, 18, 19, 48, 3, 20, 32, 31, 4, '\0'    //testcase 1 :: solveable
    //11, 2, 99, 48, 17, 20, 32, 31, 4, '\0'     //testcase 2 :: unsolvable
    12, 25, 27, 15, 30, 20, 10, 18, 23, '\0'    //testcase 3 :: solveable
};

//store value var
int solCol[MATRIX_SIZE] = {};
int arrCount = 0;                               // number of arr stored
int frqSum = 0;                                 // most freq sum
int mtrxSolArr[MAX_Y][MAX_X] = {};              // possible solution values
int usedNums[MATRIX_SIZE * MATRIX_SIZE] = {};
int solution[MATRIX_SIZE][MATRIX_SIZE] = {};    // solution




/*****************
 * MAIN ROUTINE
******************/
int main(){
    popWithSum(givens, sums, &arrCount);    // populate sum array
    insertion_sort(sums, arrCount);         // sort array
    frqSum = findFrqSum(sums, arrCount);    // find most frq sum

    // store frqSum solution in multidimentional array
    int frqSumCount = 0;
    for(int k = 0; givens[k] != '\0'; k++){
        for(int j = 0; givens[j] != '\0'; j++){
            for(int i = 0; givens[i] != '\0'; i++){
                if( (i != j) && (i != k) && (j != k)){
                    if(givens[k] + givens[j] + givens[i] == frqSum){
                        mtrxSolArr[frqSumCount][0] = givens[k];
                        mtrxSolArr[frqSumCount][1] = givens[j];
                        mtrxSolArr[frqSumCount][2] = givens[i];
                        frqSumCount++;
                    }
                }
            }
        }
    }
    
    // brute force solution
    for(int a = 0; a < frqSumCount ; a++){
        for(int row = 0; row < MATRIX_SIZE; row++){
            solution[0][row] = mtrxSolArr[a][row];
        }
        for(int b = 0; b < frqSumCount ; b++){
            for(int row = 0; row < MATRIX_SIZE; row++){
                solution[1][row] = mtrxSolArr[b][row];
            }
            for(int c = 0; c < frqSumCount ; c++){
                for(int row = 0; row < MATRIX_SIZE; row++){
                    solution[2][row] = mtrxSolArr[c][row];
                }

                // calculate column value
                int offset_y = (MATRIX_SIZE - 1);
                for(int x = 0; x < MATRIX_SIZE; x++){
                    solCol[x] = 0;
                    for(int y = 0; y < MATRIX_SIZE; y++){
                        solCol[x] += solution[y][x];
                    }
                }
                if( (updateNumTracker() == MATRIX_SIZE * MATRIX_SIZE) ){
                    break;
                }
            }
        }

        // check column sum 
        // TODO: make this check parametric (read below)
        // PARAMETRIC: just add up all the solCol1 and div by col size. if it == frqsum then break;
        if( ((solCol[0] == frqSum) && (solCol[1] == frqSum) && (solCol[2] == frqSum)) ){
            // (columnAvg == frqSum == column1)
            break;
        }
    }



                    //DEBUG PRINT OUT
                    printf("Given Numbers:");
                    for(int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++){
                        printf(" %i", givens[i]);
                    }
                    printf("\n");
                    printf("\n");
                    printf("\n");
                    printf("Solution: \n");
                    for(int j = 0; j < 3; j++){
                        for(int i = 0; i < 3; i++){
                            printf("%i ", solution[j][i]);
                        }
                        printf("\n");
                    }
                    //END DEBUG

    return 0;
}



/*****************
 * SUB ROUTINES
******************/

//populate array with sum
void popWithSum(int givenArr[], int storeArr[], int *counter){
    //populate array with sum
    for(int k = 0; givenArr[k] != '\0'; k++){
        for(int j = 0; givenArr[j] != '\0'; j++){
            for(int i = 0; givenArr[i] != '\0'; i++){
                
                if( (i != j) && (i != k) && (j != k)){
                    storeArr[*counter] = givenArr[k] + givenArr[j] + givenArr[i];
                    (*counter)++; 
                    /*
                    //output to stdout
                    printf("%i + %i + %i = %i \n", 
                    givenArr[k], givenArr[j], givenArr[i], 
                    givenArr[k] + givenArr[j] + givenArr[i]);
                    */
                }
            }
        }
    }
}

//find frequent 
//TODO: use below suggestion
/*  THIS IS DEPRICATED;
        To find frequent sum, 
        just add all the elements and divide by array size.
*/
int findFrqSum(int arr[], int param){
    int a = arr[0]; int b = arr[1];
    int sum_counter = 1; int highest_count = 0; 
    int most_frequent = 0;
    
    for(int i = 0; i <= param; i++){
        if(arr[i] != arr[i + 1]){
            int a = arr[i + 0];
            int b = arr[i + 1];

            if(sum_counter > highest_count){
                highest_count = sum_counter;
                most_frequent = arr[i];
            }
            sum_counter = 1;
        }
        else{
            sum_counter++;
        }
    }

    return most_frequent;
}

//insertion sort subroutine
void insertion_sort(int paramArr[], int elementCount){
    int sdx = 0;
    int tdx = sdx + 1;

    for(int i = 0; i < elementCount; i++){
        while( (paramArr[tdx] < paramArr[tdx - 1]) && (tdx > 0) && (tdx < elementCount) ){
            swap(&paramArr[tdx], &paramArr[tdx - 1]);
            tdx--;
        }
        sdx++;
        tdx = sdx + 1;
    }
}

//swap subroutine
void swap(int *param1, int *param2){    int buffer = 0;
    buffer = *param1;
    *param1 = *param2;
    *param2 = buffer;
}

int updateNumTracker(){
    //track used numbers
    //TODO: take in limited number of parameter
    int notEqual = 0;
    int usedNumIndex = 0;
    for(int sol_x = 0; sol_x < MATRIX_SIZE; sol_x++){
        for(int j = 0; j < MATRIX_SIZE; j++){

            notEqual = 0;   //resets counter every loop
            for(int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++){
                //printf("%i ",usedNums[i]);

                // count frequency on non-equal numbers
                if(solution[sol_x][j] != usedNums[i]){
                    notEqual++;
                }

                // assume number is unique
                if(notEqual == MATRIX_SIZE*MATRIX_SIZE){
                    usedNums[usedNumIndex] = solution[sol_x][j];
                    usedNumIndex++;
                }

            }
            //printf("returns: %i\n", notEqual);
            //printf("\n");

        }

    }
    //printf("\n");
    for(int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++){
        usedNums[i] = '\0';
    }
    return usedNumIndex;
}