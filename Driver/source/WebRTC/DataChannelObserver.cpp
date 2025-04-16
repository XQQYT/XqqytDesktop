#include "DataChannelObserver.h"


void DCO::OnStateChange()
{

}
void DCO::OnMessage(const webrtc::DataBuffer& buffer)
{

}

void DCO::OnBufferedAmountChange(uint64_t sent_data_size) 
{

}
   
bool DCO::IsOkToCallOnTheNetworkThread() 
{ 
    return false; 
}