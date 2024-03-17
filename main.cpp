/*
 * TODO перенос на boost::asio; принцип работы одинаковый, сначала запускается
 * сервер - listen(номер порта), затем к нему подключаются клиенты через socket
 * TODO перенос в visual studio code с изменением архзитектуры проекта (папки и
 * классы)
 * TODO разобраться с cmake при подключении библиотек из класса окна
 * BUG не работают кастомные слоты через сигналы и отдельный класс
 * графической оболочки
 * NOTE реализовать обмен с информационными системами по
 * протоколоам REST API и samba
 */

#include "gui.h"
#include "socket.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Socket socket("127.0.0.1", 2323);
    socket.show();

//    GUI gui;
//    gui.show();

//    QObject::connect(&gui, SIGNAL(signal_sendToServer()),
//                     &socket, SLOT(slotReadyRead()));

//    QObject::connect(&socket, SIGNAL(signal_SocketConnected()),
//                     &gui, SLOT(slot_SocketConnected()));

    return app.exec();
}
