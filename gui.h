#pragma once

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class GUI : public QWidget {
  Q_OBJECT
 public:
  explicit GUI(QWidget *parent = nullptr);

 private:
  // Указатели на элементы интерфейса
  QTextEdit *m_pteInfo;
  QTextEdit *m_pteInput;
  QPushButton *m_pcmd;
  QVBoxLayout *m_vMain;
  QLabel *m_lName;

 signals:
  void signal_sendToServer();

 public slots:
  void slot_SocketConnected();

 private slots:
  void slot_sendtoServer();
};
