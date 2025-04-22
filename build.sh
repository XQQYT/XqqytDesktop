#!/bin/bash
#Set path to your file
file="/home/qyt/XqqytDesktop/CMakeLists.txt"

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

sudo apt-get install libg11-mesa-dev -y

sudo apt-get install nlohmann-json3-dev -y

sudo apt-get install libboost-all-dev -y

mkdir build

cd build

cmake ../

make -j$(nproc)

echo "可执行文件已生成build/XqqytDesktop"
