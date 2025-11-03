#pragma once

#include <QString>

namespace Element
{

    struct Color
    {
        /* 主色 */

        // #409EFF
        static QString primary();
        // #337ECC
        static QString primaryD1();
        // #79BBFF
        static QString primaryL1();
        // #A0CFFF
        static QString primaryL2();
        // #C6E2FF
        static QString primaryL3();
        // #D9ECFF
        static QString primaryL4();
        // #ECF5FF
        static QString primaryL5();

        // #67C23A
        static QString success();
        // #529B2E
        static QString successD1();
        // #95D475
        static QString successL1();
        // #B3E19D
        static QString successL2();
        // #D1EDC4
        static QString successL3();
        // #E1F3D8
        static QString successL4();
        // #F0F9EB
        static QString successL5();

        // #E6A23C
        static QString warning();
        // #B88230
        static QString warningD1();
        // #EEBE77
        static QString warningL1();
        // #F3D19E
        static QString warningL2();
        // #F8E3C5
        static QString warningL3();
        // #FAECD8
        static QString warningL4();
        // #FDF6EC
        static QString warningL5();

        // #F56C6C
        static QString danger();
        // #C45656
        static QString dangerD1();
        // #F89898
        static QString dangerL1();
        // #FAB6B6
        static QString dangerL2();
        // #FCD3D3
        static QString dangerL3();
        // #FDE2E2
        static QString dangerL4();
        // #FEF0F0
        static QString dangerL5();

        // #909399
        static QString info();
        // #73767A
        static QString infoD1();
        // #B1B3B8
        static QString infoL1();
        // #C8C9CC
        static QString infoL2();
        // #DEDFE0
        static QString infoL3();
        // #E9E9EB
        static QString infoL4();
        // #F4F4F5
        static QString infoL5();

        /* 文本 */

        // #303133
        static QString primaryText();
        // #606266
        static QString regularText();
        // #909399
        static QString secondaryText();
        // #A8ABB2
        static QString placeholderText();
        // #C0C4CC
        static QString disabledText();

        /* 边框 */

        // #CDD0D6
        static QString darkerBorder();
        // #D4D7DE
        static QString darkBorder();
        // #DCDFE6
        static QString baseBorder();
        // #E4E7ED
        static QString lightBorder();
        // #EBEEF5
        static QString lighterBorder();
        // #F2F6FC
        static QString extraLightBorder();

        /* 填充 */

        // #E6E8EB
        static QString darkerFill();
        // #EBEDF0
        static QString darkFill();
        // #F0F2F5
        static QString baseFill();
        // #F5F7FA
        static QString lightFill();
        // #FAFAFA
        static QString lighterFill();
        // #FAFCFF
        static QString extraLightFill();
        // #FFFFFF
        static QString blankFill();

        /* 背景 */

        // #000000
        static QString basicBlack();
        // #FFFFFF
        static QString basicWhite();
        // #F2F3F5
        static QString pageBackground();
        // #FFFFFF
        static QString baseBackground();
        // #FFFFFF
        static QString overlayBackground();
    };

}