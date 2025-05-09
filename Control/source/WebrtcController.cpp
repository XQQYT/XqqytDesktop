/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "WebrtcController.h"
#include "SettingInfo.h"

static const std::string module_name = "Network";

WebrtcController::WebrtcController()
{
    webrtc_instance = std::make_unique<WebRTC>(*this);
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

    EventBus::getInstance().subscribe("/config/module_config_updated",std::bind(
        &WebrtcController::onModuleConfigUpdated,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));

    EventBus::getInstance().subscribe("/network/send_connect_request_result",std::bind(
        &WebrtcController::onInitWebrtc,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    
    EventBus::getInstance().subscribe("/webrtc/remote_ready",std::bind(
        &WebrtcController::onReady,
        this
    ));
    EventBus::getInstance().subscribe("/network/recv_connect_request_result",std::bind(
        &WebrtcController::onRecvConnectRequestResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_sdp_offer",std::bind(
        &WebrtcController::recvSDPOffer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_sdp_answer",std::bind(
        &WebrtcController::recvSDPAnswer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/set_remote_sdp_offer_done",std::bind(
        &WebrtcController::onSetRemoteSDPOfferDone,
        this
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_ice_candidate",std::bind(
        &WebrtcController::onRecvIceCandidate,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_ice_gather_done",std::bind(
        &WebrtcController::onRecvIceCandidateDone,
        this
    ));

    EventBus::getInstance().subscribe("/render/set_render_instance",std::bind(
        &WebrtcController::onSetRenderInstance,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/mouse_event/has_event",std::bind(
        &WebrtcController::onSendMouseData,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/keyboard_event/has_event",std::bind(
        &WebrtcController::onSendKeyboardData,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/control/close_control",std::bind(
        &WebrtcController::onCloseControl,
        this
    ));
    EventBus::getInstance().subscribe("/control/recv_close_control",std::bind(
        &WebrtcController::onRecvCloseControl,
        this
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
        webrtc_instance->initWebRTC(false);
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
        webrtc_instance->initWebRTC(true);
}

void WebrtcController::onSetRemoteSDPOfferDone()
{
    webrtc_instance->createSDP(WebRTC::SDPType::ANSWER);
}


void WebrtcController::dispatch_string(std::string event_name,std::string str)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name),std::move(str));
}

void WebrtcController::dispatch_string_string_string(std::string event_name, std::string str1, std::string str2, std::string str3)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name),std::move(str1),std::move(str2),std::move(str3));
}

void WebrtcController::dispatch_void(std::string event_name)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name));
}

void WebrtcController::dispatch_bool(std::string event_name,bool status)
{
    EventBus::getInstance().publish(std::move(event_name),status);
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