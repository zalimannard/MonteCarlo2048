#include <QCoreApplication>

#include "game.h"
#include <QtGlobal>
#include <QRandomGenerator>
#include <iostream>

qint64 scoreRandomSide(Game game, qint64 iter, QRandomGenerator random)
{
    for (qint64 i = 0; i < iter; ++i)
    {
        qint64 side = random.generate() % 4;
        if (side == 0)
        {
            game.left();
        }
        else if (side == 1)
        {
            game.top();
        }
        else if (side == 2)
        {
            game.right();
        }
        else if (side == 3)
        {
            game.bottom();
        }
    }
    return game.getScore();
}

void clearConsole()
{
    std::cout << "\x1B[2J\x1B[H";
}

int main(int argc, char *argv[])
{
    clearConsole();
    QCoreApplication a(argc, argv);

    qint64 sideSize = 4;

    Game game(sideSize);

    std::cout << game << std::endl;

    QRandomGenerator random = QRandomGenerator(1);
    qint64 nIter = 100;

    while (!game.isGameOver())
    {
        qint64 bestSide = 0;
        qint64 bestScore = 0;
        for (qint64 i = 0; i < 10; ++i)
        {
            qint64 newSide = random.generate() % 4;

            if (newSide == 0)
            {
                Game gameLeft = game;
                gameLeft.left();
                if (gameLeft != game)
                {
                    qint64 score = scoreRandomSide(gameLeft, nIter, random);
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestSide = 0;
                    }
                }
            }
            else if (newSide == 1)
            {
                Game gameTop = game;
                gameTop.top();
                if (gameTop != game)
                {
                    qint64 score = scoreRandomSide(gameTop, nIter, random);
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestSide = 1;
                    }
                }
            }
            else if (newSide == 2)
            {
                Game gameRight = game;
                gameRight.right();
                if (gameRight != game)
                {
                    qint64 score = scoreRandomSide(gameRight, nIter, random);
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestSide = 2;
                    }
                }
            }
            else if (newSide == 3)
            {
                Game gameBottom = game;
                gameBottom.bottom();
                if (gameBottom != game)
                {
                    qint64 score = scoreRandomSide(gameBottom, nIter, random);
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestSide = 3;
                    }
                }
            }
        }
        if (bestSide == 0)
        {
            game.left();
        }
        else if (bestSide == 1)
        {
            game.top();
        }
        else if (bestSide == 2)
        {
            game.right();
        }
        else if (bestSide == 3)
        {
            game.bottom();
        }
        clearConsole();
        std::cout << game << std::endl;
    }

    std::cout << "Итоговый счёт: " << game.getScore() << std::endl;

    return 0;
}
