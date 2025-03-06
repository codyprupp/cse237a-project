import numpy as np
import scipy.io.wavfile as wav
from scipy.signal import find_peaks
import sounddevice as sd

def read_wav_file(filename):
    sample_rate, data = wav.read(filename)
    if data.ndim > 1:
        data = np.mean(data, axis=1)  # Convert to mono by averaging channels
    return sample_rate, data

def analyze_frequencies(data, sample_rate, frame_size=2048, hop_size=512):
    window = np.hanning(frame_size)
    frequencies = []
    durations = []
    time_index = 0

    for start in range(0, len(data) - frame_size, hop_size):
        frame = data[start:start + frame_size] * window
        spectrum = np.fft.rfft(frame)
        magnitude = np.abs(spectrum)
        peak_indices, _ = find_peaks(magnitude, height=np.max(magnitude) * 0.5)
        if peak_indices.size > 0:
            peak_freq = peak_indices[0] * sample_rate / frame_size
            if frequencies and isinstance(frequencies[-1], (int, float)) and np.isclose(peak_freq, frequencies[-1], atol=5):
                durations[-1] += hop_size / sample_rate
            else:
                frequencies.append(peak_freq)
                durations.append(hop_size / sample_rate)
        else:
            if frequencies and frequencies[-1] is not None:
                frequencies.append(None)
                durations.append(hop_size / sample_rate)
        time_index += hop_size / sample_rate

    return frequencies, durations

def play_sine_wave(frequency, duration, sample_rate=44100, amplitude=0.5):
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    wave = amplitude * np.sin(2 * np.pi * frequency * t)
    sd.play(wave, samplerate=sample_rate)
    sd.wait()  # Wait until sound has finished playing

def main(filename):
    sample_rate, data = read_wav_file(filename)
    frequencies, durations = analyze_frequencies(data, sample_rate)
    notes = [(round(freq,2), round(dur,2)) for freq, dur in zip(frequencies, durations) if freq is not None]
    
    filtered_notes = [(freq, dur) for freq, dur in notes if dur >= 0.07]
    # for note in filtered_notes:
    #     print(f"Frequency: {note[0]:.2f} Hz, Duration: {note[1]:.2f} s")
    for freq, dur in filtered_notes:
        print(f"Frequency: {freq:.2f} Hz, Duration: {dur:.2f} s")
        play_sine_wave(freq, dur)
    
if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python script.py <wav_file>")
        sys.exit(1)
    main(sys.argv[1])
