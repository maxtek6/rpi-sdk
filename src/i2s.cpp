#include <internal.hpp>

using handle_type = snd_pcm_t;
using handle_ptr = std::unique_ptr<handle_type, decltype(&snd_pcm_close)>;

class i2s_device
{
public:
    i2s_device(const std::string& device, bool rx, bool tx)
    {
        _rx_handle.reset(open_handle(rx, device.c_str(), SND_PCM_STREAM_CAPTURE));
        _tx_handle.reset(open_handle(tx, device.c_str(), SND_PCM_STREAM_PLAYBACK));
    }
    ~i2s_device() = default;
    ssize_t read(void *buf, size_t size)
    {
        if(!_rx_handle)
        {
            throw std::runtime_error("I2S RX handle not opened");
        }
        return snd_pcm_readi(_rx_handle.get(), buf, size / 4); // Assuming 16-bit stereo
    }
    ssize_t write(const void *buf, size_t size)
    {
        if(!_tx_handle)
        {
            throw std::runtime_error("I2S TX handle not opened");
        }
        return snd_pcm_writei(_tx_handle.get(), buf, size / 4); // Assuming 16-bit stereo
    }
private:
    static handle_type* open_handle(bool do_open, const char *name, snd_pcm_stream_t stream)
    {
        handle_type *result(nullptr);
        if(do_open)
        {
            if (snd_pcm_open(&result, name, stream, 0) != 0)
            {
                throw std::runtime_error("Failed to open I2S stream");
            }
        }
        return result;
    }
    handle_ptr _rx_handle= handle_ptr(nullptr, snd_pcm_close);
    handle_ptr _tx_handle= handle_ptr(nullptr, snd_pcm_close);
};

class i2s_driver
{
public:
    static i2s_driver& get()
    {
        return instance;
    }

    i2s_driver() = default;
    ~i2s_driver() = default;

private:
    static i2s_driver instance;
    std::vector<std::unique_ptr<i2s_device>> devices;
};

