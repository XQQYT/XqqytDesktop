# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [v3.0.0] - 2025-05-25

### Added

- 增加文件中转站，支持上传，复制，移除文件
- 增加文件中转站支持 同步更新，多端实时保持一致
- 增加对话框的主题随同设置切换

### Fixed

- 修复了停止远控时，控制端概率性崩溃的问题
- 修复了对话框与主窗口可分离的问题
- 修复了部分窗口切换主题失败的问题

### Updated

- WebRTC 通道结构优化：由单一数据通道改为控制通道和文件通道（注意：可能与旧版本不兼容）

## [v2.0.0] - 2025-05-21

### Added

- 增加用户功能，用户登录，注册
- 增加用户中心，修改头像，用户名，密码
- 增加从服务器获取设备代码
- 增加设备列表，管理用户的设备
- 增加与用户服务器通信加密

### Fixed

- 修复了打包脚本未打包lib目录
- 修复了消息气泡概率性失效的问题
- 修复了无法正常居中弹窗的问题

### Updated

- 更新软件架构图到文档

## [v1.4.0] - 2025-05-14

### Added

- 增加支持CPU渲染视频，实现设置中GPU加速的开关
- 增加复制邀请连接的信息到剪切板
- 增加记住上个连接目标的id
- 增加记住连接过的目标的key
- 优化连接流程，发起连接时检查目标状态，目标在线才输入key

### Fixed

- 修复了被控端没有正确处理close webrtc消息的问题，这问题会使下次连接时发生崩溃

## [v1.3.0] - 2025-05-13

### Added

- 增加剪切板同步
- 增加设置手动更新动态密码
- 增加deb打包工具，deb包模板
- 增加设置开机自启

### Updated

- 重构了连接界面的UI
- 更新了打包文档(增加打包deb包的说明)

## [v1.2.0] - 2025-05-12

### Added

- 增加发起远控连接时，发起方与接收方的密码核对，Xqqyt_SignalServer版本需>=1.1.0
- 增加动态密码，定时更新
- 增加在设置界面安全设置，可修改更新密码的间隔

## [v1.1.0] - 2025-05-11

### Added

- 增加打包脚本以及打包文档

### Fixed

- 修复了openGL渲染中途图像尺寸发生改变导致的崩溃问题
- 修复了openGL在高帧率下发生的崩溃问题

### Updated

- 更改客户端从settings.json中获取信令服务器的ip和port

## [v1.0.0] - 2025-05-10

### Added

- 增加ui界面，包括连接，设备列表，设置(通用，网络，显示，网络，关于)
- 增加切换中英语言，主题，最大渲染帧率，最大捕获帧率
- 增加EventBus增加线程池，支持动态扩容
- 增加远控功能，支持键鼠同步，音频同步
- 增加支持Pulse音频驱动，X11桌面驱动


[v1.0.0]: https://github.com/XQQYT/XqqytDesktop/tree/v1.0.0
[v1.1.0]: https://github.com/XQQYT/XqqytDesktop/tree/v1.1.0
[v1.2.0]: https://github.com/XQQYT/XqqytDesktop/tree/v1.2.0
[v1.3.0]: https://github.com/XQQYT/XqqytDesktop/tree/v1.3.0
[v1.4.0]: https://github.com/XQQYT/XqqytDesktop/tree/v1.4.0