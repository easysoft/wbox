#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QAction>
#include <QScreen>

#include "traymanager.h"
#include "base/gscale.h"
#include "base/glang.h"
#include "controls/globalcontrol.h"
#include "controls/servicecontainer.h"
#include "controls/logcontainer.h"
#include "controls/apachesetting.h"
#include "base/inforesult.h"
#include "base/zpopupbutton.h"
#include "base/zoffsetmenu.h"
#include "base/zpopupmenu.h"

#include "services/quickonservice.h"
#include "httprequest/zhttprequest.h"

#include <QCheckBox>
#include <QTimer>

#include <string>
#include <memory>

class Controller;

class MainWindow : public QMainWindow,GScale,GLang
{
    Q_OBJECT

    enum
    {
        ST_REQDOMAIN = 0,
        ST_CHECKHARDWARE,
        ST_CHECKSERVICE,
        ST_STARTSERVICE,
        ST_DONE,
    };

public:
    MainWindow(Controller *ctr, QWidget *parent = nullptr);
    ~MainWindow();

    void appendMsg(MsgResult msg);
    void onAppStateChanged();
    void onServiceStateChanged(QString typeAndState);
    std::string OnHttpPostData(std::shared_ptr<std::string> url, std::shared_ptr<std::string> data);

private:
    TrayManager *m_trayMgr;
    Controller *m_ctr;

    bool m_showLog;
    QString m_themeName;
    QString m_langName;
    QPixmap m_bgPixmap;

    QLabel *m_lblLogo;
    QLabel *m_lblFootor;
    QWidget *m_leftWidget; 
    QPushButton *m_btnSwitch;

    GlobalControl *m_globalControl;
    ServiceContainer *m_serviceContainer;
    LogContainer *m_logContainer;
//    ApacheSetting *m_apacheSetting;

    QVBoxLayout *m_leftLayout;

    ZPopupMenu *m_menuWidget;
    QLabel *m_menuIcon;

    ZPopupButton* m_StartSvrBtn;
    ZPopupButton* m_StopSvrBtn;
    ZPopupButton* m_InstallSvrBtn;
    ZPopupButton* m_UninstallSvrBtn;
    ZPopupButton* m_ReisntallSvrBtn;
    
    QVBoxLayout m_QuickOnLayer;
    QWidget m_QuickOnWidget;
    // NO.1，启动渠成软件百宝箱
    QPushButton m_btnStartQuickOn;

    // NO.2, 设置域名
    QWidget m_SettingWidget;
    QVBoxLayout m_SettingLayout;
    QLabel m_SettingTitle;

    QHBoxLayout m_DomainLayer;
    QLineEdit m_Domain0;
    QLabel m_Dot;
    QComboBox m_Domain1;

//    QCheckBox m_CustomizeDomain;

    QLabel m_ValidDomain;
    QPushButton m_SettingSave;

    // NO.3, 当前状态显示
    QLabel m_CurrentStatus;
    QPushButton m_RetryButton;

    // NO.4，成功启动界面
    QWidget m_StartWidget;
    QVBoxLayout m_StartLayer;

    QHBoxLayout m_StartButtonsLayer;
    QPushButton m_StopQuickOn;
    QPushButton m_VisitQuickOnPage;

    QHBoxLayout m_UserLayer;
    QLabel m_Usr;
    QLineEdit m_UsrName;
    QLabel m_Pass;
    QLineEdit m_UsrPass;
    bool m_ConfigQuickOnFailed;
    int m_LastStat;

    QTimer m_InitMoveTimer;

    ZHttpRequest m_HttpReq;
    std::string m_Domain;
    int m_HttpPort, m_HttpsPort;

    int m_desireHeight = 570;
    int desireWidth(int realWidth, int realHeight);

    void hideLog();
    void showLog();

    void setLogWin();
    void setNologWin();

    void loadLang();
    void changeLang(QString langName);

    void loadTheme();
    void changeTheme(QString themeName);

    void adjustAfterLang();
    void adjustAfterLangImpl();

    void createLogo();
    void createLeftUI();
    void createSetingMenu(QPushButton *btn);
    void createMainUI();
    void createRightUI();
    void createFooter();

    void makeEnvironmentPath();
    void makeBasicsInfo();

    bool m_Drag;
    QPoint m_DragPosition;
    QPoint m_preDragPos;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QScreen* getScreen();
    QuickOnService* GetQuickOnService();
    void SignUrl();
    void CheckHardWare();
    void InstallQuickOnService();
    void StartQuickOnService();
protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);

signals:
    void togglelog();
    void SetupQuickOnInitStatus();
    void StartQuickOnButtonsClicked();
    void SetupQuickOnSettingStatus();
    void SetupQuickOnCurrentStatus(int stat);
    void SetupQuickOnStartStatus();
    void SaveQuickOnConfig();
    void RetryConfig();
    void StopQuickOn();
    void VisitQuickOn();
    
private slots:
    void toggleLog();
    void closeApp();
    void onLangChanged();
    void onThemeChanged();

    void onClickViewService();
    void onClickUninstall();
    void onClickBackup();
    void onClickViewHelp();
    void onClickUpdateHelp();

    void OneClickSetup();
    void oneClickStart();
    void onClickInstall();
    void oneClickStop();
    void onClickReisntall();

    void clickVisit();

    void showMenu();

    void resized();

    void OnNotifyQuickOnInfo(const std::shared_ptr<std::string> domain, int http_port, int https_port);

    void OnSetupQuickOnInitStatus();
    void OnSetupQuickOnSettingStatus();
    void OnSetupQuickOnCurrentStatus(int stat);
    void OnSetupQuickOnStartStatus();
    void OnButtonStartQuickOn();
    void OnCustomizeDomain(int state);
    void OnInitMoveWindow();
    void OnSaveQuickOnConfig();
    void OnRetryConfig();
};

#endif // MAINWINDOW_H
