#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "resq_protocol.h"

static const char *TAG = "ResQ_Protocol";
static QueueHandle_t lora_tx_queue = NULL;

static void lora_tx_task(void *pvParameters) {
    resq_message_t tx_msg;
    
    while (1) {
        if (xQueueReceive(lora_tx_queue, &tx_msg, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "Trama de %d bytes recibida en cola. Enviando por SPI a SX1262...", (int)sizeof(resq_message_t));
        }
    }
}

void app_main(void) {
    _Static_assert(sizeof(resq_message_t) == 13, "Error: ResQMessage debe ser exactamente de 13 bytes");

    lora_tx_queue = xQueueCreate(10, sizeof(resq_message_t));

    xTaskCreatePinnedToCore(
        lora_tx_task,
        "lora_tx_task",
        3072,
        NULL,
        5,
        NULL,
        1
    );

    ESP_LOGI(TAG, "Modulo de protocolo de comunicacion iniciado correctamente.");

    resq_data_t sos_event = {
        .node_id = 1,
        .latitude = 19.432608f,
        .longitude = -99.133209f,
        .alert_type = 0x01,
        .battery = 88,
        .sequence_id = 1
    };

    resq_message_t binary_payload;
    resq_encode(&sos_event, &binary_payload);

    xQueueSend(lora_tx_queue, &binary_payload, 0);
}