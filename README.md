# Stepper Motor Electronic Xylophone

## Motivation
The goal of this project is to create an electronic xylophone that provides additional benefits compared to a traditional xylophone. By leveraging stepper motors, the instrument becomes more portable and compact. Additionally, it introduces new playing features, such as:
- Playing music from pre-recorded audio files.
- Replaying music heard live through a connected microphone.

These functionalities are not typically possible with a standard physical xylophone. Additionally, having it be electronic also lends itself to very easily allow us to implement and add any sort of features we would want in the future, for example if we wanted to create a feature for playing speed, we could implement that easily without having to overhaul the entire project. The long-term vision is also to expand this project to other instruments, creating a product line that appeals to both professional and casual musicians.

## Related Work
There have been various projects that use stepper motors to generate audio output. Additionally, electronic xylophones have been created using pressure or capacitive sensors to trigger sounds through speakers. This project aims to combine these ideas by introducing:
- A low-latency input-to-output pipeline (from pressure sensor contact to stepper motor activation).
- The ability to replay live music.
- The capability to play music from existing audio files.

## Hardware
The hardware for this project consists of the following components:
- **4x Nema 17 stepper motors**
- **4x A4988 stepper motor drivers**
- **4x MakerHawk RP-C pressure sensors**
- **1x ADS1115 ADC**
- **1x 12V DC power supply**
- **Resistors for voltage dividers**

## Software Overview
The software implementation includes:
- **Real-time ADC reading using ADS1115**: Reads pressure sensor inputs and triggers corresponding stepper motors.
- **Stepper motor control**: Converts sensor input into stepper motor actuation, producing specific musical notes.
- **Music playback features**: Allows for pre-recorded music playback and live music replays.

### Code Highlights
The main firmware components include:
- **ADS1115 ADC Handling**: A background thread continuously updates sensor readings to prevent interference with audio output.
- **Motor Actuation Logic**: Each motor plays a specific frequency based on sensor input.
- **Music Playback Modes**:
  - **Manual Mode**: Plays notes based on real-time sensor input.
  - **Demo Mode**: Plays predefined songs.

### Key Functions
- `updateADS1115()`: Runs in a separate thread to update ADC readings.
- `getMicroseconds()`: Returns the current timestamp in microseconds.
- `actuateMotor(int motor)`: Determines whether to actuate a motor based on time elapsed since the last actuation.
- `playMusic()`: Handles playing pre-recorded melodies.

## File Structure
```
project-root/
├── audio/app/
│   ├── Makefile
│   ├── play_from_file.c
│   ├── pull_notes_to_file.py
│   ├── record.py
│
├── firmware/
│   ├── Makefile
│   ├── ads1115.c
│   ├── ads1115.h
│   ├── main.c
│   ├── music.c
│   ├── music.h
│   ├── stepper.c
│   ├── stepper.h
│   ├── pinout.txt
```

## Installation & Usage
1. **Hardware Setup**:
   - Connect the stepper motors, drivers, pressure sensors, and ADC according to `pinout.txt`.
   - Ensure the 12V power supply is properly connected.
2. **Compile Firmware**:
   ```sh
   cd firmware
   make
   ```
3. **Run the Main Program**:
   ```sh
   ./main
   ```
4. **To Play a Predefined Song**:
   Modify `DEMO_MODE` in `main.c` and recompile.
5. **To record live and save to a playable audiofile**:
   ```sh
   python record.py
   ```
   in audio/
## Future Work
- Expand the number of playable notes.
- Improve motor response time for lower latency.
- Implement more accurate and advanced music processing features, such as an ML model to try to recognize notes better through noisy audiofiles, and/or an   audio separation algorithm such as Blind Source Separation to better distinguish concurrent notes. 
- Develop a user interface for easier configuration.

## Authors
Cody Rupp & Jason Lee
