import numpy as np
import scipy.io.wavfile as wav
from scipy.signal import find_peaks
from pathlib import Path

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

    #iterate through audio by frame_size
    for start in range(0, len(data) - frame_size, hop_size):
        
        #for each frame, grab the most prominent frequencies/notes
        frame = data[start:start + frame_size] * window
        spectrum = np.fft.rfft(frame)
        magnitude = np.abs(spectrum)
        peak_indices, _ = find_peaks(magnitude, height=np.max(magnitude) * 0.5)

        if peak_indices.size > 0:
            peak_freq = peak_indices[0] * sample_rate / frame_size

            #if most recent frequency/note is similar to the previous one, simply extend the duration of the previous note
            #otherwise, add to list as a new note/frequency
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

def main(filename):
    # grab notes
    sample_rate, data = read_wav_file(filename)
    frequencies, durations = analyze_frequencies(data, sample_rate)
    notes = [(round(freq,2), round(dur,2)) for freq, dur in zip(frequencies, durations) if freq is not None]
    
    #reduce noise by removing notes that are too short
    filtered_notes = [(freq, dur) for freq, dur in notes if dur >= 0.07]

    #write the read in notes to an outfile
    script_dir = Path(__file__).parent
    notes_dir = script_dir / 'notesfiles'
    notes_dir.mkdir(parents=True, exist_ok=True)
    
    outfile = notes_dir / (Path(filename).stem + ".txt")

    with open(outfile, 'w') as file:
        for f, d in filtered_notes:
            file.write(str(f) + ',' + str(d) + '\n')


    
if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python script.py <wav_file>")
        sys.exit(1)
    main(sys.argv[1])
