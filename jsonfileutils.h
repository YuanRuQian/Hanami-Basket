#ifndef JSONFILEUTILS_H
#define JSONFILEUTILS_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "user.h"

class JsonFileUtils
{
public:
    static error_t writeObject(QString path, QJsonObject obj);
    static error_t writeArray(QString path, QJsonArray arr);
    static QJsonDocument readFile(QString path);
    static void removeFile(QString path);
};

#endif // JSONFILEUTILS_H
