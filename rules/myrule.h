#ifndef MYRULE_H
#define MYRULE_H

#include <QtMath>
#include <QPointF>
#include <QPainterPath>
#include <QList>
#include <QMap>
#include <QStringList>

struct Line{
    QPointF pLU;  // 左上端点
    QPointF pRD;  // 右上端点
};

/**
 * @brief 制板规则类
 */
class MyRule
{
private:
    QStringList types; /**< 实体类型表 */
    QString file;     /**< 规则文件路径 */

public:
    MyRule(QString file);
    ~MyRule();

    // 基本约束方法:
    // 求偏移 位置参考点，距离参数，方向向量
    QPointF offset(QPointF p1, qreal distance, QPointF direction);
    // 定长延长 方向参考线，长度参数，定长线段
    QPointF extend(Line l1, qreal length, Line lFixLength);
    // 求垂足 垂线上的点，直线
    QPointF foot(QPointF p1, Line l1);
    // 等分点	 线段上参考端点，线段另一端点，比例
    QPointF divide(QPointF p1, QPointF p2, qreal proprtion);
    // 求交点 直线，另一斜率不同的直线
    QPointF cross(Line l1, Line l2);
    // 连接 线段的端点，线段另一端点
    Line line(QPointF p1, QPointF p2);

    // 所有实体的表：
    QMap<QString,QString> params;        /**< 参数型实体 */
    QMap<QString,QPointF> points;        /**< 点类型实体 */
    QMap<QString,Line> lines;            /**< 直线型实体 */
    QMap<QString,QList<QPointF>> curves; /**< 曲线型实体 */

    // 规则代码解析：
    void parseCode(QString code);
    QStringList getEntityNames(QString code);
    QString getEntityType(QString code);
    void defineEntity(QString code);
    void assignEntity(QString code);
    QString getTypeOf(QString name);

    // 使用自定义规则：
    QString callRule(QString file,QString input);

    // 生成绘图路径：
    QPainterPath drawPath();
};

#endif // MYRULE_H
