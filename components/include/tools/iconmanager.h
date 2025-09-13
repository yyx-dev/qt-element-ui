#pragma once

#include <QObject>
#include <QIcon>
#include <QMap>
#include <QColor>

#include <tuple>


namespace Element
{
    enum class Icon
    {
        None = -1,
        AddLocation = 0, Aim, AlarmClock, Apple, ArrowDown, ArrowDownBold, ArrowLeft, ArrowLeftBold, ArrowRight, ArrowRightBold, ArrowUp, ArrowUpBold, Avatar,
        Back, Baseball, Basketball, Bell, BellFilled, Bicycle, Bottom, BottomLeft, BottomRight, Bowl, Box, Briefcase, Brush, BrushFilled, Burger,
        Calendar, Camera, CameraFilled, CaretBottom, CaretLeft, CaretRight, CaretTop, Cellphone, ChatDotRound, ChatDotSquare, ChatLineRound, ChatLineSquare, ChatRound, ChatSquare, Check, Checked,
        Cherry, Chicken, ChromeFilled, CircleCheck, CircleCheckFilled, CircleClose, CircleCloseFilled, CirclePlus, CirclePlusFilled, Clock, Close, CloseBold,
        Cloudy, Coffee, CoffeeCup, Coin, ColdDrink, Collection, CollectionTag, Comment, Compass, Connection, Coordinate, CopyDocument, Cpu, CreditCard, Crop,
        DArrowLeft, DArrowRight, DataAnalysis, DataBoard, DataLine, DCaret, Delete, DeleteFilled, DeleteLocation, Dessert, Discount,
        Dish, DishDot, Document, DocumentAdd, DocumentChecked, DocumentCopy, DocumentDelete, DocumentRemove, Download, Drizzling,
        Edit, EditPen, Eleme, ElemeFilled, ElementPlus, Expand,
        Failed, Female, Files, Film, Filter, Finished, FirstAidKit, Flag, Fold, Folder, FolderAdd, FolderChecked, FolderDelete, FolderOpened, FolderRemove, Food, Football, ForkSpoon, Fries, FullScreen,
        Goblet, GobletFull, GobletSquare, GobletSquareFull, GoldMedal, Goods, GoodsFilled, Grape, Grid, Guide,
        Handbag, Headset, Help, HelpFilled, Hide, Histogram, HomeFilled, HotWater, House,
        IceCream, IceCreamRound, IceCreamSquare, IceDrink, IceTea, InfoFilled, Iphone,
        Key, KnifeFork,
        Lightning, Link, List, Loading, Location, LocationFilled, LocationInformation, Lock, Lollipop,
        MagicStick, Magnet, Male, Management, MapLocation, Medal, Memo, Menu, Message, MessageBox, Mic, Microphone, MilkTea,
        Minus, Money, Monitor, Moon, MoonNight, More, MoreFilled, MostlyCloudy, Mouse, Mug, Mute, MuteNotification,
        NoSmoking, Notebook, Notification,
        Odometer, OfficeBuilding, Open, Operation, Opportunity, Orange,
        Paperclip, PartlyCloudy, Pear, Phone, PhoneFilled, Picture, PictureFilled, PictureRounded, PieChart, Place, Platform, Plus, Pointer, Position, Postcard, Pouring, Present, PriceTag, Printer, Promotion,
        QuartzWatch, QuestionFilled,
        Rank, Reading, ReadingLamp, Refresh, RefreshLeft, RefreshRight, Refrigerator, Remove, RemoveFilled, Right,
        ScaleToOriginal, School, Scissor, Search, Select, Sell, SemiSelect, Service, Setting, SetUp, Share, Ship, Shop, ShoppingBag, ShoppingCart, ShoppingCartFull, ShoppingTrolley, Smoking,
        Soccer, SoldOut, Sort, SortDown, SortUp, Stamp, Star, StarFilled, Stopwatch, SuccessFilled, Sugar, Suitcase, SuitcaseLine, Sunny, Sunrise, Sunset, Switch, SwitchButton, SwitchFilled,
        TakeawayBox, Ticket, Tickets, Timer, ToiletPaper, Tools, Top, TopLeft, TopRight, TrendCharts, Trophy, TrophyBase, TurnOff,
        Umbrella, Unlock, Upload, UploadFilled, User, UserFilled,
        Van, VideoCamera, VideoCameraFilled, VideoPause, VideoPlay, View,
        Wallet, WalletFilled, Warning, WarningFilled, WarnTriangleFilled, Watch, Watermelon, WindPower,
        ZoomIn, ZoomOut,
    };

    class IconManager
    {
    public:
        static IconManager& instance();

        IconManager(const IconManager&) = delete;
        IconManager& operator=(const IconManager&) = delete;

        QIcon getIcon(Icon icon, const QString& color, int size);

    private:
        void preloadIcons();
        explicit IconManager();
        QIcon createSvgIcon(const QString &path, const QString &color, int size);

    private:
        // name,color,size => icon
        QMap<std::tuple<QString, QString, int>, QIcon> _iconCache;
        QStringList _iconList;
    };


}
