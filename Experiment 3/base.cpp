#include <iostream>
#include <portaudio.h>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)
#define NUM_SECONDS (5)
#define NUM_CHANNELS (2)

// Define a structure to hold audio data
typedef struct {
    float* buffer;
    unsigned long buffer_size;
    unsigned long current_index;
} paTestData;

// Callback function that handles audio playback
static int playbackCallback(const void* inputBuffer, void* outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void* userData) {
    paTestData* data = (paTestData*)userData;
    float* out = (float*)outputBuffer;
    unsigned long framesLeft = data->buffer_size - data->current_index;

    // Check if we need to fill the output buffer
    if (framesLeft < framesPerBuffer) {
        // Copy the remaining frames from the audio buffer to the output buffer
        for (unsigned long i = 0; i < framesLeft; i++) {
            *out++ = data->buffer[data->current_index++];
            *out++ = data->buffer[data->current_index++];
        }

        // Fill the rest of the output buffer with zeros
        for (unsigned long i = framesLeft; i < framesPerBuffer; i++) {
            *out++ = 0;
            *out++ = 0;
        }

        // Return paComplete to signal the end of playback
        return paComplete;
    } else {
        // Copy framesPerBuffer frames from the audio buffer to the output buffer
        for (unsigned long i = 0; i < framesPerBuffer; i++) {
            *out++ = data->buffer[data->current_index++];
            *out++ = data->buffer[data->current_index++];
        }

        // Continue playback
        return paContinue;
    }
}

int main(int argc, char** argv) {
    // Initialize PortAudio
    PaError error = Pa_Initialize();
    if (error != paNoError) {
        std::cerr << "Failed to initialize PortAudio: " << Pa_GetErrorText(error) << std::endl;
        return -1;
    }

    // Load the audio file into memory
    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        std::cerr << "Failed to open audio file" << std::endl;
        return -1;
    }
    fseek(file, 0, SEEK_END);
    unsigned long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    float* buffer = new float[file_size];
    fread(buffer, sizeof(float), file_size / sizeof(float), file);
    fclose(file);

    // Create a data structure to hold audio data
    paTestData data;
    data.buffer = buffer;
    data.buffer_size = file_size / sizeof(float);
    data.current_index = 0;

    // Open a PortAudio stream for audio playback
    PaStream* stream;
    error = Pa_OpenDefaultStream(&stream, 0, NUM_CHANNELS, paFloat32, SAMPLE_RATE,
                                 FRAMES_PER_BUFFER, playbackCallback, &data);
    if (error != paNoError) {
        std::cerr << "Failed to open PortAudio stream: " << Pa_GetErrorText(error) << std::endl;
        return -1;
    }

    // Start audio playback
    error = Pa_StartStream(stream);
    if (error != paNoError) {
        std::cerr << "Failed to start Port
