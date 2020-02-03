#include "MainWindow.hxx"

#include <QApplication>

int main(int p_argc, char* p_argv[])
{
  QApplication a(p_argc, p_argv);
  MainWindow w;
  w.show();
  return a.exec();
}
