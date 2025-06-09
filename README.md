# XqqytDesktop
- [User Server](https://github.com/XQQYT/Xqqyt_UserServer)
- [Signal Server](https://github.com/XQQYT/Xqqyt_SignalServer)
- [中文文档](./README_zh.md)

- [Click here to view demo video](https://www.bilibili.com/video/BV1cKTRzWEj1/?vd_source=af81440a64836b1a33af1a82ed3c8609)
- [Click here to view the project documentation](https://deepwiki.com/XQQYT/XqqytDesktop)

## How to Build & Run

Before building, please ensure the following dependencies are installed:

### Required Dependencies:
- **Qt 5** (For Qt development libraries)
- **CMake** (Build system)

### Optional Tools (for development convenience):
- **Qt Creator** (Qt IDE for development)
- **Qt Designer** (GUI design tool)

### Install Required Dependencies:
#### Set the Qt Installation Path

If Qt is installed in a custom location (e.g., not in the default system path), you need to specify the Qt installation path in the CMakeLists.txt file.

Open the CMakeLists.txt file in the root of project and edit the CMAKE_PREFIX_PATH variable to point to the directory where Qt is installed. For example:

```bash
set(CMAKE_PREFIX_PATH "/path/to/your/Qt/installation")
```
Replace /path/to/your/Qt/installation with the actual path to your Qt installation directory (e.g., /opt/Qt5.14.2/5.14.2/gcc_64).

This ensures that CMake can find your Qt installation and use it during the build process.

#### Install Optional Tools (if needed):

```bash
sudo apt install qtcreator
sudo apt install qttools5-dev-tools
```
#### Build & Run the Project
Clone the repository (if not done already):

```bash
git clone https://github.com/XQQYT/XqqytDesktop.git
cd XqqytDesktop
```
Run the build.sh:

```bash
bash build.sh
```

#### Run the application:
##### X11 Graphics System Required
XqqytDesktop only supports the X11 graphics system.

If you are currently using Wayland or another non-X11 display server, the application may not function correctly or may fail to start.

How to Switch to X11 (Ubuntu GNOME)
1. At the login screen, click your username but do not enter your password yet.

2. Click the gear icon in the bottom right corner.

3. Select "Ubuntu on Xorg" or "GNOME on X11".

4. Then enter your password and log in.

```bash
./XqqytDesktop
```
#### Additional Notes:
If you encounter issues with dependencies or missing packages, ensure that your package list is up to date (sudo apt update).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
