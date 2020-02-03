#ifndef IKEAWEBVIEW_HXX
#define IKEAWEBVIEW_HXX

#include <QWidget>

class QWebView;
class QLineEdit;
class QPushButton;
class QDoubleSpinBox;
class QLabel;
class QProcess;

class IKEAWebView : public QWidget {
  Q_OBJECT

public:
  IKEAWebView(QWidget* p_parent = nullptr);

private:
  QLineEdit* m_searchLineEdit;
  QWebView* m_webView;
  QPushButton* m_getInfoButton;
  QLineEdit* m_nameInfoLineEdit;
  QDoubleSpinBox* m_priceInfoEdit;
  QLabel* m_furnitureLabel;
  QProcess* m_getInfoProcess;
};

#endif
