#!/bin/bash

# 用法：
# pwd: XqqytDesktop
# bash Scripts/package/generate_release_deb.sh build/XqqytDesktop ~/temp /opt/Qt5.14.2/5.14.2/gcc_64

EXECUTABLE="$1"
PACKAGE_DIR="$2"
QT_GCC_PATH="$3"

if [[ -z "$EXECUTABLE" || -z "$PACKAGE_DIR" || -z "$QT_GCC_PATH" ]]; then
    echo "Usage: $0 <executable_path> <temp_output_path> <qt_gcc_path>"
    exit 1
fi

# 从 settings-example.json 文件中提取版本号
VERSION=$(jq -r '.Meta.version' settings-example.json)

if [[ -z "$VERSION" ]]; then
    echo "版本号未找到，请检查 settings-example.json 文件"
    exit 1
fi

# 设置包的名称
PACKAGE_NAME="XqqytDesktop_${VERSION}_amd64.deb"
DEB_TEMPLATE="DebTemplete"
DEB_DIR="$PACKAGE_DIR/XqqytDesktop_${VERSION}_tmp"
DEB_TEMPLATE_DIR="$DEB_DIR/$DEB_TEMPLATE"

# 创建目标包目录
rm -rf "$DEB_DIR"  # 清除已存在的目标目录
mkdir -p "$DEB_DIR"

# 复制Deb模板
cp -r "$DEB_TEMPLATE" "$DEB_DIR"

rm -rf "$DEB_TEMPLATE_DIR/.git"
rm -f "$DEB_TEMPLATE_DIR/.gitignore"

VERSION=$(echo "$VERSION" | sed 's/^v//')
# 更新版本号到 control 文件
sed -i "s/Version: .*/Version: $VERSION/" "$DEB_TEMPLATE_DIR/DEBIAN/control"

# 拷贝依赖的 Qt 库到 lib 文件夹
LIB_DIR="$DEB_TEMPLATE_DIR/opt/XqqytDesktop/lib"
mkdir -p "$LIB_DIR"

echo "🔍 Collecting shared library dependencies for $EXECUTABLE..."

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

cp "$QT_GCC_PATH/lib/libQt5XcbQpa.so.5" "$LIB_DIR/"
cp "$QT_GCC_PATH/lib/libQt5DBus.so.5" "$LIB_DIR/"

# 拷贝 Qt 插件目录
for plugin_dir in platforms xcbglintegrations; do
    SRC="$QT_GCC_PATH/plugins/$plugin_dir"
    DEST="$DEB_TEMPLATE_DIR/opt/XqqytDesktop/$plugin_dir"
    if [[ -d "$SRC" ]]; then
        echo "Copying $plugin_dir -> $DEST"
        mkdir -p "$DEST"
        cp -ru "$SRC/"* "$DEST/"
    else
        echo "Plugin directory not found: $SRC"
    fi
done

patch_rpath "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/platforms/libqxcb.so" '$ORIGIN/../lib'

# 拷贝 Theme 文件夹
if [[ -d "Theme" ]]; then
    echo "Copying Theme folder..."
    cp -r "Theme" "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/"
else
    echo "Theme directory not found: ../../Theme"
fi

# 拷贝 Scripts/utils 目录
if [[ -d "Scripts/utils" ]]; then
    echo "Copying Scripts/utils folder..."
    mkdir -p "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/Scripts"
    cp -r "Scripts/utils" "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/Scripts/"
else
    echo "Scripts/utils directory not found!"
fi

# 拷贝 Translations 文件夹
if [[ -d "Translations" ]]; then
    echo "Copying Translations folder..."
    cp -r "Translations" "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/Translations"
else
    echo "Translations directory not found: Translations"
fi

# 拷贝设置文件
cp "settings-example.json" "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/settings.json"

# 拷贝构建好的可执行文件
cp "build/XqqytDesktop" "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/XqqytDesktop"

cp "Resources/pic/logo.png" "$DEB_TEMPLATE_DIR/opt/XqqytDesktop/logo.png"

# 打包为deb文件
dpkg-deb --build "$DEB_TEMPLATE_DIR" "$PACKAGE_NAME"

echo "Done. DEB package created: $PACKAGE_NAME"
