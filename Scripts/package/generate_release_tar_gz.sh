#!/bin/bash

# 用法：
# pwd: XqqytDesktop
# bash Scripts/package/generate_release_tar_gz.sh build/XqqytDesktop ~/release /opt/Qt5.14.2/5.14.2/gcc_64

EXECUTABLE="$1"
PACKAGE_DIR="$2"
QT_GCC_PATH="$3"

if [[ -z "$EXECUTABLE" || -z "$PACKAGE_DIR" || -z "$QT_GCC_PATH" ]]; then
    echo "Usage: $0 <executable_path> <output_path> <qt_gcc_path>"
    exit 1
fi

LIB_DIR="$PACKAGE_DIR/lib"
mkdir -p "$LIB_DIR"

echo "Collecting shared library dependencies for $EXECUTABLE..."

# 提取依赖库
ldd "$EXECUTABLE" | awk '{ print $3 }' | grep "^/" | while read -r lib; do
    if [[ -f "$lib" ]]; then
        echo "Copying: $lib"
        cp -u "$lib" "$LIB_DIR"
    fi
done

function patch_rpath {
    local target_file="$1"
    local rpath_value="$2"
    if [[ -f "$target_file" ]]; then
        echo "Patching RPATH of $target_file -> $rpath_value"
        patchelf --set-rpath "$rpath_value" "$target_file"
    else
        echo "Not found: $target_file"
    fi
}

# 拷贝必要的 Qt 库
cp "$QT_GCC_PATH/lib/libQt5XcbQpa.so.5" "$LIB_DIR/"
cp "$QT_GCC_PATH/lib/libQt5DBus.so.5" "$LIB_DIR/"

# 复制 Qt 插件目录（platforms 和 xcbglintegrations）
echo "Copying Qt plugins from $QT_GCC_PATH/plugins..."

for plugin_dir in platforms xcbglintegrations; do
    SRC="$QT_GCC_PATH/plugins/$plugin_dir"
    DEST="$PACKAGE_DIR/$plugin_dir"
    if [[ -d "$SRC" ]]; then
        echo "Copying $plugin_dir -> $DEST"
        mkdir -p "$DEST"
        cp -ru "$SRC/"* "$DEST/"
    else
        echo "Plugin directory not found: $SRC"
    fi
done

# 更新 rpath
patch_rpath "$PACKAGE_DIR/platforms/libqxcb.so" '$ORIGIN/../lib'

# 拷贝 Theme 文件夹
if [[ -d "Theme" ]]; then
    echo "Copying Theme folder..."
    cp -r "Theme" "$PACKAGE_DIR/Theme"
else
    echo "Theme directory not found: Theme"
fi

# 拷贝 Translations 文件夹
if [[ -d "Translations" ]]; then
    echo "Copying Translations folder..."
    cp -r "Translations" "$PACKAGE_DIR/Translations"
else
    echo "Translations directory not found: Translations"
fi

# 拷贝设置文件
cp "settings-example.json" "$PACKAGE_DIR/settings.json"
cp "devices-example.json" "$PACKAGE_DIR/devices.json"


cp "Resources/pic/logo.png" "$PACKAGE_DIR/logo.png"

# 拷贝构建好的可执行文件
cp "$EXECUTABLE" "$PACKAGE_DIR/XqqytDesktop"

echo "Files prepared in: $PACKAGE_DIR"

# 生成 tar.gz 压缩包
ARCHIVE_NAME="XqqytDesktop_$(date +%Y%m%d_%H%M%S).tar.gz"
ARCHIVE_DIR="$(dirname "$PACKAGE_DIR")"

echo "Creating archive: $ARCHIVE_NAME ..."
tar -czf "$ARCHIVE_DIR/$ARCHIVE_NAME" -C "$(dirname "$PACKAGE_DIR")" "$(basename "$PACKAGE_DIR")"

echo "Archive created at: $ARCHIVE_DIR/$ARCHIVE_NAME"
