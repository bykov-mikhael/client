#include "gui.h"

#include <QMessageBox>

GUI::GUI(QWidget *parent) : QWidget{parent} {
  QTextEdit *m_pteInfo = new QTextEdit();
  m_pteInfo->setReadOnly(true);

  QTextEdit *m_pteInput = new QTextEdit();
  QPushButton *m_pcmd = new QPushButton("send");
  QVBoxLayout *m_vMain = new QVBoxLayout();
  QLabel *m_lName = new QLabel("Client");

  m_vMain->addWidget(m_lName);
  m_vMain->addWidget(m_pteInfo);
  m_vMain->addWidget(m_pteInput);
  m_vMain->addWidget(m_pcmd);
  setLayout(m_vMain);

  connect(m_pcmd, SIGNAL(clicked(bool)), this, SLOT(slot_sendtoServer()));
  connect(m_pteInput, SIGNAL(returnPress), this, SLOT(slot_sendtoServer()));
}

void GUI::slot_SocketConnected() {
  m_pteInfo->append("Socket connected");
}

void GUI::slot_sendtoServer() {
  emit signal_sendToServer();
}
