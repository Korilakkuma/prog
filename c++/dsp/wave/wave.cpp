#include <iostream>
#include <fstream>
#include <string>
#include "wave.h"

void WAVE::wave_read(MONO_PCM *pcm, std::string filename) {
    char riff_chunk_id[4];
    long riff_chunk_size;
    char riff_form_type[4];
    char fmt_chunk_id[4];
    long fmt_chunk_size;
    short fmt_wave_format_type;
    short fmt_channel;
    long fmt_samples_per_sec;
    long fmt_bytes_per_sec;
    short fmt_block_size;
    short fmt_bits_per_sample;
    char data_chunk_id[4];
    long data_chunk_size;
    short data;

    std::fstream file(filename, std::ios::binary | std::ios::in);

    file.read((char *)riff_chunk_id, 1 * 4);
    file.read((char *)&riff_chunk_size, 4 * 1);
    file.read((char *)riff_form_type, 1 * 4);
    file.read((char *)fmt_chunk_id, 1 * 4);
    file.read((char *)&fmt_chunk_size, 4 * 1);
    file.read((char *)&fmt_wave_format_type, 2 * 1);
    file.read((char *)&fmt_channel, 2 * 1);
    file.read((char *)&fmt_samples_per_sec, 4 * 1);
    file.read((char *)&fmt_bytes_per_sec, 4 * 1);
    file.read((char *)&fmt_block_size, 2 * 1);
    file.read((char *)&fmt_bits_per_sample, 2 * 1);
    file.read((char *)data_chunk_id, 1 * 4);
    file.read((char *)&data_chunk_size, 4 * 1);

    pcm->fs = fmt_samples_per_sec;
    pcm->bits = fmt_bits_per_sample;
    pcm->length = data_chunk_size / (1 * (pcm->bits / 8));

    std::cout << "Read ..." << std::endl;
    std::cout << "Sample Rate: " << pcm->fs << std::endl;
    std::cout << "Quantization Bit: " << pcm->bits << std::endl;
    std::cout << "Length: " << pcm->length << std::endl;

    pcm->s.reserve(pcm->length);

    for (int n = 0; n < pcm->length; n++) {
        // std::cout << static_cast<int>(n / pcm->length) << " %" << std::endl;
        file.read((char *)&data, sizeof(short) * 1);
        pcm->s[n] = (double)data / 32768.0;
    }

    file.close();
}

