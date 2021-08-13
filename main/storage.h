#pragma once

#include <cJSON.h>

/**
 * File descriptor.
 */
typedef int file_handle_t;

/**
 * Initialize the non-volatile storage on flash, and the SD card file system.
 */
void init_storage(void);

/**
 * Try to open a given file.
 *
 * @param path Path to the file
 * @param handle In case of success, this is set to the opened file handle
 * @return Whether the operation succeeded
 */
bool open_file(const char* path, file_handle_t* handle);

/**
 * Try to close a file.
 *
 * @param handle File handle to use
 * @return Whether the operation succeeded
 */
bool close_file(file_handle_t handle);

/**
 * Try to read file content into a given buffer.
 *
 * @param handle File handle to use
 * @param buffer Where to put the read bytes
 * @param size How many bytes to read
 * @param bytes_read Actual number of read bytes
 * @return Whether the operation succeeded and there is still bytes to read
 */
bool read_file_into(file_handle_t handle, uint8_t* buffer, size_t size, size_t* bytes_read);

/**
 * Try to get a file's size in bytes.
 *
 * @param handle File handle to use
 * @param size In case of success, this is set to the file's size
 * @return Whether the operation succeeded
 */
bool get_file_size(file_handle_t handle, size_t* size);

// TODO: refactor these
char* read_file(const char* path);
cJSON* read_json_file(const char* path);
