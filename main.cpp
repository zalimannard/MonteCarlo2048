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
    qint64 nIter = 1000;

    while (!game.isGameOver())
    {
        Game gameLeft = game;
        gameLeft.left();
        qint64 scoreLeft = 0;
        if (gameLeft != game)
        {
            scoreLeft = scoreRandomSide(gameLeft, nIter, random);
        }

        Game gameTop = game;
        gameTop.top();
        qint64 scoreTop = 0;
        if (gameTop != game)
        {
            scoreTop = scoreRandomSide(gameTop, nIter, random);
        }

        Game gameRight = game;
        gameRight.right();
        qint64 scoreRight = 0;
        if (gameRight != game)
        {
            scoreRight = scoreRandomSide(gameRight, nIter, random);
        }

        Game gameBottom = game;
        gameBottom.bottom();
        qint64 scoreBottom = 0;
        if (gameBottom != game)
        {
            scoreBottom = scoreRandomSide(gameBottom, nIter, random);
        }

        if ((scoreLeft >= scoreTop) && (scoreLeft >= scoreRight) && (scoreLeft >= scoreBottom))
        {
            game.left();
        }
        else if ((scoreTop >= scoreLeft) && (scoreTop >= scoreRight) && (scoreTop >= scoreBottom))
        {
            game.top();
        }
        else if ((scoreRight >= scoreLeft) && (scoreRight >= scoreTop) && (scoreRight >= scoreBottom))
        {
            game.right();
        }
        else if ((scoreBottom >= scoreLeft) && (scoreBottom >= scoreTop) && (scoreBottom >= scoreRight))
        {
            game.bottom();
        }
        clearConsole();
        std::cout << game << std::endl;
    }

    std::cout << "Итоговый счёт: " << game.getScore() << std::endl;

    return 0;
}