void WAVE::wave_write(MONO_PCM *pcm, std::string filename) {
    char riff_chunk_id[4];
    long riff_chunk_size;
    char riff_form_type[4];
    char fmt_chunk_id[4];
    long fmt_chunk_size;
    short fmt_wave_format_type;
    short fmt_channel;
    long fmt_samples_per_sec;
    long fmt_bytes_per_sec;
    short fmt_block_size;
    short fmt_bits_per_sample;
    char data_chunk_id[4];
    long data_chunk_size;
    short data;
    double s;

    riff_chunk_id[0] = 'R';
    riff_chunk_id[1] = 'I';
    riff_chunk_id[2] = 'F';
    riff_chunk_id[3] = 'F';

    riff_chunk_size = 36 + (1 * (16 / 8) * pcm->length);

    riff_form_type[0] = 'W';
    riff_form_type[1] = 'A';
    riff_form_type[2] = 'V';
    riff_form_type[3] = 'E';

    fmt_chunk_id[0] = 'f';
    fmt_chunk_id[1] = 'm';
    fmt_chunk_id[2] = 't';
    fmt_chunk_id[3] = ' ';

    fmt_chunk_size = 16;
    fmt_wave_format_type = 1;
    fmt_channel = 1;
    fmt_samples_per_sec = pcm->fs;
    fmt_bytes_per_sec = pcm->fs * (1 * (pcm->bits / 8));
    fmt_block_size = 1 * (pcm->bits / 8);
    fmt_bits_per_sample = pcm->bits;

    data_chunk_id[0] = 'd';
    data_chunk_id[1] = 'a';
    data_chunk_id[2] = 't';
    data_chunk_id[3] = 'a';

    data_chunk_size = (1 * (16 / 8)) * pcm->length;

    std::fstream file(filename, std::ios::binary | std::ios::out);

    file.write((char *)riff_chunk_id, 1 * 4);
    file.write((char *)&riff_chunk_size, 4 * 1);
    file.write((char *)riff_form_type, 1 * 4);
    file.write((char *)fmt_chunk_id, 1 * 4);
    file.write((char *)&fmt_chunk_size, 4 * 1);
    file.write((char *)&fmt_wave_format_type, 2 * 1);
    file.write((char *)&fmt_channel, 2 * 1);
    file.write((char *)&fmt_samples_per_sec, 4 * 1);
    file.write((char *)&fmt_bytes_per_sec, 4 * 1);
    file.write((char *)&fmt_block_size, 2 * 1);
    file.write((char *)&fmt_bits_per_sample, 2 * 1);
    file.write((char *)data_chunk_id, 1 * 4);
    file.write((char *)&data_chunk_size, 4 * 1);

    std::cout << "Write ..." << std::endl;
    std::cout << "Sample Rate: " << pcm->fs << std::endl;
    std::cout << "Quantization Bit: " << pcm->bits << std::endl;
    std::cout << "Length: " << pcm->length << std::endl;

    for (int n = 0; n < pcm->length; n++) {
        // std::cout << static_cast<int>(n / pcm->length) << " %" << std::endl;
        s = ((pcm->s[n] + 1.0) / 2.0) * 65536.0;

        if (s > 65535.0) {
            s = 65535.0;
        }

        if (s < 0.0) {
            s = 0.0;
        }

        data = (short)((s + 0.5) - 32768);

        file.write((char *)&data, 2 * 1);
    }

    file.close();
}
void WAVE::wave_read(STEREO_PCM *pcm, std::string filename) {
    char riff_chunk_id[4];
    long riff_chunk_size;
    char riff_form_type[4];
    char fmt_chunk_id[4];
    long fmt_chunk_size;
    short fmt_wave_format_type;
    short fmt_channel;
    long fmt_samples_per_sec;
    long fmt_bytes_per_sec;
    short fmt_block_size;
    short fmt_bits_per_sample;
    char data_chunk_id[4];
    long data_chunk_size;
    short dataL;
    short dataR;

    std::fstream file(filename, std::ios::binary | std::ios::in);

    file.read((char *)riff_chunk_id, 1 * 4);
    file.read((char *)&riff_chunk_size, 4 * 1);
    file.read((char *)riff_form_type, 1 * 4);
    file.read((char *)fmt_chunk_id, 1 * 4);
    file.read((char *)&fmt_chunk_size, 4 * 1);
    file.read((char *)&fmt_wave_format_type, 2 * 1);
    file.read((char *)&fmt_channel, 2 * 1);
    file.read((char *)&fmt_samples_per_sec, 4 * 1);
    file.read((char *)&fmt_bytes_per_sec, 4 * 1);
    file.read((char *)&fmt_block_size, 2 * 1);
    file.read((char *)&fmt_bits_per_sample, 2 * 1);
    file.read((char *)data_chunk_id, 1 * 4);
    file.read((char *)&data_chunk_size, 4 * 1);

    pcm->fs = fmt_samples_per_sec;
    pcm->bits = fmt_bits_per_sample;
    pcm->length = data_chunk_size / (2 * (pcm->bits / 8));

    std::cout << "Read ..." << std::endl;
    std::cout << "Sample Rate: " << pcm->fs << std::endl;
    std::cout << "Quantization Bit: " << pcm->bits << std::endl;
    std::cout << "Length: " << pcm->length << std::endl;

    pcm->sL.reserve(pcm->length);
    pcm->sR.reserve(pcm->length);

    for (int n = 0; n < pcm->length; n++) {
        // std::cout << static_cast<int>(n / pcm->length) << " %" << std::endl;
        file.read((char *)&dataL, sizeof(short) * 1);
        file.read((char *)&dataR, sizeof(short) * 1);

        pcm->sL[n] = (double)dataL / 32768.0;
        pcm->sR[n] = (double)dataR / 32768.0;
    }

    file.close();
}

