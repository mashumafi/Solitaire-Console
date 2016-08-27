#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <stdio.h>

#if __unix__
#include <termios.h>
#include <unistd.h>
int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;
  
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
  
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
}
char getkey(void)
{
  int ch;
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  while (!kbhit())
  {
  }
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
#elif _WINDOWS
#include <conio.h>
char getkey(void)
{
  while(!kbhit())
  {
  }
  return getch();
}
#else
#endif
#endif