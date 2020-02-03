#include "MainWindow.hxx"

#include "RoomTabWidget.hxx"
#include "IKEAWebView.hxx"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* p_parent):
  QMainWindow(p_parent) {

  m_roomTabWidget = new RoomTabWidget;
  m_roomTabWidget->setIconSize(QSize(64, 64));
  m_roomTabWidget->setTabPosition(QTabWidget::West);
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/bath-solid.png"), "");
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/utensils-solid.png"), "");
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/laptop-solid.png"), "");
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/couch-solid.png"), "");
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/book-solid.png"), "");
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/bed-solid.png"), "");
  m_roomTabWidget->addTab(new IKEAWebView, QIcon("../IKEA_Picker/icons/toilet-paper-solid.png"), "");

  setCentralWidget(m_roomTabWidget);

  showMaximized();
}

MainWindow::~MainWindow() = default;

