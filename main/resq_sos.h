#ifndef RESQ_SOS_H
#define RESQ_SOS_H

#include <stdint.h>

// Definición de la trama binaria extendida para SOS (18 bytes)
typedef struct __attribute__((packed)) {
    uint8_t  user_id[4];     // ID único de usuario (4 bytes)
    uint32_t timestamp;       // UTC UNIX Timestamp (4 bytes)
    int32_t  latitude;        // Grados * 10^7 (4 bytes)
    int32_t  longitude;       // Grados * 10^7 (4 bytes)
    uint8_t  incident_type;   // 0x01: Médico, 0x02: Atrapado, 0x03: Incendio (1 byte)
    uint8_t  battery;         // Batería % (1 byte)
} resq_sos_message_t;

void resq_sos_process(const resq_sos_message_t *sos_msg);

#endif // RESQ_SOS_H