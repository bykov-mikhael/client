#include "socket.h"

#include <QLabel>
#include <QMessageBox>
#include <QTime>
#include <QVBoxLayout>

Socket::Socket(const QString &serverName, qint16 port, QWidget *parent)
    : QWidget(parent),
      nextBlockSize(0)
// Устанавливаем nextBlockSize и revision равными нулю
{
  // Инициализируем сокет
  localSocket = new QTcpSocket(this);

  localSocket->connectToHost(serverName, port);

  // Устанавливаем соединение между сигналом подключения сокета к серверу
  // и обработчиком сигнала
  connect(localSocket, SIGNAL(connected()), SLOT(slotConnected()));
  // Соединяем сигнал сокета о готовности приёма данных данных с обработчиком
  // данных
  connect(localSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));

  connect(localSocket, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(QAbstractSocket::SocketError));

  // Инициализируем элементы интерфейса
  m_pteInfo = new QTextEdit;
  m_pteInput = new QTextEdit;

  m_pteInfo->setReadOnly(true);

  QPushButton *pcmd = new QPushButton("send");

  // Соединяем нажатие кнопки с обработчиком, передающим информацию о ревизии на
  // сервер
  connect(pcmd, SIGNAL(clicked()),
          this, SLOT(slotSendToServer()));

  connect(m_pteInput, SIGNAL(returnPress),
          this, SLOT(slotSendToServer()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(new QLabel("Client"));
  layout->addWidget(m_pteInfo);
  layout->addWidget(m_pteInput);
  layout->addWidget(pcmd);
  setLayout(layout);
}

Socket::~Socket() {}

// Слот чтения информации, получаемой от сервера
void Socket::slotReadyRead() {
  // Всё аналогично приёму информации на стороне сервера
  QDataStream in(localSocket);
  in.setVersion(QDataStream::Qt_5_3);
  for (;;) {
    if (!nextBlockSize) {
      if (localSocket->bytesAvailable() < (int)sizeof(quint16)) break;
    }

    in >> nextBlockSize;

    if (localSocket->bytesAvailable() < nextBlockSize) break;

    QTime time;
    QString string;
    in >> time >> string;

    m_pteInfo->append(time.toString() + " " + string);
    nextBlockSize = 0;
  }
}

// Слот обработки ошибок сокета
void Socket::slotError(QAbstractSocket::SocketError error) {
  QString strError =
      "Error: " + (error == QAbstractSocket::HostNotFoundError
                       ? "The server was not found."
                   : error == QAbstractSocket::RemoteHostClosedError
                       ? "The server is closed."
                   : error == QAbstractSocket::ConnectionRefusedError
                       ? "The connection was refused."
                       : QString(localSocket->errorString()));
  m_pteInfo->append(strError);
}
/*
 * Слот передачи информации на сервер
 */
void Socket::slotSendToServer() {
  // Блок для передачи формируется аналогично тому, как это делается на сервере
  QByteArray arrayBlock;
  QDataStream out(&arrayBlock, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_3);
  ++revision;
  //  QString message = "Revision: " + QString("%1").arg(revision);

  // отправка тектса из QTextEdit
  QString message = m_pteInput->toPlainText();

  out << quint16(0) << QTime::currentTime() << message;

  out.device()->seek(0);
  out << quint16(arrayBlock.size() - sizeof(quint16));

  localSocket->write(arrayBlock);

  m_pteInput->clear();
}

// Слот обработки сигнала соединения с сервером
void Socket::slotConnected() {
  m_pteInfo->append("Received the connected() signal");

  emit signal_SocketConnected();
}
