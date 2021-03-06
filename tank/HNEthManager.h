#ifndef HNETHMANAGER_H
#define HNETHMANAGER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "qcomponent.h"
#include <qthread.h>
#include "qtankdefine.h"

class HNNetworkClearThread : public QThread
{
    Q_OBJECT
public:
    HNNetworkClearThread(QObject* parent = 0) : QThread(parent) {
    }
signals:
    void cleared();
    void notcleared();

    // QThread interface
protected:
    void run();
};

class HNDhcpThread : public QThread
{
    Q_OBJECT
public:
    HNDhcpThread(QObject* parent = 0) : QThread(parent) {
    }
    void setnet(QString eth = "eth0") {net=eth;}
signals:
    void passed(QString);
    // QThread interface
protected:
    void run();
private:
    QString net;
};

// thread unsafe
class HNEthManager : public QObject
{
    Q_OBJECT
public:
    static HNEthManager *Instance(QObject* parent = 0);

    QList<TWifi>& wifiList() { return m_wifiList; }
    inline TWifi currentWifi(){ return m_curWifi; }
    bool setCurrentWifi(QString bssid_mac, QString password = "");
    void setRefresh(bool ref = true) { ref ? m_workTimer->start(5000) : m_workTimer->stop(); }
    void setDHCP(bool bUse = false);
    bool dhcp();
    void configIPAddress(QString ip, QString mask, QString gw, QString dns);
    QString currentNetName();
    QTimer* workTimer() { return m_workTimer; }
    void saveAddr(QString ip, QString mask, QString gw, QString dns);
    void getAddr(QString& ip, QString& mask, QString& gw, QString& dns);

signals:
    //没有配置就会发送这个信号
    void sigScanning();
    //断开连接的状态
    void sigDisConnected();
    //正在连接的状态
    void sigConnecting();
    //连接成功的状态
    void sigConnected();
    //Wifi列表更新 之上状态改变会影响list中wifi的标志位。
    void sigRefreshed();
    //Wifi状态改变
    void sigStatusChanged(QString status);
    //有线连接上
    void sigLanConnected();
    //有线断开
    void sigLanDisConnected();
    //网络线路连接上
    void sigNetworkClear();
    //网络线路断开
    void sigNetworkNotClear();

private slots:
    void refreshWifiList();
    void refreshWifiStatus();
    void checkLanConnection();
    void DhcpPassed(QString netname);
    void checkNetworkClear();

private:
    explicit HNEthManager(QObject *parent = 0);
    void readStatus();
    void restoreWifi();
    bool restartWifi();
    void saveScript();
    void config();

signals:

public slots:
private:
    static HNEthManager* _instance;
    QTimer* m_workTimer;
    QList<TWifi> m_wifiList;
    TWifi m_curWifi;
    bool m_bUseDHCP;
    QString m_netName;
    HNDhcpThread* m_thread;
    HNNetworkClearThread* m_clearThread;
    QString m_status;
};

#endif // HNETHMANAGER_H
