import sounddevice as sd
import numpy as np
import scipy.io.wavfile as wav

def list_input_devices():
    print("Available audio input devices:")
    for idx, device in enumerate(sd.query_devices()):
        if device['max_input_channels'] > 0:
            print(f"{idx}: {device['name']}")

def record_audio(filename, duration, sample_rate=44100, device_index=None):
    """
    Records audio from the microphone and saves it to a WAV file.

    Parameters:
    - filename: Name of the output WAV file.
    - duration: Duration of the recording in seconds.
    - sample_rate: Sampling rate (samples per second).
    - device_index: Index of the input device to use (optional).
    """
    try:
        print(f"Recording for {duration} seconds...")
        recording = sd.rec(int(duration * sample_rate), samplerate=sample_rate,
                           channels=1, dtype='int16', device=device_index)
        sd.wait()  # Wait until the recording is finished
        wav.write(filename, sample_rate, recording)
        print(f"Recording saved to {filename}")
    except Exception as e:
        print(f"An error occurred during recording: {e}")

if __name__ == "__main__":
    list_input_devices()  # Display available input devices
    duration = 20  # Duration in seconds
    filename = "recording.wav"
    device_index = int(input("Enter the device index to use for recording: "))
    record_audio(filename, duration, device_index=device_index)