import librosa
from pydub.generators import Sine
from pydub.playback import play
import sounddevice as sd
import numpy as np
import sys

import musicalbeeps

note_names = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
note_freqs = {
    'C': 261.63, 'C#': 277.18, 'D': 293.66, 'D#': 311.13, 'E': 329.63,
    'F': 349.23, 'F#': 369.99, 'G': 392.00, 'G#': 415.30, 'A': 440.00,
    'A#': 466.16, 'B': 493.88
}


def chroma_to_note_name(frequency):
    return note_names[note_pitch]

audio_file = sys.argv[1]

y, sr = librosa.load(audio_file)

chroma = librosa.feature.chroma_stft(y=y, sr=sr)
onset_frames = librosa.onset.onset_detect(y=y, sr=sr)

first = True
notes = []
prev_note_duration = 0

for onset in onset_frames:
  chroma_at_onset = chroma[:, onset]
  note_pitch = chroma_at_onset.argmax()
#   print(note_pitch)
  note_name = chroma_to_note_name(note_pitch)

  if not first:
      note_duration = librosa.frames_to_time(onset, sr=sr)
      notes.append((note_name,onset, note_duration - prev_note_duration))
      prev_note_duration = note_duration
  else:
      prev_note_duration = librosa.frames_to_time(onset, sr=sr)
      first = False
      
print("Note pitch \t Onset frame \t Note duration")
for entry in notes:
  print(entry[0],'\t\t',entry[1],'\t\t',entry[2])

player = musicalbeeps.Player(volume = .3, mute_output = False)

for entry in notes:
  player.play_note(entry[0], round(entry[2], 2))