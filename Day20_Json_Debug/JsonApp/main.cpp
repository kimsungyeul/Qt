#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

void sendRequest();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sendRequest();
    return a.exec();
}

void sendRequest()
{
    // 스택 위의 임시 이벤트 루프(event loop)
    QEventLoop eventLoop;

    // "finished()"가 불려지면 이벤트 루프를 종료("quit()")
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)),
                     &eventLoop, SLOT(quit()));

    // HTTP 요청
    QNetworkRequest req( QUrl( QString("https://jsonplaceholder.typicode.com/posts/1/comments") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec( );           // "finished( )" 가 호출 될때까지 블록

    if (reply->error( ) == QNetworkReply::NoError) {
        QString strReply = (QString)reply->readAll( );
        // Json 파싱
        qDebug( ) << "Response:" << strReply;

        QJsonDocument jsonResponse =
                QJsonDocument::fromJson(strReply.toUtf8( ));

        QJsonArray jsonArr = jsonResponse.array();
        for(int i = 0; i < jsonArr.size(); i++) {
            QJsonObject jsonObj = jsonArr.at(i).toObject();    //jsonResponse.object();
#if 0
            foreach(const QString& key, jsonObj.keys()) {
                QJsonValue value = jsonObj.value(key);
                qDebug() << "Key = " << key << ", Value = " << value.toString();
            }
#else
            qDebug( ) << "ID:" << jsonObj["id"].toInt();
            qDebug( ) << "EMail:" << jsonObj["email"].toString( );
            qDebug( ) << "Name:" << jsonObj["name"].toString( );
            qDebug( ) << "Body:" << jsonObj["body"].toString( );
#endif
        }
        delete reply;
    }
}
