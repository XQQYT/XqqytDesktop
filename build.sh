#!/bin/bash
#Set path to your file
file="./CMakeLists.txt"

#Set the line
lineNum=9

#Write New text
read -p "please select the path:" path

# 创建临时文件并写入内容
temp_file="newPath"
echo "set(CMAKE_PREFIX_PATH \"$path\")" > "$temp_file"

# 读取临时文件内容
new_content=$(cat "$temp_file")

# 对特殊字符进行转义
escaped_content=$(echo "$new_content" | sed 's/[\/&]/\\&/g')

# 构造 sed 命令
sed_command="sed -i '${lineNum}s/.*/$escaped_content/' \"$file\""

# 执行 sed 命令
eval $sed_command

# 删除临时文件
rm "$temp_file"

# 输出修改后的文件内容
#cat "$file"
sudo apt-get install gcc g++ cmake -y

sudo apt-get install libgl1-mesa-dev -y

sudo apt-get install pkg-config -y

sudo apt-get install libglib2.0-dev -y

sudo apt-get install nlohmann-json3-dev -y

sudo apt-get install libboost-all-dev -y

sudo apt-get install libpulse-dev -y

sudo apt-get install libssl-dev -y

sudo apt-get install libx11-dev -y

sudo apt-get install libxfixes-dev -y

sudo apt-get install libxtst-dev -y

sudo apt-get install libsodium-dev -y

sudo apt-get install libxcomposite-dev libxrandr-dev libxrender-dev libxdamage-dev libgbm-dev libdrm-dev -y

mkdir build

cp -r Theme build/Theme
cp -r Scripts build/Scripts
cp -r Translations build/Translations
cp -r User build/User
cp devices-example.json build/devices.json
cp settings-example.json build/settings.json

cd build

cmake ../

make -j$(nproc)

echo "可执行文件已生成build/XqqytDesktop"
