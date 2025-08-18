#ifndef LIBIOTCAPIST_H
#define LIBIOTCAPIST_H

#include <stdint.h>

/*
 * Minimal representation of the packet header used by the
 * IOTC library.  Only the fields required by the exported
 * byte order conversion helpers are modelled here.
 */
typedef struct {
    uint32_t flag;      /* packet flags and version */
    uint32_t sid;       /* session identifier */
    uint32_t seq;       /* sequence number */
    uint32_t timestamp; /* timestamp or similar */
    uint32_t payload;   /* payload length */
} IOTCHeader;

int64_t IOTC_Session_Read(int64_t sid, void *buf, int64_t size,
                          int64_t timeout, int32_t flags);
int64_t IOTC_sCHL_shutdown(int64_t ssl);
uint32_t IOTC_Data_ntoh(uint32_t data);
uint32_t IOTC_Data_hton(uint32_t data);
void IOTC_Header_ntoh(IOTCHeader *hdr);
void IOTC_Header_hton(IOTCHeader *hdr);
void IOTC_Get_Version(uint32_t *pnVersion);
const char *IOTC_Get_Version_String(void);

int64_t IOTC_Session_Channel_ON(int64_t sid, int32_t chID);
int64_t IOTC_Session_Channel_OFF(int64_t sid, int32_t chID);
int64_t IOTC_Session_Channel_Check_ON_OFF(int64_t sid, int32_t chID);
int64_t IOTC_Session_Close(int64_t sid);
int32_t IOTC_Session_Get_Free_Channel(int64_t sid);

#endif /* LIBIOTCAPIST_H */
