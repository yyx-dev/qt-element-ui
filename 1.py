import os
import re

# 1. 配置需要转换的事件列表
# 格式: { '旧参数类型': '新参数类型', '事件函数名': 'event_name' }
EVENT_MAP = {
    'enterEvent': 'QEnterEvent',
    'leaveEvent': 'QEvent', # Qt6 中 leaveEvent 其实没变参数类型，但有些环境会报错，这里预留
}

def replace_qt_events(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    original_content = content

    # --- 模式 A: 处理 .cpp 中的实现 (void Class::enterEvent(QEvent* e)) ---
    # 匹配: void 类名::enterEvent ( QEvent * 变量名 )
    cpp_pattern = r'(void)\s+([\w:]+)?(enterEvent)\s*\(\s*QEvent\s*\*\s*(\w+)\)'
    
    def cpp_replacer(match):
        ret_type = match.group(1)   # void
        class_name = match.group(2) if match.group(2) else "" # _BackButton::
        func_name = match.group(3)  # enterEvent
        var_name = match.group(4)   # event
        new_type = EVENT_MAP[func_name]
        
        return (f"#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)\n"
                f"void {class_name}{func_name}({new_type}* {var_name})\n"
                f"#else\n"
                f"void {class_name}{func_name}(QEvent* {var_name})\n"
                f"#endif")

    # --- 模式 B: 处理 .h 中的声明 (void enterEvent(QEvent* e) override;) ---
    # 匹配: void enterEvent ( QEvent * 变量名 ) override;
    h_pattern = r'(void)\s+(enterEvent)\s*\(\s*QEvent\s*\*\s*(\w+)\)(\s+override)?;?'

    def h_replacer(match):
        ret_type = match.group(1)
        func_name = match.group(2)
        var_name = match.group(3)
        override = match.group(4) if match.group(4) else ""
        new_type = EVENT_MAP[func_name]
        
        return (f"#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)\n"
                f"    {ret_type} {func_name}({new_type}* {var_name}){override};\n"
                f"#else\n"
                f"    {ret_type} {func_name}(QEvent* {var_name}){override};\n"
                f"#endif")

    # 执行替换
    if file_path.endswith('.cpp'):
        content = re.sub(cpp_pattern, cpp_replacer, content)
    elif file_path.endswith('.h'):
        content = re.sub(h_pattern, h_replacer, content)

    # 保存文件
    if content != original_content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"已处理: {file_path}")

def main(root_dirs):
    for target_dir in root_dirs:
        if not os.path.exists(target_dir):
            print(f"路径不存在，跳过: {target_dir}")
            continue
        for root, _, files in os.walk(target_dir):
            for file in files:
                if file.endswith(('.h', '.cpp')):
                    replace_qt_events(os.path.join(root, file))

if __name__ == "__main__":
    # 根据你的项目结构，处理这四个文件夹
    target_folders = ["./components", "./example", "./gallery"]
    
    print("开始批量转换 Qt5/Qt6 事件签名...")
    main(target_folders)
    print("转换完成！请检查代码并编译。")