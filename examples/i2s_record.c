#include <rpi.h>

int main(int argc, char **argv)
{
    if (argc >= 3)
    {
    }
    else
    {
        puts("Usage: i2s_record <device> <output_file>");
    }
    return 0;
}