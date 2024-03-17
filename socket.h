#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QTextEdit>
#include <QWidget>

class Socket : public QWidget {
  Q_OBJECT

 public:
  Socket(const QString& serverName, qint16 port, QWidget* parent = 0);
  ~Socket();

 private:
  // Указатель на QLocalSocket
  QTcpSocket* localSocket;

  // Указатели на элементы интерфейса
  QTextEdit* m_pteInfo;
  QTextEdit* m_pteInput;
  // Размер принимаемого от сервера блока
  quint16 nextBlockSize;

  // Номер ревизии, отправляемый серверу
  // Увеличивается при каждом нажатии QPushButton
  int revision;

 signals:
  void signal_SocketConnected();

 public slots:
  // Слот передачи информации на сервер
  void slotSendToServer();

 private slots:
  // Слот чтения информации, получаемой от сервера
  void slotReadyRead();

  // Слот обработки ошибок сокета
  void slotError(QAbstractSocket::SocketError);

  // Слот обработки сигнала соединения с сервером
  void slotConnected();
};
