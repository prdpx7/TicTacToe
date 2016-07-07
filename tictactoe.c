#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int chk_empty_cell(int empty[])
{
    int i;
    for(i=0;i<9;++i)
    {
        if(empty[i])
            return empty[i];
    }
    return 0;
}
void help()
{
    printf("user input should be in format: 1 1 (i.e RowIndex ColIndex ) \n");
    int i,j,k;
    for(i=0;i<3;++i)
    {
        for(k=0;k<3;++k)
        printf(" ____");
        printf("\n");
        for(j=0;j<3;++j)
            printf("| %d%d ",i+1,j+1);
        
        printf("\n");
    }

}

int find_move(char mat[4][5], char ch, int  flagbot)
{
    char dig[10];
    int i,j;
    char inv_dig[10];
    const char *pre_win_moves[3]; 
    if(ch == 'X')
    {
        pre_win_moves[0] = " XX";
        pre_win_moves[1] = "X X";
        pre_win_moves[2] = "XX ";
    }
    else
    {    
        pre_win_moves[0] = " OO";
        pre_win_moves[1] = "O O";
        pre_win_moves[2] = "OO ";
    }

    //check for upside string match 
    //X O X         X   X
    //  X     ==>   O X O
    //X O O         X   O
    char tmp_mat[4][5];
    for(i=0;i<=3;++i)
    {    
        for(j=0;j<=3;++j)
            tmp_mat[i][j] = mat[j][i];
        tmp_mat[i][j] = '\0';
    }
    
    for(i=1;i<=3;++i)
    {
        dig[i-1] = mat[i][i];
        inv_dig[i-1] = mat[i][4-i];
    }
    dig[i] = '\0';
    inv_dig[i] = '\0';
    
    //killer move breaker
    //X   X
    //  0
    //    X
    
    
    if( mat[2][2] == ' ')
        return 22;

    if(!flagbot && strcmp("X  ",tmp_mat[1]+1)==0 && strcmp("  X",mat[3]+1)==0)
        return 31;
    if(!flagbot && strcmp("  X",tmp_mat[3]+1)==0 && strcmp("X  ",mat[1]+1) == 0)
        return 13;


    for(i=1;i<=3;++i)
    {

        //printf("pre_win_moves[%d-1]=%s ,dig=%s\n",i,pre_win_moves[i-1],dig);
        //printf("pre_win_moves[%d-1]=%s ,inv_dig=%s\n",i,pre_win_moves[i-1],inv_dig);
        if(strcmp(pre_win_moves[i-1],dig)==0)
            return i*10 + i;
        if(strcmp(pre_win_moves[i-1],inv_dig)==0)
            return i*10 + 4-i;
        
        for(j=0;j<3;++j)
        {
            //printf("pre_win_moves[%d]=%s , mat[%d]=%s\n",j,pre_win_moves[j],i,mat[i]);
            //printf("pre_win_moves[%d]=%s , tmp_mat[%d]=%s\n",j,pre_win_moves[j],i,tmp_mat[i]);
            if(strcmp(pre_win_moves[j],mat[i]+1)==0)
            {
                return i*10 + j+1;
            }
            if(strcmp(pre_win_moves[j],tmp_mat[i]+1)==0)
                return (j+1)*10 + i;
            
        }
    }
        //random block selection
    return -1;

}

int win(char mat[4][5])
{
    int i, j;

    if(mat[1][1] == mat[2][2] && mat[2][2] == mat[3][3] && mat[1][1] != ' ')
        return 1;
    
    if(mat[1][3] == mat[2][2] && mat[2][2] == mat[3][1] && mat[1][3] != ' ')
        return 1;
    
    for(i = 1; i <= 3; ++i)
    {
        char prow = mat[i][1];
        char pcol = mat[1][i];
        int flag_prow = 1;
        int flag_pcol = 1;
        for(j = 1; j <= 3; ++j)
        {
           if(mat[i][j] != prow)
           {
               flag_prow = 0;
           }
           if(mat[j][i] != pcol)
           {
               flag_pcol = 0;
           }
        }
        if((flag_prow && prow != ' ')|| (flag_pcol && pcol != ' '))
            return 1;
    }
    return 0;
}
void display(char mat[4][5])
{
    printf("\n\n");
    int i,j,k;
    
    for(i = 1; i <= 3; ++i)
    {
        for(k = 1; k <= 3; ++k)
            printf(" ____");
        
        printf("\n");
        
        for(j = 1; j <= 3; ++j)
            printf("| %c  ",mat[i][j]);
        
        printf("\n");
    }
    
}
int main()
{
    int empty[9] = {11,12,13,21,22,23,31,32,33};
    int empsize = 9;
    char mat[4][5]={{' ',' ',' ',' ','\0'},{' ',' ',' ',' ','\0'},{' ',' ',' ',' ','\0'},{' ',' ',' ',' ','\0'}};
    int ch,i,r,c;
    char player,bot;
    help();
    printf("Choose: X or O(alphabet O) \n1.X\n2.O\n");
    scanf("%d",&ch);
    if(ch == 1)
    {
        player = 'X';
        bot = 'O';
    }
    else if(ch == 2)
    {
        bot = 'X';
        player = 'O';
    }
    else
    {
        printf("Invalid Choice....");
        exit(1);
    }
    for(i = 1; i <= 5; ++i)
    {
    
        printf("Player Move: \n");
        scanf("%d %d",&r,&c);
        if(!(r>=1 && r<=3 && c>=1 && c<=3 && mat[r][c] == ' '))
        {
            printf("Either Invalid Move Or Block Already Filled (Input Format must be RowIndex ColIndex)  \n\n\n");
            i-=1;
            continue;
        }
        mat[r][c] = player;
        empty[3*(r-1)+c-1] = 0;
        if(win(mat))
        {
            display(mat);
            printf("Player won");
            exit(0);
        }
        
        // check if bot is winning in next move
        int bot_move = find_move(mat,bot,1);
        if(bot_move != -1)
        {
            int x = bot_move;
            mat[x/10][x%10] = bot;
            if(win(mat))
            {
                printf("Bot Move %d %d\n",x/10,x%10);
                display(mat);
                printf("\n\nBot Won");
                exit(0);
            }
            else
                mat[x/10][x%10] = ' ';
        }
        // stopping player to win in his next move
        int player_next_move = find_move(mat,player,0);
        
        int x = player_next_move;
        //printf("x is %d\n",x);
        if(player_next_move == -1)
        {
            x = chk_empty_cell(empty);
            if(x == -1)
                break;
        }
        
        printf("Bot Move: %d %d\n",x/10,x%10);
        mat[x/10][x%10] = bot;
        display(mat);
        if(win(mat))
        {
       
            printf("Bot won\n");
            exit(0);
        }
        empty[3*(x/10-1)+(x%10-1)] = 0;
        /*
        printf("\n1 --- %s\n",mat[1]);
        printf("\n2 --- %s\n",mat[2]);
        printf("\n3 --- %s\n",mat[3]);
        */
    }
   
    printf("\n\n....DRAW......\n");
    return 0;
}
