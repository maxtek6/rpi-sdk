#include <rpi.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <signal.h>

static bool running;
static void main_loop(const char *device_name, const char *output_path);
static void signal_handler(int signum);

int main(int argc, const char **argv)
{
    int handle;
    if (argc >= 3)
    {
        rpi_initialize();
        signal(SIGINT, signal_handler);
        running = true;
        main_loop(argv[1], argv[2]);
        rpi_shutdown();
    }
    else
    {
        puts("Usage: i2s_record <device> <output_file>");
    }
    return 0;
}

void main_loop(const char *device_name, const char *output_path)
{
    char error[128];
    bool is_open;
    int rc, handle;
    uint8_t buffer[4096];
    size_t bytes_read;

    is_open = false;

    rc = rpi_i2s_open(device_name, RPI_I2S_STREAM_CAPTURE, &handle);
    if (rc != 0)
    {
        snprintf(error, sizeof(error), "Failed to open I2S device(%d)", rc);
        goto error;
    }

    is_open = true;

    rc = rpi_i2s_configure(handle, 44100, 2, 16);
    if (rc != 0)
    {
        snprintf(error, sizeof(error), "Failed to configure I2S device(%d)", rc);
        goto error;
    }

    rc = rpi_i2s_start(handle);
    if (rc != 0)
    {
        snprintf(error, sizeof(error), "Failed to start I2S device(%d)", rc);
        goto error;
    }

    while (running)
    {
        rc = rpi_i2s_read(handle, buffer, sizeof(buffer), &bytes_read);
        if (rc < 0)
        {
            snprintf(error, sizeof(error), "Failed to read from I2S device(%d)", rc);
            goto error;
        }
        // Here you would write bytes_read from buffer to output file
    }

    rc = rpi_i2s_stop(handle);
    if (rc != 0)
    {
        snprintf(error, sizeof(error), "Failed to stop I2S device(%d)", rc);
        goto error;
    }

    goto done;
error:
    printf("Error: %s\n", error);
done:
    if(is_open)
    {
        rpi_i2s_close(handle);
    }
}

void signal_handler(int signum)
{
    running = false;
}