#include "IKEAWebView.hxx"

#include <QtWebKitWidgets/QWebView>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QProcess>

#include <limits>

IKEAWebView::IKEAWebView(QWidget* p_parent):
  QWidget(p_parent),
  m_searchLineEdit(nullptr),
  m_webView(nullptr),
  m_getInfoButton(nullptr),
  m_nameInfoLineEdit(nullptr),
  m_priceInfoEdit(nullptr),
  m_furnitureLabel(nullptr),
  m_getInfoProcess(nullptr) {

  m_searchLineEdit = new QLineEdit;
  m_webView = new QWebView;
  m_getInfoButton = new QPushButton;
  m_getInfoButton->setFixedSize(40, 40);
  m_getInfoButton->setIconSize(QSize(32, 32));
  m_getInfoButton->setIcon(QIcon("../IKEA_Picker/icons/get.png"));
  m_nameInfoLineEdit = new QLineEdit;
  m_priceInfoEdit = new QDoubleSpinBox;
  m_priceInfoEdit->setRange(0., 99999.);
  m_priceInfoEdit->setSuffix("€");
  m_furnitureLabel = new QLabel;

  auto webAndInfoLayout = new QHBoxLayout;
  webAndInfoLayout->addWidget(m_webView);

  auto infoLayout = new QVBoxLayout;
  auto infoFormLayout = new QFormLayout;
  infoFormLayout->addRow("Name", m_nameInfoLineEdit);
  infoFormLayout->addRow("Price", m_priceInfoEdit);
  infoLayout->addWidget(m_getInfoButton);
  infoLayout->addLayout(infoFormLayout);
  infoLayout->addWidget(m_furnitureLabel);
  webAndInfoLayout->addLayout(infoLayout);
  webAndInfoLayout->setStretch(0, 3);
  webAndInfoLayout->setStretch(1, 1);

  auto mainLayout = new QVBoxLayout;
  mainLayout->addWidget(m_searchLineEdit);
  mainLayout->addLayout(webAndInfoLayout);
  setLayout(mainLayout);

  QString url("https://www.ikea.com/fr/fr/p/godmorgon-odensvik-meuble-lavabo-2tir-effet-chene-blanchi-dalskaer-mitigeur-lavabo-s59292855/");
  m_webView->load(QUrl(url));

  connect(m_webView, &QWebView::loadFinished, this, [this](){
    m_searchLineEdit->setText(m_webView->url().toString());
  });

  m_getInfoProcess = new QProcess(this);
  connect(m_getInfoProcess, &QProcess::readyReadStandardOutput, this, [this]() {
    QString infoStr(m_getInfoProcess->readAllStandardOutput());
    auto infoList = infoStr.split("\n");
    infoList.removeLast();
    QMap<QString, QString> infoMap;
    for (auto info: infoList) {
      auto infoTokens = info.split(":");
      if (infoTokens.size() == 2) {
        infoMap[infoTokens.at(0)] = infoTokens.at(1);
      }
    }
    m_nameInfoLineEdit->setText(infoMap["name"]);
    m_priceInfoEdit->setValue(infoMap["price"].toDouble());
  });

  connect(m_getInfoButton, &QPushButton::clicked, [this]() {
    m_getInfoProcess->start("../IKEA_Picker/scripts/GetIKEAInfo.py", {m_searchLineEdit->text()});
  });

  connect(m_getInfoProcess, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this, [this](int p_code){
    if (p_code == 0) {
      QPixmap pixmap("../IKEA_Picker/images/meuble.png");
      pixmap.scaledToWidth(m_nameInfoLineEdit->width());
      m_furnitureLabel->setPixmap(pixmap);
    }
  });
}
