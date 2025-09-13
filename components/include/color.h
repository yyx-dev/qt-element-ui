/*
 *
 * https://element-plus.org/zh-CN/component/color.html
 *
 * */

#pragma once

#include <QString>

namespace Element
{

    class Color
    {
    public:
        // 主色
        static QString primary()   { return "#409EFF"; }
        static QString primaryD1() { return "#337ECC"; }
        static QString primaryL1() { return "#79BBFF"; }
        static QString primaryL2() { return "#A0CFFF"; }
        static QString primaryL3() { return "#C6E2FF"; }
        static QString primaryL4() { return "#D9ECFF"; }
        static QString primaryL5() { return "#ECF5FF"; }

        static QString success()   { return "#67C23A"; }
        static QString successD1() { return "#529B2E"; }
        static QString successL1() { return "#95D475"; }
        static QString successL2() { return "#B3E19D"; }
        static QString successL3() { return "#D1EDC4"; }
        static QString successL4() { return "#E1F3D8"; }
        static QString successL5() { return "#F0F9EB"; }


        static QString warning()   { return "#E6A23C"; }
        static QString warningD1() { return "#B88230"; }
        static QString warningL1() { return "#EEBE77"; }
        static QString warningL2() { return "#F3D19E"; }
        static QString warningL3() { return "#F8E3C5"; }
        static QString warningL4() { return "#FAECD8"; }
        static QString warningL5() { return "#FDF6EC"; }

        static QString danger()    { return "#F56C6C"; }
        static QString dangerD1()  { return "#C45656"; }
        static QString dangerL1()  { return "#F89898"; }
        static QString dangerL2()  { return "#FAB6B6"; }
        static QString dangerL3()  { return "#FCD3D3"; }
        static QString dangerL4()  { return "#FDE2E2"; }
        static QString dangerL5()  { return "#FEF0F0"; }

        static QString info()      { return "#909399"; }
        static QString infoD1()    { return "#73767A"; }
        static QString infoL1()    { return "#B1B3B8"; }
        static QString infoL2()    { return "#C8C9CC"; }
        static QString infoL3()    { return "#DEDFE0"; }
        static QString infoL4()    { return "#E9E9EB"; }
        static QString infoL5()    { return "#F4F4F5"; }

        //文本
        static QString primaryText()     { return "#303133"; }
        static QString regularText()     { return "#606266"; }
        static QString secondaryText()   { return "#909399"; }
        static QString placeholderText() { return "#A8ABB2"; }
        static QString disabledText()    { return "#C0C4CC"; }

        //边框
        static QString darkerBorder()     { return "#CDD0D6"; }
        static QString darkBorder()       { return "#D4D7DE"; }
        static QString baseBorder()       { return "#DCDFE6"; }
        static QString lightBorder()      { return "#E4E7ED"; }
        static QString lighterBorder()    { return "#EBEEF5"; }
        static QString extraLightBorder() { return "#F2F6FC"; }

        //填充
        static QString darkerFill()     { return "#E6E8EB"; }
        static QString darkFill()       { return "#EBEDF0"; }
        static QString baseFill()       { return "#F0F2F5"; }
        static QString lightFill()      { return "#F5F7FA"; }
        static QString lighterFill()    { return "#FAFAFA"; }
        static QString extraLightFill() { return "#FAFCFF"; }
        static QString blankFill()      { return "#FFFFFF"; }

        //背景
        static QString basicBlack()        { return "#000000"; }
        static QString basicWhite()        { return "#FFFFFF"; }
        static QString pageBackground()    { return "#F2F3F5"; }
        static QString baseBackground()    { return "#FFFFFF"; }
        static QString overlayBackground() { return "#FFFFFF"; }
    };

}
