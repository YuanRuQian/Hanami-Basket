#ifndef JSONFILEUTILS_H
#define JSONFILEUTILS_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class JsonFileUtils
{
public:
    static bool writeObject(QString path, QJsonObject obj);
    static bool writeArray(QString path, QJsonArray arr);
    static QJsonDocument readFile(QString path);
    static void removeFile(QString path);
};

#endif // JSONFILEUTILS_H
