/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//Daniyal Faraz
//22I-1096
//Project
//---Piece Starts to Fall When Game Starts---//
void fallingPiece(int BLOCKS[][4], float& timer, float& delay, int& colorNum, int point_3[][2], int next[][2], int& nextblock, int& nextblockcolor, int next2[][2], int& nextblock2, int& nextblockcolor2, int level, int rows, int cols){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly(rows, cols)){
            
            for (int i = 0; i < 4; i++)
            {
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            }
            //colorNum = 1 + rand() % 7;
            //int n=rand()%7;
            colorNum = nextblockcolor;
            int n=nextblock;
            int offset = rand() % (cols - 1);
            //--- Un-Comment this Part When You Make BLOCKS array---//
            for (int i=0;i<4;i++){
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
                point_1[i][0] += offset; // to start new block at a random position
                point_3[i][0] = point_1[i][0]; // keeping shadow equal to current block
                point_3[i][1] = point_1[i][1];
                
            }
            nextblockcolor = nextblockcolor2;
            nextblock = nextblock2; // the next block is assigned value of second next block
            if (level == 1)
                nextblock2 = rand() % 4;  
            else
                nextblock2 = rand() % 7;  // new blocks are unlocked after second level
            nextblockcolor2 = 1 + rand() % 7;  // This assigns new color and block to second next block
        }
        timer=0;
    }
}





/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
bool shadowanamoly(int point_3[][2], int rows, int cols){ //function to perform anamoly check on the shadow
    for (int i=0;i<4;i++)
        if (point_3[i][0]<0 || point_3[i][0]>=cols || point_3[i][1]>=rows)
            return 0;
        else if (gameGrid[point_3[i][1]][point_3[i][0]])
            return 0;
    return 1;
}

bool bombanamoly(int bombpoint[], int rows, int cols){ // function to perform anamoly check on the bomb
    
    if (bombpoint[0]<0 || bombpoint[0]>=cols || bombpoint[1]>=rows)
        return 0;
    else if (gameGrid[bombpoint[1]][bombpoint[0]])
        return 0;
    return 1;
}

void sort(int arr[], int size) // performs insertion sort on the array that is read from the file
{                                  // This was used to sort the array to display highscores
    for (int i = 1; i < size; i++) 
    {
        int item = arr[i];
        int current = i - 1;
        while (arr[current] > item && current > -1)
        {
            arr[current + 1] = arr[current];
            current--;
        }
        arr[current + 1] = item;
    }
}

void shrinkGrid(int& rows, int& cols, int bombpoint[]) // This function shrinks the grid and the shrinked grid
{           // values are assigned to -1 so that it is displayed accordingly
    rows--;
    cols--;
    if (!anamoly(rows, cols)) // this feature pushes back the peice if grid is shrinked on it
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0]--;
        }
    }
    if (!bombanamoly(bombpoint, rows, cols)) // this feature pushes bomb back if grid is shrinked on it
        bombpoint[0] -= 1;
    for (int i = 0; i < M; i++)
    {
        gameGrid[i][cols] = -1;
    }
    for (int i = 0; i < N;i++)
    {
        gameGrid[rows][i] = -1;
    }
}


void nextPiece(int BLOCKS[][4], int nextblock, int next[][2], int nextblockcolor, int next2[][2], int nextblock2, int nextblockcolor2){ // assigns next blocks the shapes
            
    for (int i=0;i<4;i++){
        next[i][0] = BLOCKS[nextblock][i] % 2;
        next[i][1] = BLOCKS[nextblock][i] / 2;
    }
    for (int i=0;i<4;i++){
        next2[i][0] = BLOCKS[nextblock2][i] % 2;
        next2[i][1] = BLOCKS[nextblock2][i] / 2;
    }      
}



std::string getBombColor(std::string bombcolor[], int bombcolornum) // return bombcolor from the colors array
{
    return bombcolor[bombcolornum];
}
int get_score_add(int lines) // To get the score to be added according to the number of consecutive lines destroyed
{
    if (lines == 1)
        return 10;
    else if (lines == 2)
        return 30;
    else if (lines == 3)
        return 60;
    else if (lines == 4)
        return 100;
    else
        return 0;
}



