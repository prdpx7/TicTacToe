#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int empty[9]={0,0,0,0,0,0,0,0,0};
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
void display(char mat[3][4])
{
    printf("\n\n");
    int i,j,k;
    
    for(i = 0; i < 3; ++i)
    {
        for(k = 1; k <= 3; ++k)
            printf(" ____");
        
        printf("\n");
        
        for(j = 0; j < 3; ++j)
            printf("| %c  ",mat[i][j]);
        
        printf("\n");
    }
    
}
int chk_empty_cell(int empty[])
{
    int i;
    for(i=0;i<9;++i)
    {
        if(empty[i])
            return empty[i];
    }
    return -1;
}
int find_move(char mat[3][4],char ch, int flag)
{
    char dig[10];
    int i,j;
    char inv_dig[10];
    const char *pre_win_moves[3]; 
    if(ch == 'X')
    {
        pre_win_moves[0] = "_XX";
        pre_win_moves[1] = "X_X";
        pre_win_moves[2] = "XX_";
    }
    else
    {    
        pre_win_moves[0] = "_OO";
        pre_win_moves[1] = "O_O";
        pre_win_moves[2] = "OO_";
    }

    //check for upside string match 
    //X O X         X   X
    //  X     ==>   O X O
    //X O O         X   O
    char tmp_mat[3][4];
    for(i=0;i<3;++i)
    {    
        for(j=0;j<3;++j)
            {
            if(mat[i][j] == '_')
                empty[i*3+j] = 10*i + j;
            else
                empty[i*3+j] = 0;
            tmp_mat[i][j] = mat[j][i];
        }
        tmp_mat[i][j] = '\0';
    }
    
    for(i=0;i<3;++i)
    {
        dig[i] = mat[i][i];
        inv_dig[i] = mat[i][2-i];
    }
    dig[i] = '\0';
    inv_dig[i] = '\0';
    
    //killer move breaker
    //X   X
    //  0
    //    X
    
    
    if( mat[1][1] == '_')
        return 11;
    if(ch == 'X')
    {
        if(!flag && strcmp("X__",tmp_mat[0])==0 && strcmp("__X",mat[2])==0 ){
            if(strcmp("_O_",tmp_mat[1])==0)
                return 01;
            else
                return 20;
        }
        if(!flag && strcmp("__X",tmp_mat[2])==0 && strcmp("X__",mat[0]) == 0){
            if(strcmp("_O_",tmp_mat[1])==0)
                return 01;
            else
                return 02;
        }
      
    }
    else
        {
        if(!flag && strcmp("O__",tmp_mat[0])==0 && strcmp("__O",mat[2])==0){
            if(strcmp("_O_",tmp_mat[1])==0)
                return 01;
            else
                return 20;
        }
        if(!flag && strcmp("__O",tmp_mat[2])==0 && strcmp("O__",mat[0]) == 0){
            if(strcmp("_O_",tmp_mat[1])==0)
                return 01;
            else
                return 20;
        }
    }


    for(i=0;i<3;++i)
    {

        //printf("pre_win_moves[%d]=%s ,dig=%s\n",i,pre_win_moves[i],dig);
        //printf("pre_win_moves[%d]=%s ,inv_dig=%s\n",i,pre_win_moves[i],inv_dig);
        if(strcmp(pre_win_moves[i],dig)==0)
            return i*10 + i;
        if(strcmp(pre_win_moves[i],inv_dig)==0)
            return i*10 + 2-i;
        
        for(j=0;j<3;++j)
        {
            //printf("pre_win_moves[%d]=%s , mat[%d]=%s\n",j,pre_win_moves[j],i,mat[i]);
            //printf("pre_win_moves[%d]=%s , tmp_mat[%d]=%s\n",j,pre_win_moves[j],i,tmp_mat[i]);
            if(strcmp(pre_win_moves[j],mat[i])==0)
            {
                return i*10 + j;
            }
            if(strcmp(pre_win_moves[j],tmp_mat[i])==0)
                return j*10 + i;
            
        }
    }
        //random block selection
    return chk_empty_cell(empty);

}

int win(char mat[3][4])
{
    int i, j;

    if(mat[0][0] == mat[1][1] && mat[1][1] == mat[2][2] && mat[1][1] != '_')
        return 1;
    
    if(mat[0][2] == mat[1][1] && mat[1][1] == mat[2][0] && mat[2][0] != '_')
        return 1;
    
    for(i = 0; i < 3; ++i)
    {
        char prow = mat[i][0];
        char pcol = mat[0][i];
        int flag_prow = 1;
        int flag_pcol = 1;
        for(j = 0; j < 3; ++j)
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
        if((flag_prow && prow != '_')|| (flag_pcol && pcol != '_'))
            return 1;
    }
    return 0;
}



int main()
{
    char mat[3][4]={{'_','_','_','\0'},{'_','_','_','\0'},{'_','_','_','\0'}};
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
        r-=1;
        c-=1;
        if(!(r>=0 && r<3 && c>=0 && c<3 && mat[r][c] == '_'))
        {
            printf("Either Invalid Move Or Block Already Filled (Input Format must be RowIndex ColIndex)  \n\n\n");
            i-=1;
            continue;
        }
        mat[r][c] = player;
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
                printf("Bot Move %d %d\n",x/10+1,x%10+1);
                display(mat);
                printf("\n\nBot Won");
                exit(0);
            }
            else
                mat[x/10][x%10] = '_';
        }
        // stopping player to win in his next move
        int x = find_move(mat,player,0);
        
        if(x == -1)
        {
            break;
        }
        
        printf("Bot Move: %d %d\n",x/10+1,x%10+1);
        mat[x/10][x%10] = bot;
        display(mat);
        if(win(mat))
        {
       
            printf("Bot won\n");
            exit(0);
        }
    
    }
   
    printf("\n\n....DRAW......\n");
    return 0;
}
