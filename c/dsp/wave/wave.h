typedef struct {
    int fs;
    int bits;
    long length;
    double *s;
} MONO_PCM;

typedef struct {
    int fs;
    int bits;
    long length;
    double *sL;
    double *sR;
} STEREO_PCM;

extern void mono_wave_read(MONO_PCM *pcm, char *filename);
extern void mono_wave_write(MONO_PCM *pcm, char *filename);
extern void stereo_wave_read(STEREO_PCM *pcm, char *filename);
extern void stereo_wave_write(STEREO_PCM *pcm, char *filename);