void WAVE::wave_write(STEREO_PCM *pcm, std::string filename) {
    char riff_chunk_id[4];
    long riff_chunk_size;
    char riff_form_type[4];
    char fmt_chunk_id[4];
    long fmt_chunk_size;
    short fmt_wave_format_type;
    short fmt_channel;
    long fmt_samples_per_sec;
    long fmt_bytes_per_sec;
    short fmt_block_size;
    short fmt_bits_per_sample;
    char data_chunk_id[4];
    long data_chunk_size;
    short dataL;
    short dataR;
    double sL;
    double sR;

    riff_chunk_id[0] = 'R';
    riff_chunk_id[1] = 'I';
    riff_chunk_id[2] = 'F';
    riff_chunk_id[3] = 'F';

    riff_chunk_size = 36 + (2 * (16 / 8) * pcm->length);

    riff_form_type[0] = 'W';
    riff_form_type[1] = 'A';
    riff_form_type[2] = 'V';
    riff_form_type[3] = 'E';

    fmt_chunk_id[0] = 'f';
    fmt_chunk_id[1] = 'm';
    fmt_chunk_id[2] = 't';
    fmt_chunk_id[3] = ' ';

    fmt_chunk_size = 16;
    fmt_wave_format_type = 1;
    fmt_channel = 2;
    fmt_samples_per_sec = pcm->fs;
    fmt_bytes_per_sec = pcm->fs * (2 * (pcm->bits / 8));
    fmt_block_size = 2 * (pcm->bits / 8);
    fmt_bits_per_sample = pcm->bits;

    data_chunk_id[0] = 'd';
    data_chunk_id[1] = 'a';
    data_chunk_id[2] = 't';
    data_chunk_id[3] = 'a';

    data_chunk_size = (2 * (16 / 8)) * pcm->length;

    std::fstream file(filename, std::ios::binary | std::ios::out);

    file.write((char *)riff_chunk_id, 1 * 4);
    file.write((char *)&riff_chunk_size, 4 * 1);
    file.write((char *)riff_form_type, 1 * 4);
    file.write((char *)fmt_chunk_id, 1 * 4);
    file.write((char *)&fmt_chunk_size, 4 * 1);
    file.write((char *)&fmt_wave_format_type, 2 * 1);
    file.write((char *)&fmt_channel, 2 * 1);
    file.write((char *)&fmt_samples_per_sec, 4 * 1);
    file.write((char *)&fmt_bytes_per_sec, 4 * 1);
    file.write((char *)&fmt_block_size, 2 * 1);
    file.write((char *)&fmt_bits_per_sample, 2 * 1);
    file.write((char *)data_chunk_id, 1 * 4);
    file.write((char *)&data_chunk_size, 4 * 1);

    std::cout << "Write ..." << std::endl;
    std::cout << "Sample Rate: " << pcm->fs << std::endl;
    std::cout << "Quantization Bit: " << pcm->bits << std::endl;
    std::cout << "Length: " << pcm->length << std::endl;

    for (int n = 0; n < pcm->length; n++) {
        // std::cout << static_cast<int>(n / pcm->length) << " %" << std::endl;
        sL = ((pcm->sL[n] + 1.0) / 2.0) * 65536.0;
        sR = ((pcm->sR[n] + 1.0) / 2.0) * 65536.0;

        if (sL > 65535.0) {
            sL = 65535.0;
        }

        if (sL < 0.0) {
            sL = 0.0;
        }

        if (sR > 65535.0) {
            sR = 65535.0;
        }

        if (sR < 0.0) {
            sR = 0.0;
        }

        dataL = (short)((sL + 0.5) - 32768);
        dataR = (short)((sR + 0.5) - 32768);

        file.write((char *)&dataL, 2 * 1);
        file.write((char *)&dataR, 2 * 1);
    }

    file.close();
}
