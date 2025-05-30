/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "WebrtcController.h"
#include "SettingInfo.h"
#include "TransferFiles.h"

static const std::string module_name = "Network";

WebrtcController::WebrtcController()
{
    webrtc_instance = std::make_unique<WebRTC>(*this);
    webrtc_instance->setSyncMsgCallback(
        std::bind(&WebrtcController::onSyncFileMsg, this, std::placeholders::_1)
    );
    json_instance = std::make_unique<NlohmannJson>();
    loadSetting();
}

void WebrtcController::loadSetting()
{
    auto config = SettingInfoManager::getInstance().getModuleConfig("Display");
    std::string capture_rate = (*config)["capture_rate"];
    int fpsValue = std::atoi(capture_rate.c_str());
    webrtc_instance->setCaptureRate(fpsValue);
    std::cout<<"catch webrtc config"<<std::endl;
}

void WebrtcController::initWebrtcSubscribe()
{

    EventBus::getInstance().subscribe(EventBus::EventType::Config_ModuleConfigUpdated,std::bind(
        &WebrtcController::onModuleConfigUpdated,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));

    EventBus::getInstance().subscribe(EventBus::EventType::Network_SendConnectRequestResult,std::bind(
        &WebrtcController::onInitWebrtc,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_RemoteReady,std::bind(
        &WebrtcController::onReady,
        this
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Network_RecvConnectRequestResult,std::bind(
        &WebrtcController::onRecvConnectRequestResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_RecvSdpOffer,std::bind(
        &WebrtcController::recvSDPOffer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_RecvSdpAnswer,std::bind(
        &WebrtcController::recvSDPAnswer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_SetRemoteSdpOfferDone,std::bind(
        &WebrtcController::onSetRemoteSDPOfferDone,
        this
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_RecvIceCandidate,std::bind(
        &WebrtcController::onRecvIceCandidate,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_RecvIceGatherDone,std::bind(
        &WebrtcController::onRecvIceCandidateDone,
        this
    ));

    EventBus::getInstance().subscribe(EventBus::EventType::Render_SetRenderInstance,std::bind(
        &WebrtcController::onSetRenderInstance,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::MouseEvent_HasEvent,std::bind(
        &WebrtcController::onSendMouseData,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::KeyboardEvent_HasEvent,std::bind(
        &WebrtcController::onSendKeyboardData,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Control_CloseControl,std::bind(
        &WebrtcController::onCloseControl,
        this
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Control_RecvCloseControl,std::bind(
        &WebrtcController::onRecvCloseControl,
        this
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Clipboard_WriteIntoClipboard,std::bind(
        &WebrtcController::onWriteIntoClipboard,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_SyncFileInfo,std::bind(
        &WebrtcController::onSyncFileInfo,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_SetFileHolder,std::bind(
        &WebrtcController::onSetFileHolder,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
}


void WebrtcController::onModuleConfigUpdated(std::string module,std::string key,std::string value)
{
    if(key == "capture_rate")
    {
        int fpsValue = std::atoi(value.c_str());
        webrtc_instance->setCaptureRate(fpsValue);
        std::cout<<"webrtc receive capture rate "<<fpsValue<<std::endl;
    }
}

void WebrtcController::onInitWebrtc(std::string, bool status)
{
    if(status)
    {
        webrtc_instance->initWebRTC(false);
        webrtc_instance->setReceiveFileProgressCb(
            std::bind(&WebrtcController::onReceiveProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );
    }
}

void WebrtcController::onReady()
{
    static bool is_first = true;
    while(!webrtc_instance->getWebRtcReady()){if(is_first){std::cout<<"watting for webrtc ready"<<std::endl;is_first = false;}}
    webrtc_instance->createSDP(WebRTCInterface::SDPType::OFFER);
}

//The peer accept the connection request
void WebrtcController::onRecvConnectRequestResult(bool status)
{
    if(status)
    {
        webrtc_instance->initWebRTC(true);
        webrtc_instance->setReceiveFileProgressCb(
            std::bind(&WebrtcController::onReceiveProgress, this, std::placeholders::_1, std::placeholders::_2,std::placeholders::_3)
        );
    }

}

void WebrtcController::onSetRemoteSDPOfferDone()
{
    webrtc_instance->createSDP(WebRTC::SDPType::ANSWER);
}


void WebrtcController::dispatch_string(EventBus::EventType event_name,std::string str)
{
    EventBus::getInstance().publish(event_name,std::move(str));
}

void WebrtcController::dispatch_string_string_string(EventBus::EventType event_name, std::string str1, std::string str2, std::string str3)
{
    EventBus::getInstance().publish(event_name,std::move(str1),std::move(str2),std::move(str3));
}

void WebrtcController::dispatch_void(EventBus::EventType event_name)
{
    EventBus::getInstance().publish(event_name);
}

void WebrtcController::dispatch_bool(EventBus::EventType event_name,bool status)
{
    EventBus::getInstance().publish(event_name,status);
}

void WebrtcController::recvSDPOffer(std::string sdp)
{
    std::cout<<"webrtc recvSDPOffer"<<std::endl;
    webrtc_instance->setRemoteSDP(std::move(sdp),WebRTC::SDPType::OFFER);
}

void WebrtcController::recvSDPAnswer(std::string sdp)
{
    webrtc_instance->setRemoteSDP(std::move(sdp),WebRTC::SDPType::ANSWER);
}

void WebrtcController::onRecvIceCandidate(std::string ice_str,std::string sdp_mid,std::string sdp_mline_index)
{
    webrtc_instance->addIceCandidateIntoBuffer(std::move(ice_str),std::move(sdp_mid),std::stoi(sdp_mline_index));
}

void WebrtcController::onRecvIceCandidateDone()
{
    
}

void WebrtcController::onSetRenderInstance(RenderInterface* instance)
{
    webrtc_instance->setRenderInstance(instance);
}

void WebrtcController::onSendMouseData(MouseEventPacket packet)
{
    webrtc_instance->sendMouseEventPacket(std::move(packet));
}

void WebrtcController::onSendKeyboardData(KeyEventPacket packet)
{
    webrtc_instance->sendKeyboardEventPacket(std::move(packet));
}

void WebrtcController::onCloseControl()
{
    webrtc_instance->closeWebRTC();
}

void WebrtcController::onRecvCloseControl()
{
    webrtc_instance->closeWebRTC();
}

void WebrtcController::onWriteIntoClipboard(std::string str)
{
    webrtc_instance->writeIntoClipboard(std::move(str));
}

void WebrtcController::onSetFileHolder(std::shared_ptr<std::ofstream> out, std::function<void()> callback)
{
    webrtc_instance->setFileHolder(out);
    callback();
}

void WebrtcController::onSyncFileInfo(FileSyncType type,std::vector<std::string> args)
{
    switch (type)
    {
        case FileSyncType::ADDFILE:
            webrtc_instance->sendFileSync(*json_instance->syncfile_add_file(std::move(args[0]), std::move(args[1]), std::move(args[2])));
            break;
        case FileSyncType::GETFILE:
            webrtc_instance->sendFileSync(*json_instance->syncfile_get_file(std::move(args[0])));
            break;
    }

}

void WebrtcController::onSyncFileMsg(std::string msg)
{
    std::cout<<msg<<std::endl;
    auto parser = json_instance->getParser();
    parser->loadJson(msg);
    if(parser->contain("type"))
    {
        std::string type = parser->getKey("type");
        auto content_parser = parser->getObj("content");
        if(type == "syncfile_add")
        {
            std::string id = content_parser->getKey("id");
            std::string file_name = content_parser->getKey("filename");
            std::string file_size = content_parser->getKey("filesize");

            EventBus::getInstance().publish(EventBus::EventType::WebRTC_SyncAddFile, std::move(id), std::move(file_name),std::move(file_size));
        } 
        else if(type == "syncfile_get_file")
        {
            std::string id = content_parser->getKey("id");
            std::string path = TransferFilesManager::getInstance().getPath(std::stol(id));

            webrtc_instance->sendFile(std::stoul(id), path);
        }
    }
}

void WebrtcController::onReceiveProgress(uint16_t id, uint32_t received_size, uint32_t total_size)
{
    EventBus::getInstance().publish(EventBus::EventType::WebRTC_ReceiveFileProgess,id,received_size,total_size);
}
