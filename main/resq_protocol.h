#ifndef RESQ_PROTOCOL_H
#define RESQ_PROTOCOL_H

#include <stdint.h>

#define COORD_SCALE 10000000.0f

#pragma pack(push, 1)
typedef struct {
    uint8_t  node_id;      // 1 Byte
    int32_t  latitude;     // 4 Bytes
    int32_t  longitude;    // 4 Bytes
    uint8_t  alert_type;   // 1 Byte
    uint8_t  battery;      // 1 Byte
    uint16_t sequence_id;  // 2 Bytes
} resq_message_t;
#pragma pack(pop)

typedef struct {
    uint8_t  node_id;
    float    latitude;
    float    longitude;
    uint8_t  alert_type;
    uint8_t  battery;
    uint16_t sequence_id;
} resq_data_t;

static inline void resq_encode(const resq_data_t *in, resq_message_t *out) {
    out->node_id     = in->node_id;
    out->latitude    = (int32_t)(in->latitude * COORD_SCALE);
    out->longitude   = (int32_t)(in->longitude * COORD_SCALE);
    out->alert_type  = in->alert_type;
    out->battery     = in->battery;
    out->sequence_id = in->sequence_id;
}

static inline void resq_decode(const resq_message_t *in, resq_data_t *out) {
    out->node_id     = in->node_id;
    out->latitude    = (float)in->latitude / COORD_SCALE;
    out->longitude   = (float)in->longitude / COORD_SCALE;
    out->alert_type  = in->alert_type;
    out->battery     = in->battery;
    out->sequence_id = in->sequence_id;
}

#endif // RESQ_PROTOCOL_H