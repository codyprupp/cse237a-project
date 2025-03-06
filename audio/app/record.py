import sounddevice as sd
import numpy as np
import scipy.io.wavfile as wav

def list_input_devices():
    print("Available audio input devices:")
    for idx, device in enumerate(sd.query_devices()):
        if device['max_input_channels'] > 0:
            print(f"{idx}: {device['name']}")

def record_audio(filename, duration, sample_rate=44100, device_index=None):

    try:
        print(f"Recording for {duration} seconds...")
        recording = sd.rec(int(duration * sample_rate), samplerate=sample_rate,
                           channels=1, dtype='int16', device=device_index)
        sd.wait()  # wait until the recording is finished
        
        #save to file
        filename = "audio/" + filename
        wav.write(filename, sample_rate, recording)
        print(f"Recording saved to {filename}")
    except Exception as e:
        print(f"An error occurred during recording: {e}")

if __name__ == "__main__":
    #request input device and then record for 20s
    list_input_devices()  
    device_index = int(input("Enter the device index to use for recording: "))
    filename = input("Enter file name: ") + ".wav"
    duration = int(input("Enter recording duration in seconds: "))
    record_audio(filename, duration, device_index=device_index)