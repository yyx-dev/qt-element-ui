#include "tools/qsshelper.h"

#include <QRegularExpression>

namespace Element
{


    QSSHelper::QSSHelper(const QString& qss)
    {
        if (!qss.isEmpty())
            parse(qss);
    }

    QSSHelper& QSSHelper::operator=(const QString& qss)
    {
        if (!qss.isEmpty())
            parse(qss);

        return *this;
    }

    void QSSHelper::parse(const QString &qss)
    {
        _styleGroups.clear();

        // 使用正则表达式匹配样式组
        QRegularExpression groupRegex(R"(([^{]+)\s*\{([^}]+)\})");
        QRegularExpressionMatchIterator it = groupRegex.globalMatch(qss);

        while (it.hasNext())
        {
            QRegularExpressionMatch match = it.next();
            QString groupName = match.captured(1).trimmed();
            QString groupContent = match.captured(2).trimmed();

            // 分割属性
            QStringList properties = groupContent.split(';', QString::SkipEmptyParts);
            QStringList trimmedProperties;

            for (QString prop : properties)
                trimmedProperties << prop.trimmed();

            _styleGroups[groupName] = trimmedProperties;
        }
    }

    // 获取所有样式组名称
    QStringList QSSHelper::getGroupNames() const
    {
        return _styleGroups.keys();
    }

    // 获取指定组的属性列表
    QStringList QSSHelper::getProperties(const QString &groupName) const
    {
        return _styleGroups.value(groupName, QStringList());
    }

    // 向指定组添加属性
    QSSHelper& QSSHelper::setProperty(const QString &groupName, const QString &key, const QString &value)
    {
        // 如果组不存在，先创建空组
        if (!_styleGroups.contains(groupName)) {
            _styleGroups[groupName] = QStringList();
        }

        QStringList &properties = _styleGroups[groupName];
        QString newProperty = QString("%1: %2").arg(key).arg(value);

        // 检查是否已存在相同key的属性
        bool found = false;
        for (int i = 0; i < properties.size(); ++i) {
            if (properties[i].startsWith(key + ":")) {
                properties[i] = newProperty; // 覆盖现有属性
                found = true;
                break;
            }
        }

        if (!found) {
            properties << newProperty;
        }

        return *this;
    }

    // 从指定组移除属性
    QSSHelper& QSSHelper::removeProperty(const QString &groupName, const QString &property)
    {
        if (_styleGroups.contains(groupName))
        {
            QStringList &properties = _styleGroups[groupName];
            properties.removeAll(property);

            // 如果组为空，则移除整个组
            if (properties.isEmpty())
                _styleGroups.remove(groupName);
        }

        return *this;
    }

    // 清空指定组的所有属性并移除该组
     QSSHelper& QSSHelper::clearGroup(const QString &groupName)
    {
        _styleGroups.remove(groupName);
        return *this;
    }

    // 生成QSS字符串
    QString QSSHelper::generate() const
    {
        QString result;

        for (auto it = _styleGroups.constBegin(); it != _styleGroups.constEnd(); ++it)
        {
            const QString &groupName = it.key();
            const QStringList &properties = it.value();

            result += groupName + " {\n";
            for (const QString &prop : properties)
                result += "    " + prop + ";\n";

            result += "}\n\n";
        }

        return result.trimmed();
    }

}
