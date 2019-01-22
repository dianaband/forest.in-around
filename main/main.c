#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_mesh.h"
#include "esp_mesh_internal.h"
#include "nvs_flash.h"

#include "Arduino.h"
#include "config.h"

// wifi
uint8_t my_mac_sta[6] = { 0, };
uint8_t my_mac_ap[6] = { 0, };

void app_main()
{
  /* nvs flash */
  ESP_ERROR_CHECK(nvs_flash_init());

  /* tcpip initialization */
  tcpip_adapter_init();
  /* for mesh
   * stop DHCP server on softAP interface by default
   * stop DHCP client on station interface by default
   * */
  ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
  ESP_ERROR_CHECK(tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA));

  /* wifi initialization */
  ESP_ERROR_CHECK(esp_event_loop_init(NULL, NULL));
  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&config));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
  ESP_ERROR_CHECK(esp_wifi_start());

  /* get wifi info */
  ESP_ERROR_CHECK(esp_wifi_get_mac(WIFI_IF_STA, my_mac_sta));
  ESP_ERROR_CHECK(esp_wifi_get_mac(WIFI_IF_AP, my_mac_ap));

  /* mesh initialization */
  ESP_ERROR_CHECK(esp_mesh_init());
  ESP_ERROR_CHECK(esp_mesh_set_max_layer(CONFIG_MESH_MAX_LAYER));
  ESP_ERROR_CHECK(esp_mesh_set_vote_percentage(1));
  ESP_ERROR_CHECK(esp_mesh_set_ap_assoc_expire(10));
  #ifdef MESH_FIX_ROOT
  ESP_ERROR_CHECK(esp_mesh_fix_root(1));
  #endif
  mesh_cfg_t cfg = MESH_INIT_CONFIG_DEFAULT();

  /* mesh ID */
  memcpy((uint8_t *) &cfg.mesh_id, MESH_ID, 6);

  /* mesh event callback */
  cfg.event_cb = &mesh_event_handler;

  /* router */
  cfg.channel = CONFIG_MESH_CHANNEL;
  cfg.router.ssid_len = strlen(CONFIG_MESH_ROUTER_SSID);
  memcpy((uint8_t *) &cfg.router.ssid, CONFIG_MESH_ROUTER_SSID, cfg.router.ssid_len);
  memcpy((uint8_t *) &cfg.router.password, CONFIG_MESH_ROUTER_PASSWD, strlen(CONFIG_MESH_ROUTER_PASSWD));

  /* mesh softAP */
  ESP_ERROR_CHECK(esp_mesh_set_ap_authmode(CONFIG_MESH_AP_AUTHMODE));
  cfg.mesh_ap.max_connection = CONFIG_MESH_AP_CONNECTIONS;
  memcpy((uint8_t *) &cfg.mesh_ap.password, CONFIG_MESH_AP_PASSWD, strlen(CONFIG_MESH_AP_PASSWD));
  ESP_ERROR_CHECK(esp_mesh_set_config(&cfg));

  /* mesh start */
  ESP_ERROR_CHECK(esp_mesh_start());
  ESP_LOGI(MESH_TAG, "mesh starts successfully, heap:%d, %s\n",  esp_get_free_heap_size(), esp_mesh_is_root_fixed() ? "root fixed" : "root not fixed");

  /* arduino init & start */
  initArduino();
  arduino_start();
}
