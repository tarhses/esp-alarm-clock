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
 * @param bytes_read This is set to the actual number of bytes read
 * @return Whether the operation succeeded and there is still bytes to read
 */
bool read_file_into(file_handle_t handle, uint8_t* buffer, size_t size, size_t* bytes_read);

/**
 * Try to read JSON data from a file.
 *
 * @param handle File handle to use
 * @param json Where to put the read data
 * @return Whether the operation succeeded
 */
bool read_file_json(file_handle_t handle, cJSON** json);

/**
 * Try to get a file's size in bytes.
 *
 * @param handle File handle to use
 * @param size In case of success, this is set to the file's size
 * @return Whether the operation succeeded
 */
bool get_file_size(file_handle_t handle, size_t* size);

/**
 * List every regular files in a given folder.
 *
 * A list of strings will be allocated and must be freed by the caller.
 *
 * @param path Where to find the folder
 * @param list In case of success, this list will contain the filenames
 * @param size In case of success, this will be set to the number of files
 * @return Whether the operation succeeded
 */
bool list_files(const char* path, char*** list, size_t* size);

/**
 * Concatenate two paths adding a '/' between them if needed.
 *
 * @param a The first path (a directory)
 * @param b The second path
 * @return A new allocated path that must be freed
 */
char* concat_paths(const char* a, const char* b);
