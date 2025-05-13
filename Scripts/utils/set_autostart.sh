#!/bin/bash

# 检查输入参数
if [ $# -lt 2 ]; then
    echo "用法: $0 <enable|disable> <桌面应用文件名>"
    exit 1
fi

ACTION=$1
DESKTOP_FILE=$2
SOURCE_PATH="/usr/share/applications/$DESKTOP_FILE"
AUTOSTART_PATH="$HOME/.config/autostart/$DESKTOP_FILE"

# 检查文件是否存在
if [ ! -f "$SOURCE_PATH" ]; then
    echo "错误：找不到文件 $SOURCE_PATH"
    exit 1
fi

mkdir -p "$HOME/.config/autostart"

if [ "$ACTION" == "enable" ]; then
    # 设置开机自启
    cp "$SOURCE_PATH" "$AUTOSTART_PATH"
    echo "开机自启已设置：$AUTOSTART_PATH"
elif [ "$ACTION" == "disable" ]; then
    # 取消开机自启
    if [ -f "$AUTOSTART_PATH" ]; then
        rm "$AUTOSTART_PATH"
        echo "开机自启已取消：$AUTOSTART_PATH"
    else
        echo "错误：未找到开机自启文件 $AUTOSTART_PATH"
        exit 1
    fi
else
    echo "无效的操作！请传递 'enable' 或 'disable' 参数"
    exit 1
fi
