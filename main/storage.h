#pragma once

#include <cJSON.h>

typedef int file_handle_t;

void init_storage(void);

bool open_file(const char* path, file_handle_t* handle);
bool close_file(file_handle_t handle);
bool read_file_into(file_handle_t handle, uint8_t* buffer, size_t size, size_t* bytes_read);
bool get_file_size(file_handle_t handle, size_t* size);

char* read_file(const char* path);
cJSON* read_json_file(const char* path);
