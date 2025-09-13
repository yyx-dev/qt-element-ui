#pragma once

#include <QHash>
#include <QStringList>

namespace Element
{

    class QSSHelper
    {
    public:
        QSSHelper(const QString& qss = "");

        QSSHelper& operator=(const QString& qss);

        // 获取所有样式组名称
        QStringList getGroupNames() const;

        // 获取指定组的属性列表
        QStringList getProperties(const QString &groupName) const;

        // 向指定组添加属性
        QSSHelper& setProperty(const QString &groupName, const QString &key, const QString &value);

        // 从指定组移除属性
        QSSHelper& removeProperty(const QString &groupName, const QString &property);

        // 清空指定组的所有属性并移除该组
        QSSHelper& clearGroup(const QString &groupName);

        // 生成QSS字符串
        QString generate() const;

    private:
        void parse(const QString &qss);

    private:
        QHash<QString, QStringList> _styleGroups;
    };

}
