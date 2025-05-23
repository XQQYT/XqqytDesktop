/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "EventBus.h"
#include "NetworkController.h"
#include "WebrtcController.h"
#include "ConfigController.h"

EventBus::EventBus(){
    config_controller = std::make_unique<ConfigController>();
    network_controller = std::make_unique<NetworkController>();
    webrtc_controller = std::make_unique<WebrtcController>();
    thread_pool = std::make_unique<ThreadPool<>>(2, 4, 1024, ThreadPoolType::NORMAL);
    registerAllEvents();
};

EventBus::~EventBus(){
};

void EventBus::initModuleSubscribe()
{
    //config controller must be the first to init subscribe, due to networkd and webrtc depend on it
    config_controller->initConfigSubscribe();
    network_controller->initNetworkSubscribe();
    webrtc_controller->initWebrtcSubscribe();
}

void EventBus::registerAllEvents() {
    using ET = EventType;
    const std::vector<ET> allEvents = {
        // UI
        ET::UI_ConnectWidgetInitDone,

        // Network
        ET::Network_GetTargetStatus,
        ET::Network_ConnectToSignalServerResult,
        ET::Network_SignalRegisterResult,
        ET::Network_TargetStatus,
        ET::Network_ConnectToTarget,
        ET::Network_HasConnectRequest,
        ET::Network_SendConnectRequestResult,
        ET::Network_RecvConnectRequestResult,
        ET::Network_SendLogout,
        ET::Network_SendToUserServer,
        ET::Network_ConnectToUserServerResult,
        ET::Network_ReceiveDeviceCode,
        ET::Network_ReConnectToSignalServer,
        ET::Network_LoginResult,
        ET::Network_UserRegisterResult,
        ET::Network_UserAvatarUpdate,
        ET::Network_UpdateDeviceList,
        ET::Network_UpdateDeviceCommentResult,
        ET::Network_DeleteDeviceInConfig,
        ET::Network_DeleteDeviceResult,
        ET::Network_UploadAvatarResult,
        ET::Network_UpdateUsernameResult,
        ET::Network_UpdateUserPasswordResult,
        ET::Network_RegisterDeviceResult,
        ET::Network_GetDeviceListResult,
        ET::Network_SyncFileInfo,
        // WebRTC
        ET::WebRTC_InitWebrtcDone,
        ET::WebRTC_RemoteReady,
        ET::WebRTC_CreateSdpOffer,
        ET::WebRTC_SetRemoteSdpOfferDone,
        ET::WebRTC_CreateSdpAnswer,
        ET::WebRTC_RecvSdpOffer,
        ET::WebRTC_RecvSdpAnswer,
        ET::WebRTC_SendIceCandidate,
        ET::WebRTC_RecvIceCandidate,
        ET::WebRTC_SendIceGatherDone,
        ET::WebRTC_RecvIceGatherDone,
        ET::WebRTC_ConnectionStatus,

        // Render
        ET::Render_SetRenderInstance,

        // Input
        ET::MouseEvent_HasEvent,
        ET::KeyboardEvent_HasEvent,
        ET::Clipboard_WriteIntoClipboard,

        // Control
        ET::Control_CloseControl,
        ET::Control_RecvCloseControl,

        // Config
        ET::Config_UpdateModuleConfig,
        ET::Config_UpdateModuleConfigDone,
        ET::Config_WriteIntoFile,
        ET::Config_ModuleConfigUpdated,
        ET::Config_CopyFile,
        ET::Config_RenameFile,
        ET::Config_UpdateDeviceComment,
    };

    for (const auto& evt : allEvents) {
        registerEvent(evt);
    }
}
