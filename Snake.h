#pragma once
#include <QWidget>

class Snake : public QWidget
{
public:
  Snake(QWidget *pwgt = 0);

protected:
  void paintEvent(QPaintEvent *);
  void timerEvent(QTimerEvent *);
  void keyPressEvent(QKeyEvent *);

private:
  const int HEIGHT = 600;
  const int WIDTH = 600;
  const int SPEED = 200;
  const int CELL = 20;
  const int SIZE = 29;
  static const int FULL = 900;

  enum game
  {
    INTRO,
    IN_GAME,
    GAME_OVER
  };

  game state;

  int timer;
  int x[FULL];
  int y[FULL];
  int length;
  int aimX;
  int aimY;

  QImage aim;
  QImage head;
  QImage body;

  void init();
  void move();
  void place();
  void check();

  bool down;
  bool up;
  bool left;
  bool right;
};