void fallingshadow(float& timer, float& delay, int point_3[][2], int point_4[][2], int rows, int cols) // this function brings the shadow down
{ // just like falling peice but much quicker as the delay is a lot less for it
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_4[i][0]=point_3[i][0];
            point_4[i][1]=point_3[i][1];
            point_3[i][1]+=1;                   //How much units downward
        }
        timer=0;
        if (!shadowanamoly(point_3, rows, cols)){
            
            for (int i=0;i<4;i++){
                point_3[i][0] = point_4[i][0];
                point_3[i][1] = point_4[i][1];
            }
            
        }
    }

}
    


void fallingbomb(int bombpoint[], int bombpoint2[], float& timer, float& delay, std::string& color, std::string bombcolor[], int& bombcolorno, float time, int rows, int cols)
{ //This function holds all the functionality of the bomb
    if (timer > delay) // this block is for bringing the bomb down
    {
    
        bombpoint2[0]=bombpoint[0];
        bombpoint2[1]=bombpoint[1];
        bombpoint[1]+=1;
        timer = 0;
        if (!bombanamoly(bombpoint, rows, cols)){ // if bomb reaches the bottom
    
        if ((gameGrid[bombpoint[1]][bombpoint[0]] == (bombcolorno + 1)) && (color != " ")){ // if bomb color matches the block color
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    gameGrid[i][j] = 0; // whole grid clears
                }
            }
            
        }
        else if (gameGrid[bombpoint[1]][bombpoint[0]] != (bombcolorno + 1) && (bombpoint[1] < rows) && (color != " ")){ //here every case is discussed of bomb falling at different positions and destruction is accordingly
            if (bombpoint[1] < rows - 1 && bombpoint[0] < cols - 1)
            {   
                gameGrid[bombpoint[1]][bombpoint[0]] = 0;
                gameGrid[bombpoint[1] + 1][bombpoint[0]] = 0;
                gameGrid[bombpoint[1]][bombpoint[0] + 1] = 0;
                gameGrid[bombpoint[1] + 1][bombpoint[0] + 1] = 0;
            }
            if (bombpoint[1] == rows - 1 && bombpoint[0] == cols - 1){
                gameGrid[bombpoint[1]][bombpoint[0]] = 0;
                gameGrid[bombpoint[1]][bombpoint[0]] = 0;
            }
            if (bombpoint[1] == rows - 1 && bombpoint[0] < cols - 1)
            {
                gameGrid[bombpoint[1]][bombpoint[0]] = 0;
                gameGrid[bombpoint[1]][bombpoint[0] + 1] = 0;
            }
            if (bombpoint[1] < rows - 1 && bombpoint[0] == cols - 1){
                gameGrid[bombpoint[1]][bombpoint[0]] = 0;
                gameGrid[bombpoint[1] + 1][bombpoint[0]] = 0;
            }
        }
        
        bombcolorno = rand() % 14; // a different random color is assigned to the bomb
        color = getBombColor(bombcolor, bombcolorno);
        bombpoint[0] = rand() % cols; // a random position bomb is generated again
        bombpoint[1] = 0; //new bomb starts at top
    }
    }
    
}

std::string int_to_str(int n) // a very useful function which converts an integer value to string
{ // this function was used to convert score to string in order for it to be displayed
    if (n == 0)
        return "0";
    int digit;
    int count = 0;
    std::string str;
    int temp = n;
    while (temp > 0)
    {
        temp /= 10;
        count++;
    }
    int tens = pow(10, count - 1);
    while (n >= 0 && count != 0)
    {
        digit = n / tens;
        switch (digit)
        {
        case 1:
            str += '1';
            break;
        case 2:
            str += '2';
            break;
        case 3:
            str += '3';
            break;
        case 4:
            str += '4';
            break;
        case 5:
            str += '5';
            break;
        case 6:
            str += '6';
            break;
        case 7:
            str += '7';
            break;
        case 8:
            str += '8';
            break;
        case 9:
            str += '9';
            break;
        case 0:
            str += '0';
            break;
        }
        n = n % tens;
        tens /= 10;
        count--;
    }
    return str;
}

