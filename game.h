#ifndef GAME_H
#define GAME_H

#include <QRandomGenerator>
#include <QtGlobal>
#include <QVector>

class Game
{
public:
    Game(qint64 fieldSize);

    void top();
    void left();
    void right();
    void bottom();

    QVector<QVector<qint64> > getField() const;
    qint64 getScore() const;
    bool isGameOver() const;

    friend std::ostream& operator<< (std::ostream &out, const Game &game);
    friend bool operator!= (const Game &game1, const Game &game2);

private:
    QRandomGenerator random;
    QVector<QVector<qint64> > field_;
    qint64 score_;
    void addNew2();
    void rotateRightField(qint64 count);

    void setFieldsValue(qint64 column, qint64 row, qint64 value);
    void setScore(const qint64 value);

};

#endif // GAME_H
