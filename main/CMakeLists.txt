file(GLOB_RECURSE srcs "main.c" "src/*.c")

idf_component_register(SRCS "${srcs}"
                       REQUIRES esp_netif bt nvs_flash esp_wifi mqtt
                       INCLUDE_DIRS "./include")
