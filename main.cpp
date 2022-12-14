/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
//Daniyal Faraz
//22I-1096
//Project
#include <cmath>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main(){
    srand(time(0));
    Music gamemusic;
    if (!gamemusic.openFromFile("music/TETRIS-Theme.ogg"))
        std::cout << "error" << std::endl;
    int rows = 20, cols = 10;
    int linesOfFile = 0; int scores[1000] = {0};
    std::ifstream filein("highscores.txt");
    while (!filein.eof())
    {
        filein >> scores[linesOfFile]; linesOfFile++;
    }
    filein.close();
    int BLOCKS[7][4] = {{1, 3, 5, 7} /*I*/, {2, 4, 5, 7} /*Z*/, {2, 3, 4, 5} /*O*/, {3, 5, 4, 7} /*T*/, {3, 5, 7, 6} /*J*/, {3, 5, 4, 6} /*S*/, {2, 3, 5, 7} /*L*/};
    std::string bombcolor[14] = {"red", "green", "magenta", " ", "cyan", "blue", "yellow", " ", " ", " ", " ", " ", " ", " "};
    int point_3[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    int point_4[4][2] = {{0}, {0}, {0}, {0}};
    int bombcolornum = 0;
    int bombpoint[2] = {0}, bombpoint2[2] = {0};
    int next[4][2] = {{0}, {0}, {0}, {0}};
    int next2[4][2] = {{0}, {0}, {0}, {0}};
    int nextblock = rand() % 7, nextblockcolornum = 1 + rand() % 7;
    int nextblock2 = rand() % 7, nextblockcolornum2 = 1 + rand() % 7;
    RenderWindow window(VideoMode(380, 480), title);
    Font font;
    font.loadFromFile("font/LioneyDemo.ttf");
    Text level_text;
    level_text.setFont(font); level_text.setCharacterSize(35);
    level_text.setString("Level\n   1"); level_text.setPosition(260, 150);
    Text gameover;
    gameover.setFont(font); gameover.setCharacterSize(55);
    gameover.setString("GAME OVER"); gameover.setFillColor(Color::Red);
    gameover.setPosition(75, 180);
    Text yourscore;
    yourscore.setFont(font); yourscore.setCharacterSize(30);
    yourscore.setString("YOUR SCORE");
    yourscore.setFillColor(Color::White); yourscore.setPosition(75, 180);
    Text pause_text;
    pause_text.setFont(font); pause_text.setCharacterSize(30); pause_text.setString("Paused. Press R to resume");
    pause_text.setPosition(20, 430);
    Text nexttext; nexttext.setFont(font); nexttext.setCharacterSize(30);
    nexttext.setString("NEXT");
    nexttext.setPosition(270, 20);
    Text dispscore;
    dispscore.setFont(font); dispscore.setCharacterSize(30); dispscore.setString("SCORE:");
    dispscore.setPosition(260, 250);
    Text scoretext; scoretext.setFont(font);
    scoretext.setCharacterSize(30); scoretext.setColor(Color::Black);
    scoretext.setString("Hello"); scoretext.setPosition(290, 330);
    int score = 0;
    Texture obj1, obj2, obj3, rect, shadow, bombimg, next_fig, next_fig2;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/Background1.png");
    obj3.loadFromFile("img/frame.png");
    rect.loadFromFile("img/fr.png");
    next_fig.loadFromFile("img/tiles.png");
    next_fig2.loadFromFile("img/tiles.png");
    bombimg.loadFromFile("img/My project.png");
    Text menu[4];
    menu[0].setFont(font);
    menu[0].setCharacterSize(40); menu[0].setColor(Color::Red); menu[0].setString("START");
    menu[0].setPosition(130, 100);
    menu[1].setFont(font);
    menu[1].setCharacterSize(40); menu[1].setColor(Color::White); menu[1].setString("RESTART");
    menu[1].setPosition(130, 150);
    menu[2].setFont(font);
    menu[2].setCharacterSize(40); menu[2].setColor(Color::White); menu[2].setString("HIGHSCORE");
    menu[2].setPosition(130, 200);
    menu[3].setFont(font);
    menu[3].setCharacterSize(40); menu[3].setColor(Color::White); menu[3].setString("EXIT");
    menu[3].setPosition(130, 250);
    bool showHighScore = false;
    int menuIndex = 0;
    bool showMenu = true;
    RectangleShape rectangle;
    rectangle.setFillColor(Color::White);
    rectangle.setSize(Vector2f(18, 18));
    rectangle.setPosition(50, 50);
    Sprite sprite(obj1), background(obj2), bomb(bombimg), frame(obj3), fr(rect), shade(shadow), next_block(next_fig), next_block2(next_fig2);
    Vector2f size(25.0f, 23.0f);
    Vector2f size2(380.0f, 480.0f);
    bomb.setScale(size.x / bomb.getLocalBounds().width, size.y / bomb.getLocalBounds().height);
    background.setScale(size2.x / background.getLocalBounds().width, size2.y / background.getLocalBounds().height);
    bomb.setColor(Color::Red);
    int delta_x=0, colorNum=1;
    float timer=0, bombtimer = 0, bombdelay = 0.5, shadowtimer = 0, delay=0.3, shadowdelay = 0.0000001;
    bool rotate=0;
    float overalltime = 0;
    int breakpoint = 15;
    int shrinkGridafter = 20;
    int level = 1;
    bool gameOver = false;
    std::string bombColor;
    bool pause = false;
    Clock clock;
    while (window.isOpen()){
        gamemusic.pause();
        if (level == 1) delay = 0.3;
        else if (level == 2) delay = 0.25;
        else if (level == 3) delay = 0.2;
        else if (level == 4) delay = 0.15;
        else if (level >= 5) delay = 0.1;
        bombdelay = 0.5;
        shadowdelay = 0.0000001;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        //overalltime += time;
        if (int(overalltime) > breakpoint){
            level++;
            breakpoint += 20;
        }
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up){            //Check if the other key pressed is UP key
                    if (showMenu) // if menu is shown proper navigation is done by the up key
                    {
                        if (menuIndex - 1 >= 0)
                        {
                            menu[menuIndex].setColor(Color::White);
                            menuIndex--;
                            menu[menuIndex].setColor(Color::Red);
                        }
                    }
                    else 
                        rotate = true;                         //Rotation gets on
                }
                else if (e.key.code == Keyboard::Left){     //Check if the other key pressed is LEFT key
                    
                    delta_x = -1;                          //Change in X-Axis - Negative
                    
                    if (!pause) move_left_right(delta_x, point_3, rows, cols);
                }
                else if (e.key.code == Keyboard::Right){    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                    if (!pause) move_left_right(delta_x, point_3, rows, cols);
                }
                else if (e.key.code == Keyboard::Space){ //when space bar pressed block is brought down in a loop
                    while (anamoly(rows, cols)){
                        for (int i = 0; i < 4; i++){
                            point_1[i][1] += 1;
                        }
                    }
                    for (int i = 0; i < 4; i++){ //piece should be on top of another block or grid
                        point_1[i][1] -= 1;
                    }
                }
                else if (e.key.code == Keyboard::H)
                {
                    pause = true;
                    showMenu = true;
                }
                else if (e.key.code == Keyboard::R)
                {
                    pause = false;
                }
                else if (e.key.code == Keyboard::Down)
                {
                    if (showMenu) //if menu is shown then proper navigation is done by down key
                    {
                        if (menuIndex + 1 < 4)
                        {
                            menu[menuIndex].setColor(Color::White);
                            menuIndex++;
                            menu[menuIndex].setColor(Color::Red);
                        }
                    }
                }
            }   
        }


        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        if (!showHighScore)
        {
            if (!showMenu)
            {
                if (!gameOver)
                {
                    if (!pause) //functions are called only if these checks are passed
                    {
                        gamemusic.play();
                        timer+=time;
                        shadowtimer += time;
                        bombtimer += time;
                        overalltime += time;
                        fallingshadow(shadowtimer, shadowdelay, point_3, point_4, rows, cols);
                        fallingPiece(BLOCKS, timer, delay, colorNum, point_3, next, nextblock, nextblockcolornum, next2, nextblock2, nextblockcolornum2, level, rows, cols);   //Example: fallingPiece() function is called here
                        fallingbomb(bombpoint, bombpoint2, bombtimer, bombdelay, bombColor, bombcolor, bombcolornum, overalltime, rows, cols);
                        nextPiece(BLOCKS, nextblock, next, nextblockcolornum, next2, nextblock2, nextblockcolornum2);
                        if (Gameover(rows, cols))
                            gameOver = true;
                        if (rotate)
                            Rotate(point_3, rows, cols);
                        rotate = false;
                        int lines = count_complete_lines(rows, cols);
                        score += (get_score_add(lines) * level);
                        scoretext.setString(int_to_str(score));
                        update_after_clearing(rows, cols);
                        if (int(overalltime) > shrinkGridafter){
                            shrinkGrid(rows, cols, bombpoint);
                            shrinkGridafter += 25;
                        }
                    }
                }
            }
        }
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
        

        if (bombColor == "red")
            bomb.setColor(Color::Red);
        else if (bombColor == "green")
            bomb.setColor(Color::Green);
        else if (bombColor == "magenta")
            bomb.setColor(Color::Magenta);
        else if (bombColor == "yellow")
            bomb.setColor(Color::Yellow);
        else if (bombColor == "cyan")
            bomb.setColor(Color::Cyan);
        else if (bombColor == "blue")
            bomb.setColor(Color::Blue);
        else if (bombColor == " ")
            bomb.setColor(Color::Transparent);

        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                if (gameGrid[i][j]==-1)
                {
                    rectangle.setPosition(j*18, i*18);
                    rectangle.move(28, 31);
                    window.draw(rectangle);
                    continue;
                }
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
        if (level <= 3) // two next suggestion should be shown till level 3 else 1
            {
                for (int i=0; i<4; i++){
                    next_block.setTextureRect(IntRect(nextblockcolornum*18,0,18,18));
                    next_block.setPosition(next[i][0]*18,next[i][1]*18);
                    next_block.move(250,60);
                    window.draw(next_block);
                }
                for (int i=0; i<4; i++){
                    next_block2.setTextureRect(IntRect(nextblockcolornum2*18,0,18,18));
                    next_block2.setPosition(next2[i][0]*18,next2[i][1]*18);
                    next_block2.move(320,60);
                    window.draw(next_block2);
                }
            }
        else
            {
                for (int i=0; i<4; i++){
                    next_block.setTextureRect(IntRect(nextblockcolornum*18,0,18,18));
                    next_block.setPosition(next[i][0]*18,next[i][1]*18);
                    next_block.move(280,60);
                    window.draw(next_block);
                }
            } 
        for (int i=0; i<4; i++){
            shade.setTextureRect(IntRect(colorNum*18,0,18,18));
            shade.setPosition(point_3[i][0]*18,point_3[i][1]*18);
            shade.move(28,31);
            shade.setColor(Color(255, 255, 255, 100));
            window.draw(shade);
          }
        bomb.setPosition(bombpoint[0] * 18, bombpoint[1] * 18);
        bomb.move(24, 31);
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        fr.setPosition(250, 290);
        window.draw(fr);
        if (level == 1) level_text.setString("Level\n   1");
        if (level == 2) level_text.setString("Level\n   2");
        if (level == 3) level_text.setString("Level\n   3");
        if (level == 4) level_text.setString("Level\n   4");
        if (level == 5) level_text.setString("Level\n   MAX");
        window.draw(level_text);
        window.draw(bomb);
        window.draw(scoretext);
        window.draw(dispscore);
        window.draw(nexttext);
        if (pause) window.draw(pause_text);
        if (showMenu) //drawing the menu window and showing and navigating options accordingly
        {
            
            window.clear(Color::Black);
            window.draw(background);
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (menuIndex == 0)
                {    
                    showMenu = false;
                    pause = false;
                }
                if (menuIndex == 1)
                {   
                    rows = 20; cols = 10;
                    delta_x=0, colorNum=1;
                    timer=0, bombtimer = 0, bombdelay = 0.5, shadowtimer = 0, delay=0.3, shadowdelay = 0.0000001;
                    rotate=0;
                    overalltime = 0;
                    breakpoint = 10;
                    shrinkGridafter = 10;
                    level = 1;
                    for (int i = 0; i < M; i++)
                    {
                        for (int j = 0; j < N; j++)
                        {
                            gameGrid[i][j] = 0;
                        }
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        point_1[i][0] = 0;
                        point_1[i][1] = 0;
                        point_3[i][0] = point_1[i][0];
                        point_3[i][1] = point_1[i][1];
                    }
                    bombpoint[0] = 0; bombpoint[1] = 0;
                    score = 0;
                    showMenu = false;
                    pause = false;
                }
                if (menuIndex == 2)
                {
                    if (!showHighScore)
                    {
                        sort(scores, linesOfFile + 1);
                        showHighScore = true;
                        showMenu = false;
                    }
                }
                if (menuIndex == 3)
                {
                    window.close();
                }
            }
           
            
            window.draw(menu[0]);
            window.draw(menu[1]);
            menu[2].setPosition(130, 200);
            window.draw(menu[2]);
            window.draw(menu[3]);
        }
        if (showHighScore) // the high score window to diplay the highest 6 scores
        {
            window.clear(Color::Black);
            window.draw(background);
            menu[2].setPosition(110, 70);
            window.draw(menu[2]);
            int y = 140;
            if (linesOfFile >= 5)
            {
                for (int i = linesOfFile; i >= linesOfFile - 5; i--)
                {
                    Text highScore; highScore.setFont(font);
                    highScore.setColor(Color::White); highScore.setString(int_to_str(scores[i]));
                    highScore.setCharacterSize(40);
                    highScore.setPosition(170, y);
                    window.draw(highScore);
                    y += 40;
                }
            } 
            else
            {
                for (int i = linesOfFile; i >= 0; i--)
                {
                    Text highScore; highScore.setFont(font);
                    highScore.setColor(Color::White); highScore.setString(int_to_str(scores[i]));
                    highScore.setCharacterSize(40);
                    highScore.setPosition(170, y);
                    window.draw(highScore);
                    y += 40;
                }
            }
            Text Exit; Exit.setFont(font);
            Exit.setColor(Color::Red); Exit.setString("Press Escape To Go Back");
            Exit.setCharacterSize(30);
            Exit.setPosition(70, y + 15);
            window.draw(Exit);
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                showHighScore = false;
                showMenu = true;
            }
        }
        if (gameOver) // the gameover window
        {
            window.clear(Color::Black);
            window.draw(background);
            yourscore.setPosition(110, 250);
            gameover.setPosition(100, 150);
            window.draw(yourscore);
            scoretext.setColor(Color::White);
            scoretext.setPosition(250, 250);
            window.draw(scoretext);
            window.draw(gameover);
        }
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    if (score != 0) // write score to file at the end of the program
    {
        scores[linesOfFile + 1] = score;
        linesOfFile++;
        std::ofstream fileout("highscores.txt", std::ios::app);
        fileout << std::endl;
        fileout << scores[linesOfFile] << std::endl;
        fileout.close();
    }
    return 0;
    }
