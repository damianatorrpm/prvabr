#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include "abritesapp.h"

/******************************************
 *
 *
 *
 * Note that no memory optizimation has
 * been done. Memory leaks are expected.
 *
 * Error handling or use of unexpected
 * values inside config file incomplete.
 *
 * Acceptable according to task description:
 *
 * "Входът е от текстови файл и се предполага, че ще е коректен."
 * "The input is from a text file and is assumed to be correct."
 *
 *
 *
 ******************************************/

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QStringList argSl = QCoreApplication::arguments();
    int lineNumber = 0;

    if (argSl.length() != 2)
    {
        qCritical() << "Invalid number of arguments.";
        qCritical() << "Please specify a path to the input file.";
        exit(-1);
    }

    const QString& filePath = argSl.at(1);
    if (!QFile::exists(filePath))
    {
        qCritical() << "File at path doesn't exist.";
        exit(-1);
    }

    AbritesApp* _abrites = new AbritesApp();
    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("AbritesApp", 1, 0, "AbritesApp", _abrites);
    qmlRegisterType<PolygonObjects>("PolygonObjects", 1, 0, "PolygonObjects");

    int maxPolygonCount;
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            const QString& line = in.readLine();
            qCritical() << line << lineNumber;

            if (lineNumber == 0)
            {
                const QStringList& _roomSizeSl = line.split(" ");
                _abrites->_roomSize = QSize(_roomSizeSl.first().toInt(), _roomSizeSl.back().toInt());
            }

            else if (lineNumber == 1)
            {
                const QStringList& _observerLocationSl = line.split(" ");
                _abrites->_observerLocation = QPoint(_observerLocationSl.first().toInt(), _observerLocationSl.back().toInt());
            }
            else if (lineNumber == 2)
            {
                maxPolygonCount = line.toInt();
            }
            else
            {
                if (lineNumber > maxPolygonCount + 2)
                {
                    qCritical() << "Invalid Polygon count.";
                    exit(-1);
                }
                QPolygon polygon;
                const QStringList& _points = line.split(" ");
                qCritical() << "Polygon at line" << lineNumber << "has" << _points.length() << "points";

                for (int i = 0; i < _points.length(); i++)
                {
                    const QString& _pointStr = _points.at(i);
                    qCritical() << "Polygon at line" << lineNumber << "point has point" << _pointStr;
                    const QStringList& _pointSl = _pointStr.split(",");
                    polygon << QPoint(_pointSl.first().toInt(), _pointSl.back().toInt());
                }
                objects.append(polygon);
                qCritical() << "Added Polygon" << objects.length();

            }
            lineNumber++;
        }
        if (lineNumber < 3)
        {
            qCritical() << "Invalid Polygon count (maybe 0).";
            exit(-1);
        }
        inputFile.close();
    }
    qCritical() << "Room Size:" << _abrites->_roomSize;
    qCritical() << "Observor Location:" << _abrites->_observerLocation;
    qCritical() << "Object count:" << objects.length();



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
