#ifndef _GLOBALENUM_H
#define _GLOBALENUM_H

#include <string>

enum class UserMsgType
{
    RegisterDeviceCode,
    LOGIN,
    REGISTER,
    UPDATEAVATAR,
    UPDATEUSERNAME,
    UPDATEPASSWORD,
    UPDATEDEVICECOMMENT,
    DELETEDEVICE
};

enum class FileSyncType
{
    ADDFILE,
    GETFILE
};

#endif //_GLOBALENUM_H