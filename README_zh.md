# XqqytDesktop

[点击此处查看项目文档](https://deepwiki.com/XQQYT/XqqytDesktop)

## 如何构建与运行

在构建之前，请确保已安装以下依赖项：

### 必需依赖项：
- **Qt 5**（用于 Qt 开发库）
- **CMake**（构建系统）

### 可选工具（用于开发便利）：
- **Qt Creator**（Qt 开发集成环境）
- **Qt Designer**（图形界面设计工具）

### 安装必需依赖项：

#### 设置 Qt 安装路径

如果你将 Qt 安装在自定义位置（例如不是系统默认路径），则需要在 `CMakeLists.txt` 文件中指定 Qt 的安装路径。

打开项目根目录下的 `CMakeLists.txt` 文件，编辑 `CMAKE_PREFIX_PATH` 变量，指向 Qt 的安装目录。例如：

```cmake
set(CMAKE_PREFIX_PATH "/path/to/your/Qt/installation")
```
将 /path/to/your/Qt/installation 替换为你实际的 Qt 安装路径，例如 /opt/Qt5.14.2/5.14.2/gcc_64。

这将确保 CMake 能找到你的 Qt 安装并在构建过程中使用它。

#### 安装可选工具（如有需要）：
```bash
sudo apt install qtcreator
sudo apt install qttools5-dev-tools
```

#### 构建并运行项目
如果尚未克隆仓库，请先执行：

```bash
git clone https://github.com/XQQYT/XqqytDesktop.git
cd XqqytDesktop
```

运行构建脚本：

```bash
bash build.sh
```

#### 运行应用程序：
##### 仅支持 X11 图形系统
XqqytDesktop 仅支持 X11 图形系统。

如果你当前使用的是 Wayland 或其他非 X11 的显示服务器，程序可能无法正常运行或直接启动失败。

如何切换至 X11（适用于 Ubuntu GNOME）：

1. 在登录界面点击你的用户名，但不要立即输入密码。

2. 点击右下角的齿轮图标。

3. 选择 “Ubuntu on Xorg” 或 “GNOME on X11”。

4. 然后输入密码登录。

现在你可以启动程序：

```bash
./XqqytDesktop
```
#### 附加说明：
如果你在构建过程中遇到依赖项或缺失包的问题，请确保系统包列表是最新的：

```bash
sudo apt update
```
## 许可证
本项目采用 MIT 许可证，详情请参见 [LICENSE](LICENSE) 文件。