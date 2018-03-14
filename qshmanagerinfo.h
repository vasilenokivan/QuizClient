#ifndef QSHMANAGERINFO_H
#define QSHMANAGERINFO_H
#include <QApplication>
#include <QMutex>
#include "qthreadobject.h"
#include "TransportParser/QJSONParser.h"
#include "QThreadSocket.h"
#include "qjsontask.h"
//#include "guiprop.h"
//#include "tasks/qjsontask.h"

class QSHManagerInfo : public QThreadObject
{
    Q_OBJECT
public:
    explicit QSHManagerInfo(QObject *parent = 0, const QString & path = QString());
    virtual ~QSHManagerInfo();
    //отправка JSON event/событие в сокет с возможностью добавления доп. информации в additional_json_fields(например QString("\"ip\":\"192.168.0.11\""))
    void sendEvent(const QString & event,const QString & additional_json_fields = QString());
    //Отправка команды, аналог сигнал/слот
    void sendCommand(const QString & command,QJSONTask::JSON_ANSWER_WAIT parser = QJSONTask::JSON_ANSWER_NONE);

    bool isGSMInited() const {return _gsm_inited;}
    void finished_socket_1();



signals:
    void writeToSocket(QByteArray);
    void WPSStarted(int time_sec);
    void WPSStopped();
    void setConnected(bool);
    void addrTextEdit(QString _answer);
    void finished_socket_entr();
    void setVarMenu(QStringList _strListMenu);
    void registerSuccessfully(bool regS);

private slots:
    void parseMessage(const QByteArray & data);
    //void logError(const QString & err);
private:
    virtual void process();
    void execTasks();
    void parseJSONAnswer(const QVariantMap & answer); //Расшифровка сообщения
    void parseJSON_Gui(const QVariantMap & answer);   //Расшифровка сообщения Gui, нужно будет добавить в общий парсер

    QThreadSocket socket;

    //задачи для менеджера, парсер ожидания текущего ответа и время таймаута
    QList<QJSONTask> _tasks; //Список текущих задачь
    QJSONTask current_task;  //Текущая задача - которая выполняетя в данный момент

    QMutex local_mutex;
    int _label = 1;
    bool _gsm_inited = false;

};

#endif // QSHMANAGERINFO_H