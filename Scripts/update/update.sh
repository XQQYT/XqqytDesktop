#!/bin/bash

cd "$(dirname "$0")/../../tmp"  # 进入 ../../tmp

# 解压 app.tar.gz 到 tmp 的上一级
tar -xzvf app.tar.gz --strip-components=1 -C ../

# 清理 tmp 目录下所有内容
rm -rf ./*

# 切换到tmp 的上一级
cd ../
# 启动 XqqytDesktop
./XqqytDesktop
