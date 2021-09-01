#include "ItemDelegate.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QEvent>
#include <QDebug>
#include "Student.h"

ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

ItemDelegate::~ItemDelegate()
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    if(index.isValid())
    {
        painter->save();

        GroupNumber status = (GroupNumber)(index.data(Qt::UserRole).toInt());

        QVariant variant = index.data(Qt::UserRole+1);
        Student data = variant.value<Student>();

        QStyleOptionViewItem viewOption(option);//用来在视图中画一个item

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        //QPainterPath画圆角矩形
        const qreal radius = 7;
        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));

        if(option.state.testFlag(QStyle::State_Selected))
        {
            painter->setPen(QPen(Qt::blue));
            painter->setBrush(QColor(229, 241, 255));
            painter->drawPath(path);
        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setPen(QPen(Qt::green));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }
        else{
            painter->setPen(QPen(Qt::gray));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

        //绘制数据位置
        QRect NameRect = QRect(rect.left() +10, rect.top()+10, rect.width()-30, 25);
        QRect circle = QRect(NameRect.right(), rect.top()+10, 20, 20);
        QRect telRect = QRect(rect.left() +10, rect.bottom()-25, rect.width()-10, 25);


        switch (status) {
        case 0:
            painter->setBrush(Qt::white);
            painter->setPen(QPen(Qt::white));
            break;
        case 1:
            painter->setBrush(Qt::black);
            painter->setPen(QPen(Qt::black));
            break;
        case 2:
            painter->setBrush(Qt::red);
            painter->setPen(QPen(Qt::red));
            break;
        case 3:
            painter->setBrush(Qt::green);
            painter->setPen(QPen(Qt::green));
            break;
        case 4:
            painter->setBrush(Qt::blue);
            painter->setPen(QPen(Qt::blue));
            break;
        case 5:
            painter->setBrush(Qt::gray);
            painter->setPen(QPen(Qt::gray));
            break;
        case 6:
            painter->setBrush(Qt::darkGray);
            painter->setPen(QPen(Qt::darkGray));
            break;
        case 7:
            painter->setBrush(Qt::lightGray);
            painter->setPen(QPen(Qt::lightGray));
            break;
        case 8:
            painter->setBrush(Qt::cyan);
            painter->setPen(QPen(Qt::cyan));
            break;
        case 9:
            painter->setBrush(Qt::magenta);
            painter->setPen(QPen(Qt::magenta));
            break;
        case 10:
            painter->setBrush(Qt::yellow);
            painter->setPen(QPen(Qt::yellow));
            break;
        case 11:
            painter->setBrush(Qt::darkRed);
            painter->setPen(QPen(Qt::darkRed));
            break;
        case 12:
            painter->setBrush(Qt::darkGreen);
            painter->setPen(QPen(Qt::darkGreen));
            break;
        case 13:
            painter->setBrush(Qt::darkBlue);
            painter->setPen(QPen(Qt::darkBlue));
            break;
        case 14:
            painter->setBrush(Qt::darkCyan);
            painter->setPen(QPen(Qt::darkCyan));
            break;
        case 15:
            painter->setBrush(Qt::darkMagenta);
            painter->setPen(QPen(Qt::darkMagenta));
            break;
        }

//        painter->drawEllipse(circle);     //画圆圈

        painter->setFont(QFont("Times", 18, QFont::Bold));
        painter->drawText(circle, Qt::AlignCenter, QChar(data.groupBelongsTo + 'A' - 1));

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Times", 16, QFont::Bold));
        painter->drawText(NameRect,Qt::AlignLeft,data.name); //绘制名字

        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Times", 12));
        painter->drawText(telRect,Qt::AlignLeft,data.code); //绘制电话

        painter->restore();
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(160, 60);
}
