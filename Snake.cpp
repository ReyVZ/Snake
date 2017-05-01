#include <QtWidgets>
#include "Snake.h"

Snake::Snake(QWidget *pwgt) : QWidget(pwgt)
{
    state = INTRO;
    resize(HEIGHT, WIDTH);
    setStyleSheet("background-image: url(back.jpg);");
    aim.load("red.png");
    head.load("blue.png");
    body.load("green.png");

    init();
}

void Snake::init()
{
    down = false;
    up = false;
    left = false;
    right = true;
    length = 3;
    for (int n = 0; n < length; n++)
    {
        x[n] = (5 - n) * CELL;
        y[n] = 5 * CELL;
    }
    place();
}

void Snake::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    QFont font("serif", 30, QFont::Bold);
    painter.setPen(Qt::white);
    painter.setFont(font);
    QRect boundingRect;

    if (state == INTRO)
    {
        painter.drawText(0, 150, 600, 600, Qt::AlignHCenter, tr("Press UP, DOWN, LEFT\nand RIGHT keys\nto rule the snake!\n\n\nPress SPACE\nto start the game"), &boundingRect);
    }

    if (state == IN_GAME)
    {
        for (int n = 0; n < length; n++)
        {
            if (n == 0)
            {
                painter.drawImage(x[n], y[n], head);
            }
            else
            {
                painter.drawImage(x[n], y[n], body);
            }
        }

        painter.drawImage(aimX, aimY, aim);
    }
    if (state == GAME_OVER)
    {
        painter.drawText(0, 250, 600, 600, Qt::AlignHCenter, tr("Game Over!"), &boundingRect);
    }
}

void Snake::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    move();
    check();
    repaint();
}

void Snake::move()
{
    for (int n = length; n > 0; n--)
    {
        x[n] = x[n - 1];
        y[n] = y[n - 1];
    }

    if (down)
    {
        y[0] += CELL;
    }
    if (up)
    {
        y[0] -= CELL;
    }
    if (left)
    {
        x[0] -= CELL;
    }
    if (right)
    {
        x[0] += CELL;
    }
}

void Snake::check()
{
    if (x[0] == aimX && y[0] == aimY)
    {
        length++;
        place();
    }
    if (x[0] < 0 || x[0] == WIDTH || y[0] < 0 || y[0] == HEIGHT)
    {
        state = GAME_OVER;
    }
    for (int n = length; n > 0; n--)
    {
        if (x[0] == x[n] && y[0] == y[n])
        {
            state = GAME_OVER;
        }
    }
}

void Snake::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Space)
    {
        init();
        if (state == INTRO)
        {
            timer = startTimer(SPEED);
        }
        state = IN_GAME;
    }
    if ((e->key() == Qt::Key_Down) && (!up))
    {
        down = true;
        left = false;
        right = false;
    }
    if ((e->key() == Qt::Key_Up) && (!down))
    {
        up = true;
        left = false;
        right = false;
    }
    if ((e->key() == Qt::Key_Left) && (!right))
    {
        left = true;
        up = false;
        down = false;
    }
    if ((e->key() == Qt::Key_Right) && (!left))
    {
        right = true;
        up = false;
        down = false;
    }
}

void Snake::place()
{
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    aimX = qrand() % SIZE * CELL;
    aimY = qrand() % SIZE * CELL;
}