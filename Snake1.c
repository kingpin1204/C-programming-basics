    #include <stdio.h>  
    #include <conio.h>  
    #include <time.h>  
    #include <dos.h>  
    #include <stdlib.h>  
    #define TURE 1  
    #define FALSE 0  
    #define WALL_UP 1  
    #define WALL_DOWN 15  
    #define WALL_LEFT 20  
    #define WALL_RIGHT 60  
    #define UP 1  
    #define DOWN 2  
    #define LEFT 3  
    #define RIGHT 4  
    #define QUIT 5  
    // define struct  
    typedef struct _SNAKE  
    {  
        int x,y;  
    }SNAKE;  
    /////////////////////////////////////////  
    // define value  
    SNAKE snake[250];  
    SNAKE food;  
    int snakeLength;  
    int key;  // user press key code  
    int isEat; // Does snake eat food ?  
    int level; // game level  
    int speed; // snake move speed  
    int move_index;  
    int score; // game score  
    ////////////////////////////////////////  
    // Game control function  
    void NewGame();  
    void PlayGame();  
    int ExitGame();  
    // Paint function  
    void PaintBackground();  
    void PaintInformation();  
    void PaintSnake();  
    // Contorl function  
    void ControlKey();  
    int MoveSnake();  
    void RandomFood();  
    void CheckEat();  
    int CheckHit();  
    int CheckFoodNoHitSnake();  
    void SetGameLevel();  
    ////////////////////////////////////////////  
    void main()  
    {  
        srand(time(NULL));  
        while(TURE)  
        {  
            NewGame();  
            PlayGame();  
            if( ExitGame() )  
                break;  
        } // end of while  
    } // end of main  
    /////////////////////////////////////////////////////  
    void NewGame()  
    {  
        int i;  
        snakeLength = 5;  
        level = 1;  
        move_index = 0;  
        score = 0;  
        for(i = 0 ; i < snakeLength ;i++)  
        {  
            snake[i].x = 30 - i;  
            snake[i].y = 10;  
        }// end of for  
        key = RIGHT;  
        isEat = TURE;  
        clrscr();  
        textcolor(12);  
        gotoxy(10,10);  
        cprintf("@@ @@ @@ @@@@@@@ @@      @@@@@@@ @@@@@@@ @@      @@ @@@@@@@");  
        gotoxy(10,11);  
        cprintf("@@ @@ @@ @@      @@      @@      @@   @@ @@@    @@@ @@");  
        gotoxy(10,12);  
        cprintf("@@ @@ @@ @@@@@@@ @@      @@      @@   @@ @@ @  @ @@ @@@@@@@");  
        gotoxy(10,13);  
        cprintf("@@ @@ @@ @@      @@      @@      @@   @@ @@  @@  @@ @@");  
        gotoxy(10,14);  
        cprintf(" @@@@@@  @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@  @@  @@ @@@@@@@");  
        gotoxy(28,17);  
        textcolor(13 + 128);  
        cprintf("Press anykey to start");  
        getch();  
    } // end of NewGame  
    void PlayGame()  
    {  
        clrscr();  
        PaintBackground();  
        PaintInformation();  
        while(key != QUIT)  
        {  
            //clrscr();  
            SetGameLevel();  
            ControlKey();  
            RandomFood();  
            MoveSnake();  
            CheckEat();  
            if(CheckHit())  
                break;  
            //PaintBackground();  
            //PaintInformation();  
            PaintSnake();  
            delay(30);  
        } // end of while*/  
    } // end of PlayGame  
    int ExitGame()  
    {  
        clrscr();  
        textcolor(14);  
        gotoxy(25,12);  
        cprintf("If you want to play again ?");  
        gotoxy(25,14);  
        cprintf("Press y/n");  
        int bye;  
        char input;  
        while(TURE)  
        {  
            input = getch();  
            if(input == 'Y' || input == 'y')  
            {  
                bye = FALSE;  
                break;  
            } // end of if  
            if(input == 'N' || input == 'n')  
            {  
                bye = TURE;  
                break;  
            }// end of if  
        }// end of while  
        return bye;  
    } // end of ExitGame  
    ///////////////////////////////////////////  
    void PaintBackground()  
    {  
        int i,j;  
        textcolor(10);  
        for(i = WALL_UP ; i <= WALL_DOWN ; i++)  
        {  
            for(j = WALL_LEFT;j <= WALL_RIGHT ; j++)  
            {  
                gotoxy(j,i);  
                if(j == WALL_LEFT)  
                    cprintf("@");  
                else if(j == WALL_RIGHT)  
                    cprintf("@");  
                else if(i == WALL_UP)  
                    cprintf("@");  
                else if(i == WALL_DOWN)  
                    cprintf("@");  
            } // end of for  
        } // end of for  
    } // end of PaintBackground  
    void PaintInformation()  
    {  
        textcolor(12);  
        gotoxy(15,19);  
        cprintf("@@@@");  
        textcolor(15);  
        cprintf("HELP");  
        textcolor(12);  
        cprintf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");  
        gotoxy(15,20);  
        cprintf("@@     Press w(up),a(left),s(down),d(right)      @@");  
        gotoxy(15,21);  
        cprintf("@@     to move snake.                            @@");  
        gotoxy(15,22);  
        cprintf("@@     Press q to exit                           @@");  
        gotoxy(15,23);  
        cprintf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");  
    } // end of PaintInformation  
    void PaintSnake()  
    {  
        int i;  
        textcolor(9);  
        gotoxy(food.x,food.y);  
        cprintf("$"); // paint food  
        textcolor(11);  
        for(i = 0 ; i < snakeLength ; i++)  
        {  
            gotoxy(snake[i].x,snake[i].y);  
            cprintf("@");  
        }  
    } // end of PaintSnake  
    void ControlKey()  
    {  
        char input;  
        if(kbhit())  
        {  
            input = getch();  
            if((input == 'w' || input == 'W') && key != DOWN)  
                key = UP;  
            else if((input == 's' || input == 'S') && key != UP)  
                key = DOWN;  
            else if((input == 'a' || input == 'A') && key != RIGHT)  
                key = LEFT;  
            else if((input == 'd' || input == 'D') && key != LEFT)  
                key = RIGHT;  
            else if(input == 'q' || input == 'Q')  
                key = QUIT;  
        } // end of if  
    } // end of ControlKey  
    int MoveSnake()  
    {  
        SNAKE next;  
        int i;  
        for(i = 0 ; i < snakeLength ; i++)  
        {  
            // clear snake  
            gotoxy(snake[i].x,snake[i].y);  
            cprintf(" ");  
        } // end of for  
        // Check snake can move  
        if(move_index > speed)  
            move_index = 0;  
        else  
        {  
            move_index++;  
            return FALSE;  
        } // end of else  
        // move snake  
        switch(key)  
        {  
            case UP:  
                next.x = snake[0].x;  
                next.y = snake[0].y - 1;  
                break;  
            case DOWN:  
                next.x = snake[0].x;  
                next.y = snake[0].y + 1;  
                break;  
            case LEFT:  
                next.x = snake[0].x - 1;  
                next.y = snake[0].y;  
                break;  
            case RIGHT:  
                next.x = snake[0].x + 1;  
                next.y = snake[0].y;  
                break;  
        } // end of switch  
        for(i = snakeLength - 1 ; i > 0 ; i--)  
        {  
            snake[i].x = snake[i - 1].x;  
            snake[i].y = snake[i - 1].y;  
        } // end of for  
        snake[0].x = next.x;  
        snake[0].y = next.y;  
        return TURE;  
    } // end of MoveSnake  
    void RandomFood()  
    {  
        if(isEat)  
        {  
            // clear old food and random a new food  
            gotoxy(food.x,food.y);  
            cprintf(" ");  
            while(TURE)  
            {  
                food.x = rand() % 38 + 22;  
                food.y = rand() % 13 + 2;  
                if(CheckFoodNoHitSnake())  
                    break;  
            } // end of while  
            isEat = FALSE;  
        } // end of if  
    } // end of RandomFood  
    void CheckEat()  
    {  
        if(food.x == snake[0].x && food.y == snake[0].y)  
        {  
            score = score + level * 10;  
            isEat = TURE;  
            sound(100);  
            delay(30);  
            nosound();  
            snakeLength++;  
        } // end of if  
    } // end of CheckEat  
    int CheckHit()  
    {  
        int gameover = FALSE;  
        if(snake[0].x <= WALL_LEFT || snake[0].x >= WALL_RIGHT)  
            gameover = TURE;  
        if(snake[0].y <= WALL_UP || snake[0].y >= WALL_DOWN)  
            gameover = TURE;  
        int i;  
        for(i = 1 ; i < snakeLength ; i++)  
        {  
            if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)  
            {  
                gameover = TURE;  
                break;  
            } // end of if  
        } // end of for  
        if(gameover)  
        {  
            clrscr();  
            textcolor(13 + 128);  
            gotoxy(33,13);  
            cprintf("Game Over");  
            delay(3000);  
        } // end of if  
        return gameover;  
    } // end of CheckHit  
    int CheckFoodNoHitSnake()  
    {  
        int i;  
        for(i = 0 ; i < snakeLength ; i++)  
        {  
            if(food.x == snake[i].x && food.y == snake[i].y)  
                return FALSE;  
        } // end of for  
        return TURE;  
    } // end of CheckFoodNoHitSnake  
    void SetGameLevel()  
    {  
        if(level <= 10)  
        {  
            level = snakeLength / 5;  
        } // end of if  
        speed = 11 - level;  
        gotoxy(25,18);  
        cprintf("Game Level : %2d  ",level);  
        cprintf("Score : %d",score);  
    } // end of SetGameLevel  
