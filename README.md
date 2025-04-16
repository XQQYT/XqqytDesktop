# XqqytDesktop

## File Structure

- **[UI]**: A directory that contains all UI-related files. Each widget has its own directory, containing `.h`, `.cpp`, and `.ui` files.
- **[Control]**: A directory that contains classes responsible for managing the data flow between the UI and the driver.
- **[Driver]**: A directory that contains the driver classes for database, network, configuration files, and local files. In the future, I plan to add QoS (Quality of Service) and stream control to this directory.
- **[main.cpp]**: The entry point of the program. It will initialize and start the project.

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

Open the CMakeLists.txt file in the root of project and edit the CMAKE_PREFIX_PATH variable to point to the directory where Qt is installed. For example:ss

```bash
set(CMAKE_PREFIX_PATH "/path/to/your/Qt/installation")
```
Replace /path/to/your/Qt/installation with the actual path to your Qt installation directory (e.g., /opt/Qt5.14.2/5.14.2/gcc_64).

This ensures that CMake can find your Qt installation and use it during the build process.

```bash
sudo apt update
sudo apt install qtbase5-dev cmake
```
#### Install Optional Tools (if needed):

```bash
sudo apt install qtcreator
sudo apt install qttools5-dev-tools
```
#### Build & Run the Project
Clone the repository (if not done already):

```bash
git clone <repository-url>
cd XqqytDesktop
```
Create a build directory:

```bash
mkdir build
cd build
```
Generate the build files with CMake:

```bash
cmake ..
```
Compile the project:

```bash
make -j$(nproc)
```
-j$(nproc) will automatically use all available CPU cores for faster compilation.

Run the application:

```bash
./XqqytDesktop
```
#### Additional Notes:
If you encounter issues with dependencies or missing packages, ensure that your package list is up to date (sudo apt update).

