#include <string>
#include <vector>

typedef struct {
    int fs;
    int bits;
    long length;
    std::vector<double> s;
} MONO_PCM;

typedef struct {
    int fs;
    int bits;
    long length;
    std::vector<double> sL;
    std::vector<double> sR;
} STEREO_PCM;

class WAVE {
public:
    static void wave_read(MONO_PCM *pcm, std::string filename);
    static void wave_read(STEREO_PCM *pcm, std::string filename);
    static void wave_write(MONO_PCM *pcm, std::string filename);
    static void wave_write(STEREO_PCM *pcm, std::string filename);
};
