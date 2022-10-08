#ifndef ZHTTPREQUEST_H_
#define ZHTTPREQUEST_H_

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QString>
#include <QObject>
#include <QTimer>

#include <string>
#include <memory>

class ZHttpRequest : public QObject {
    Q_OBJECT
public:
    ZHttpRequest(QObject* parent, int interval = 15 * 1000);
    ~ZHttpRequest() {}

public:
    void SetTimeout(int interval);
    void SetUrl(const char* fmt, ...);
    void AddHeader(const char* key, const char* value);
    void SetPost(const char* fmt, ...);
    void SetTokenHeader();

    void SetToken(const char* token)
	{
        m_Token = token;
	}

    bool Exec(std::string& reply_str);
    bool UploadFormFile(std::string& reply_str, const QByteArray& pix_bytes);

private:
    QNetworkAccessManager* m_Manager;
    std::shared_ptr<QNetworkRequest> m_Request;

	QString m_Data;
	QTimer m_Timer;

    std::string m_Token;
};

#endif // ZHTTPREQUEST_H_
