#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>

class RoomTabWidget;

class MainWindow: public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* p_parent = nullptr);
  ~MainWindow();

private:
  RoomTabWidget* m_roomTabWidget;
};

#endif
