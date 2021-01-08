#include "abritesapp.h"

PolygonObjects::PolygonObjects(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void PolygonObjects::paint(QPainter *painter)
{
    QBrush brush(QColor("green"));
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < objects.length(); i++)
    {
        painter->drawPolygon(objects.at(i));
    }
}

AbritesApp::AbritesApp() {}

Q_INVOKABLE int AbritesApp::getVisibleObjects(int angle)
{
    int visibleCount = 0;
    QRect visibleArea;

    //  ¯\_(ツ)_/¯
    // tried already too many things

    //    visibleArea.setWidth(std::numeric_limits<uint>::max());
    //    visibleArea.setHeight(std::numeric_limits<uint>::max());
    visibleArea.setWidth(_roomSize.width());
    visibleArea.setHeight(_observerLocation.y());
    //    visibleArea.setX(0);
    //    visibleArea.setY(0);
    visibleArea.setLeft(0);
    visibleArea.setTop(0);
    visibleArea.setRight(visibleArea.right());
    visibleArea.setBottom(_observerLocation.y());

    //    QTransform t = QTransform();
    //    t.rotate(angle / 2, Qt::XAxis);
    //    t.rotate(angle / 2 , Qt::YAxis);
    //    t.rotate(angle, Qt::XAxis);
    //    t.rotate(angle, Qt::YAxis);

    //    t.translate(visibleArea.topLeft().x(), visibleArea.bottomRight().y());
    //    t.translate(-visibleArea.left(), -visibleArea.bottom());
    //    t.translate(_observerLocation.x(), _observerLocation.y());

    //    QRect transformed = t.mapRect(visibleArea);
    //    visibleArea = transformed;

    qCritical() << "Rotated rect is" << visibleArea;
    std::function<bool(const QPolygon&)> isVisible = [=] (const QPolygon& pointsV)
    {
        for (int i = 0; i < pointsV.length(); ++i)
        {
            const QPoint& _point = pointsV.at(i);
            if (visibleArea.contains(_point))
                return true;
        }

        return false;
    };

    for (int i = 0; i < objects.length(); ++i)
    {
        if (isVisible(objects.at(i)))
        {
            visibleCount++;
        }
    }

    _visibleArea = visibleArea;
    Q_EMIT visibleAreaChanged();

    return visibleCount;
}

// Possible setter functions
// direct MEMBER reading is used instead, see header

//void AbritesApp::setRoomSize(const QSize& roomSize)
//{
//   if (_roomSize != roomSize)
//   {
//       _roomSize = roomSize;
//       Q_EMIT => a change signal (not written in these examples)
//   }
//}

//const QPoint& AbritesApp::setObserverLocation(QPoint& observerLocation)
//{
//   if (_observerLocation != _observerLocation)
//   {
//       _observerLocation = observerLocation;
//       Q_EMIT => a change signal (not written in these examples)
//   }
//}


// Possible getter functions
//const QSize& AbritesApp::getRoomSize()
//{
//    return _roomSize;
//}

//const QPoint& AbritesApp::getObserverLocation()
//{
//    return _observerLocation;
//}
