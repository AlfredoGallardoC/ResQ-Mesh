#include <stdio.h>
#include "esp_log.h"
#include "resq_sos.h"

static const char *TAG = "ResQ_SOS";

void resq_sos_process(const resq_sos_message_t *sos_msg) {
    ESP_LOGI(TAG, "--- ALERTA SOS RECIBIDA ---");
    ESP_LOGI(TAG, "Timestamp: %lu", (unsigned long)sos_msg->timestamp);
    ESP_LOGI(TAG, "Tipo Incidente: 0x%02X", sos_msg->incident_type);
    ESP_LOGI(TAG, "Latitud: %f | Longitud: %f", 
             sos_msg->latitude / 10000000.0f, 
             sos_msg->longitude / 10000000.0f);
}