int count_complete_lines(int rows, int cols) // function to count the lines which are completed
{ // this function counts the consecutive lines and returns the specific number
    bool remove = true;
    int i = 0;
    int count = 0;
    while (i < rows)
    {
        remove = true;
        for (int j = 0; j < cols; j++)
        {
            if (!(gameGrid[i][j]))
            {
                remove = false;
            }
        }
        if (remove)
            count++;
        i++;
    }
    return count;
}

void move_left_right(int delta_x, int point_3[][2], int rows, int cols) // function to move the falling peice left and right 
{
    bool movable = true;
    if (delta_x == 1) //checking if right movement does not go out of bounds or overwrites a block
    {
        for (int i = 0; i < 4; i++)
        {
            if (point_1[i][0] + delta_x == cols || gameGrid[point_1[i][1]][point_1[i][0] + delta_x])
            {
                movable = false;
                break;
            }

        }
    }
    else if (delta_x == -1) //checking if left movement does not go out of bounds or overwrites a block
    {
        for (int i = 0; i < 4; i++)
        {
            if (point_1[i][0] + delta_x < 0 || gameGrid[point_1[i][1]][point_1[i][0] + delta_x])
            {
                movable = false;
                break;
            }
        }
    }
    if (movable) //if the movement checks pass block's position is adjusted accordingly
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] += delta_x;
            point_3[i][1] = point_1[i][1]; 
            point_3[i][0] = point_1[i][0];  //shadow coordinates are also updated to match falling peice
        }
    }
}

int clear_complete_line(int rows, int cols) // this finction clears the consecutive complete lines used to update the grid by setting 
{  // complete grid lines to zero
    bool remove = true;
    int i = 0;
    while (i < rows)
    {
        remove = true;
        for (int j = 0; j < cols; j++)
        {
            if (!(gameGrid[i][j]))
            {
                remove = false;
            }
        }
        if (remove)
        {
            for (int j = 0; j < cols; j++)
            {
                gameGrid[i][j] = 0;
            }
            for (int j = i; j >= 0; j--)
            {
                if (j == 0)
                {
                    for (int k = 0; k < cols; k++)
                        gameGrid[j][k] = 0;
                }
                else
                {
                    for (int k = 0; k < cols; k++)
                        gameGrid[j][k] = gameGrid[j - 1][k];
                }
            }
            break;
        }
        i++;
    }
    return i;
    
}
void update_after_clearing(int rows, int cols) // this function updates the grid after clearing by using the two defined functions for counting complete lines and clearing them
{  //this had to be used as a function so that the updation could go in one go.
    int count = count_complete_lines(rows, cols);
    for (int i = 0; i < count; i++)
    {
        clear_complete_line(rows, cols);
    }
}
int Gameover(int rows, int cols) //this function checks if blocks have reached at the top
{ // returns value accordingly
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < 4; j++)
        {    
            if ((gameGrid[1][i] && gameGrid[2][i]) && point_1[j][0] == i)
                return 1;
        }
    }
    return 0;
}
void Rotate(int point_3[][2], int rows, int cols) //Function for performing the rotation of the blocks
{
    int centerOfRotation[] = {point_1[1][0], point_1[1][1]}; //defining the center point around which the block is rotated
    int xoffset, yoffset;
    for (int i = 0; i < 4; i++)
    {
        xoffset = point_1[i][1] - centerOfRotation[1]; //how far from center 
        yoffset = point_1[i][0] - centerOfRotation[0];
        point_1[i][0] = centerOfRotation[0] + xoffset; //adding the x offset from center according to the identity matrix
        point_1[i][1] = centerOfRotation[1] - yoffset; //subtracting the y offset to center according to the identity matrix
    }
    if (!anamoly(rows, cols)){ //function checks if rotated point does not go out of bound 
        for (int i = 0; i < 4; i++){
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
    for (int i = 0; i < 4; i++) //this sets shadow point equal to falling peice after the changes
    {
        point_3[i][1] = point_1[i][1]; 
        point_3[i][0] = point_1[i][0];
    }
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////