#pragma once
#include <QObject>
#include <QRect>
#include <QPolygon>
#include <QQuickPaintedItem>
#include <QPainter>

inline QList<QPolygon> objects;

class PolygonObjects : public QQuickPaintedItem
{
    Q_OBJECT

    public:
        PolygonObjects(QQuickItem *parent = 0);
        void paint(QPainter *painter);

};

class AbritesApp : public QObject
{
    Q_OBJECT
public:
    AbritesApp();
    /*********************************************************************
     * Changing the values after initial read from file is not expected
     * and also not reachable via UI.
     *
     * Omitting get/set functions
     ********************************************************************/

    Q_PROPERTY(QSize roomSize MEMBER _roomSize CONSTANT)
    Q_PROPERTY(QPoint observerLocation MEMBER _observerLocation CONSTANT)
    Q_PROPERTY(QRect visibleArea MEMBER _visibleArea NOTIFY visibleAreaChanged)

    Q_INVOKABLE int getVisibleObjects(int angle);
    Q_SIGNAL void visibleAreaChanged();

    QSize _roomSize;
    QPoint _observerLocation;
    QRect _visibleArea;

};
