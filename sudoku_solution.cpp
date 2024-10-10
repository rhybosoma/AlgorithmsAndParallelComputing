/*
 * Check sudoku matrix
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;

int basic_search (const unsigned v[], unsigned n_elements);

int check_rows (const unsigned sudoku[][SIZE]);
int check_cols (const unsigned sudoku[][SIZE]);
int check_regions (const unsigned sudoku[][SIZE]);

// Return:
//         1 if sudoku matrix complies to all Sudoku rules
//        -1 if a row violates the game rules
//        -2 if a column violates the game rules
//        -3 if a region violates the game rules
int check_sudoku(const unsigned sudoku[][SIZE]);

// Create a Sudoku matrix by Lewis' Algorithm
// (https://en.wikipedia.org/wiki/Sudoku_solving_algorithms)
void generate_sudoku(unsigned sudoku[][SIZE]);

int main()
{
    // initialize a sudoku matrix
    unsigned sudoku[SIZE][SIZE] = {
            {1,2,3,4,5,6,7,8,9},
            {2,3,4,5,6,7,8,9,1},
            {3,4,5,6,7,8,9,1,2},
            {4,5,6,7,8,9,1,2,3},
            {5,6,7,8,9,1,2,3,4},
            {6,7,8,9,1,2,3,4,5},
            {7,8,9,1,2,3,4,5,6},
            {8,9,1,2,3,4,5,6,7},
            {9,1,2,3,4,5,6,7,8}
    };

    //print sudoku 1
    for (auto &row:sudoku){
        for (auto &col: row){
            cout<<" "<< col<<" ";
        }
        cout<<endl;
    }
/*
 * //row test and col test for sudoku 1
    int test = check_rows(sudoku);
    cout<<"test rows result: "<< test<<" "<<endl;

    int test2 = check_cols(sudoku);
    cout<<"test cols result "<< test2<<" "<<endl;
*/
    // check
    int res = check_sudoku(sudoku);
    cout << "check_sudoku returns: " <<  res << endl;

    // initialize another sudoku matrix
    unsigned sudoku2[SIZE][SIZE];
    generate_sudoku(sudoku2);

    //print sudoku 2
    for (auto &row:sudoku2){
        for (auto &col: row){
            cout<<" "<< col<<" ";
        }
        cout<<endl;
    }
    /*
    // test regions 3
    int test3 = check_regions(sudoku2);
    cout<<"test regions result "<< test3<<" "<<endl;
    */

    //res = check_sudoku(sudoku2);
    //cout << "check_sudoku returns: " <<  res << endl;

    return 0;
}

int search_key (const unsigned v[], unsigned n_elements, unsigned key)
{
    unsigned key_found = 0;

    for (size_t i=0; i<n_elements; ++i)
        if (v[i] == key)
            key_found = 1;

    return key_found;
}




int basic_search (const unsigned v[], unsigned n_elements){

    bool is_in = false;
    for (unsigned int i = 1; i<=n_elements; i++ ){

        if (is_in == search_key(v,n_elements,i)){
            cout<<"# not found: "<<i<<endl;
            return 0;
        }
    }

return 1;
}

int check_rows (const unsigned sudoku[][SIZE]){

    unsigned v[SIZE]={};

    for(size_t i=0;i<SIZE; i++){
        //copy row of sudoku to v
        memcpy(v, sudoku[i], sizeof (v));
        /* print
        cout<<"v: "<<endl;
        for (auto &row:v){
            cout<<" "<< row<<" ";
            cout<<endl;
        }*/

        //check if all 1 to 9 are present in each sudoku row i
       int result_row = basic_search(v,SIZE);
        if (result_row==0){
            cout<<"sudoku rows violated"<<endl;
            cout<<"In row: "<< i<<endl;
            return -1;
        }
    }
    return 1;
}

int check_cols (const unsigned sudoku[][SIZE]){
    //initilize v, the i-th column of sudoku
    unsigned v[SIZE]={};

    //copy the col of sudoku to v
    for (unsigned j = 0; j < SIZE; j++){
        for (unsigned i = 0; i<SIZE; i++){
            v[i]=sudoku[i][j];
        }
        /* //print ith sudoku col
        cout<<"v: "<<endl;
        for (auto &col:v){
            cout<<" "<< col<<" ";
            cout<<endl;
        }
         */
        int check_col = basic_search(v,SIZE);
        if (check_col==0){
            cout<<"sudoku cols violated: "<<endl;
            cout<<"In col: "<< j<<endl;
            return -2;
        }
    }

    return 1;
}

int check_regions (const unsigned sudoku[][SIZE]){

    unsigned v[SIZE]={};
    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            unsigned aux = 0;
            for (size_t k=0; k<SIZE; ++k)
            {   if(k>0&&k%3==0)aux++;
                //cout<<3*(i-1)+aux;
                v[k]= sudoku[3*(i-1)+aux][3*(j-1)+k%3];

            }
            /*cout<<"v: "<<endl;
            for (auto &col:v){
                cout<<" "<< col<<" ";
                cout<<endl;
            }*/
            int result_row = basic_search(v,SIZE);
            if (result_row==0){
                cout<<"sudoku regions violated: "<<endl;
                cout<<"In region i: "<< i-1<< " j: "<< j-1 << endl;
                return -3;
            }
        }
    }


    // i = 0 j = 0 k = 0
    // sudoku 0 0
    // sudoku 0 1
    // sudoku 0 2
    // k = 3
    // sudoku 1 0
    // sudoku 1 1
    // sudoku 1 2
    // k = 6
    // sudoku 2 0
    // sudoku 2 1
    // sudoku 2 2

    //i=0 j=1
    // sudoku 0 3
    // sudoku 0 4
    // sudoku 0 5
    // k = 3
    // sudoku 1 3
    // sudoku 1 4
    // sudoku 1 5
    // k = 6
    // sudoku 2 3
    // sudoku 2 4
    // sudoku 2 5

    //i=1 j=0
    // sudoku 3 0
    // sudoku 3 1
    // sudoku 3 2
    // k = 3
    // sudoku 4 0
    // sudoku 4 1
    // sudoku 4 2
    // k = 6
    // sudoku 5 0
    // sudoku 5 1
    // sudoku 5 2

    return 1;
}



int check_sudoku(const unsigned sudoku[][SIZE])
{
    cout << "The sudoku is... " << endl;

    int rows = check_rows (sudoku);
    if (rows!=1){
        //cout<<"rows failed"<<endl;
        return -1;
    }
    int cols = check_cols (sudoku);
    if (cols!=1){
        //cout<<"cols failed"<<endl;
        return -2;
    }

    int regions = check_regions (sudoku);
    if (regions!=1){
        //cout<<"regions failed"<<endl;
        return -3;
    }

    return 1;
}

void generate_sudoku(unsigned sudoku[][SIZE])
{
    int x = 0;
    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            for (size_t k=1; k<=SIZE; ++k)
            {
                sudoku[3*(i-1)+j-1][k-1] = (x % SIZE) + 1;
                x++;
            }
            x += 3;
        }
        x++;
    }
}

