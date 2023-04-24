#include "jsonfileutils.h"

#include <QFile>

/**
 * @brief Write a QJsonObject to a specified path.
 * @param path -- the path to be written in
 * @param obj -- the QJsonObject to be written
 */
error_t JsonFileUtils::writeObject(QString path, QJsonObject obj) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream in(&file);
        QJsonDocument doc(obj);
        in << doc.toJson();
        file.close();
        return success;
    } else {
        qDebug() << "can't open the file!";
        return open_file_failure;
    }
}

/**
 * @brief Write a QJsonArray to a specified path.
 * @param path -- the path to be written in
 * @param obj -- the QJsonArray to be written
 */
error_t JsonFileUtils::writeArray(QString path, QJsonArray arr) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream in(&file);
        QJsonDocument doc(arr);
        in << doc.toJson();
        file.close();
        return success;
    } else {
        qDebug() << "can't open the file!";
        return open_file_failure;
    }
}

/**
 * @brief Read a Json file and store it in a QJsonDocument
 * @param path -- the file path to read
 * @return the QJsonDocument of the file
 */
QJsonDocument JsonFileUtils::readFile(QString path) {
    QFile file(path);
    if (!file.exists()) {
        return QJsonDocument();
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open the file: " << path;
    }
    QTextStream stream(&file);
    QString str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    return doc;
}

/**
 * @brief Remove a file.
 * @param path -- the specified path of the file
 */
void JsonFileUtils::removeFile(QString path) {
    QFile file(path);
    file.remove();
}
