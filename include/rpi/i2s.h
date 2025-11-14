/*
 * Copyright 2025 Maxtek Consulting
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef RPI_I2S_H
#define RPI_I2S_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RPI_I2S_STREAM_PLAYBACK 1
#define RPI_I2S_STREAM_CAPTURE 2
#define RPI_I2S_STREAM_DUPLEX 3

#define RPI_I2S_LAYOUT_MONO 0
#define RPI_I2S_LAYOUT_STEREO 1
#define RPI_I2S_LAYOUT_STEREO_NI 2

int rpi_i2s_open(const char *device, int stream_type, int *handle);

int rpi_i2s_close(int handle);

int rpi_i2s_configure(int handle, unsigned int sample_rate, int layout, int bits_per_sample);

int rpi_i2s_start(int handle);

int rpi_i2s_stop(int handle);

int rpi_i2s_read(int handle, void *buffer, size_t size, size_t *bytes_read);

int rpi_i2s_write(int handle, const void *buffer, size_t size, size_t *bytes_written);

#ifdef __cplusplus
}
#endif

#endif // RPI_I2S_H