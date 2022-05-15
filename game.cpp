#include "game.h"

#include <QTime>
#include <iostream>

Game::Game(qint64 fieldSize)
{
    setScore(0);
    QVector<qint64> row(fieldSize, 0);
    field_ = QVector<QVector<qint64> >(fieldSize, row);
    addNew2();

    random = QRandomGenerator(time(NULL));
}

void Game::top()
{
    QVector<QVector<qint64> > field = getField();
    qint64 nRow = field.size();
    qint64 nColumn = field[0].size();
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            if (field[row][column] != 0)
            {
                bool isMerged = false;
                bool isAbove = (row == 0);
                qint64 rowOffset = 0;
                while (!isAbove)
                {
                    if (row - rowOffset == 0)
                    {
                        isAbove = true;
                    }
                    else if (field[row - rowOffset - 1][column] == 0)
                    {
                        field[row - rowOffset - 1][column] = field[row - rowOffset][column];
                        field[row - rowOffset][column] = 0;
                        ++rowOffset;
                    }
                    else if ((field[row - rowOffset - 1][column] == field[row - rowOffset][column]) &&
                        (!isMerged))
                    {
                        setScore(getScore() + 2 * field[row - rowOffset - 1][column]);
                        field[row - rowOffset - 1][column] *= 2;
                        field[row - rowOffset][column] = 0;
                        ++rowOffset;
                    }
                    else
                    {
                        isAbove = true;
                    }
                }
            }
        }
    }
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            setFieldsValue(column, row, field[column][row]);
        }
    }
    addNew2();
}

void Game::left()
{
    rotateRightField(1);
    top();
    rotateRightField(3);
}

void Game::right()
{
    rotateRightField(3);
    top();
    rotateRightField(1);
}

void Game::bottom()
{
    rotateRightField(2);
    top();
    rotateRightField(2);
}

QVector<QVector<qint64> > Game::getField() const
{
    return field_;
}

qint64 Game::getScore() const
{
    return score_;
}

void Game::setScore(const qint64 value)
{
    score_ = value;
}

bool Game::isGameOver() const
{
    QVector<QVector<qint64> > field = getField();
    qint64 nColumn = field.size();
    qint64 nRow = field[0].size();
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            if (field[row][column] == 0)
            {
                return false;
            }
        }
    }
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow - 1; ++row)
        {
            if (field[row][column] == field[row + 1][column])
            {
                return false;
            }
        }
    }
    for (qint64 column = 0; column < nColumn - 1; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            if (field[row][column] == field[row][column + 1])
            {
                return false;
            }
        }
    }
    return true;
}

void Game::addNew2()
{
    QVector<QVector<qint64> > field = getField();
    qint64 nColumn = field.size();
    qint64 nRow = field[0].size();
    bool isZeroExist = false;
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            if (field[row][column] == 0)
            {
                isZeroExist = true;
            }
        }
    }
    if (isZeroExist)
    {
        bool added = false;
        QVector<QVector<qint64> > field = getField();
        while (!added)
        {
            qint64 column = (qint64) random.generate() % field.size();
            qint64 row = (qint64) random.generate() % field[0].size();
            if (field[column][row] == 0)
            {
                setFieldsValue(column, row, 2);
                added = true;
            }
        }
    }
}

void Game::rotateRightField(qint64 count)
{
    for (qint64 r = 0; r < count % 4; ++r)
    {
        QVector<QVector<qint64> > oldField = getField();
        QVector<QVector<qint64> > newField = getField();
        qint64 nRow = oldField.size();
        qint64 nColumn = oldField[0].size();
        for (qint64 column = 0; column < nColumn; ++column)
        {
            for (qint64 row = 0; row < nRow; ++row)
            {
                newField[column]
                        [nRow - 1 - row] = oldField[row][column];
            }
        }

        for (qint64 column = 0; column < nColumn; ++column)
        {
            for (qint64 row = 0; row < nRow; ++row)
            {
                setFieldsValue(row, column, newField[row][column]);
            }
        }
    }
}

void Game::setFieldsValue(qint64 row, qint64 column, qint64 value)
{
    field_[row][column] = value;
}

qint64 intLenght(qint64 value)
{
    qint64 answer = 1;
    while (value > 9)
    {
        ++answer;
        value /= 10;
    }
    return answer;
}

std::ostream& operator<< (std::ostream &out, const Game &game)
{
    QVector<QVector<qint64> > field = game.getField();
    qint64 nColumn = field.size();
    qint64 nRow = field[0].size();
    qint64 maxLength = 0;
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            if (intLenght(field[column][row]) > maxLength)
            {
                maxLength = intLenght(field[column][row]);
            }
        }
    }
    for (qint64 column = 0; column < nColumn; ++column)
    {
        for (qint64 row = 0; row < nRow; ++row)
        {
            out << field[column][row];
            for (qint64 i = 0; i < maxLength - intLenght(field[column][row]) + 1; ++i)
            {
                out << ' ';
            }
        }
        out << std::endl;
    }
    return out;
}

bool operator!= (const Game &game1, const Game &game2)
{
    bool isEqual = true;
    if (game1.getScore() != game2.getScore())
    {
        isEqual = false;
    }
    QVector<QVector<qint64> > field1 = game1.getField();
    QVector<QVector<qint64> > field2 = game2.getField();
    for (qint64 i = 0; i < field1.size(); ++i)
    {
        for (qint64 j = 0; j < field1[0].size(); ++j)
        {
            if (field1[i][j] != field2[i][j])
            {
                isEqual = false;
            }
        }
    }
    return !isEqual;
}
