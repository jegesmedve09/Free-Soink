from midiutil import MIDIFile

# Initialize MIDI object with 4 tracks (Melody, Arpeggio, Bass, Drums)
midi = MIDIFile(4)

# Set tempo to 140 BPM across all tracks
for track in range(4):
    midi.addTrackName(track, 0, f"Track {track+1}")
    midi.addTempo(track, 0, 140)

# Track configuration
TRACK_MELODY = 0
TRACK_ARP = 1
TRACK_BASS = 2
TRACK_DRUMS = 3

# Channel mapping (Channel 9 is standard for MIDI drums)
midi.addProgramChange(TRACK_MELODY, 0, 0, 81)  # Lead synth / Sawtooth-esque
midi.addProgramChange(TRACK_ARP, 1, 0, 80)     # Square lead / Arp
midi.addProgramChange(TRACK_BASS, 2, 0, 38)    # Synth bass

# Chord progression in C Major: C -> G -> Am -> F (4 bars per loop, repeated 8 times for ~1.4 mins)
# Each chord lasts 4 beats (1 bar = 4 quarter notes)
chords = [
    [60, 64, 67],  # C major (C4, E4, G4)
    [55, 59, 62],  # G major (G3, B3, D3)
    [57, 60, 64],  # A minor (A3, C4, E4)
    [53, 57, 60]   # F major (F3, A3, C4)
]

melody_notes = [
    # Bar 1 (C)
    (72, 0.0, 0.75, 100), (74, 0.75, 0.5, 90), (76, 1.25, 0.75, 100), (79, 2.0, 2.0, 110),
    # Bar 2 (G)
    (77, 4.0, 0.75, 100), (76, 4.75, 0.5, 90), (74, 5.25, 0.75, 100), (72, 6.0, 2.0, 110),
    # Bar 3 (Am)
    (72, 8.0, 0.75, 100), (74, 8.75, 0.5, 90), (76, 9.25, 0.75, 100), (81, 10.0, 2.0, 110),
    # Bar 4 (F)
    (79, 12.0, 0.75, 100), (77, 12.75, 0.5, 90), (76, 13.25, 0.75, 100), (74, 14.0, 2.0, 110)
]

# Generate 8 full loops (approx 72 seconds at 140 BPM)
loops = 8
for loop in range(loops):
    loop_offset = loop * 16.0
    
    # 1. Melody Track
    for note, start, duration, volume in melody_notes:
        midi.addNote(TRACK_MELODY, 0, note, loop_offset + start, duration, volume)
        
    # 2. Arpeggio Track (16th-note rapid fire running through chord tones)
    for bar in range(4):
        bar_offset = loop_offset + (bar * 4.0)
        chord = chords[bar]
        # Play 16 sixteenth notes per bar (0.25 beats each)
        for i in range(16):
            # Cycle through chord notes: root, 3rd, 5th, octave-3rd
            note_idx = i % len(chord)
            note = chord[note_idx] + 12  # One octave up for brightness
            midi.addNote(TRACK_ARP, 1, note, bar_offset + (i * 0.25), 0.2, 85)

    # 3. Bassline Track (Syncopated 8th-note root pulses)
    for bar in range(4):
        bar_offset = loop_offset + (bar * 4.0)
        root = chords[bar][0] - 12  # Bass octave down
        for i in range(8):
            midi.addNote(TRACK_BASS, 2, root, bar_offset + (i * 0.5), 0.4, 100)

    # 4. Drum Track (Channel 9: 36=Kick, 38=Snare, 42=Closed Hi-Hat)
    for bar in range(4):
        bar_offset = loop_offset + (bar * 4.0)
        for beat in range(4):
            beat_pos = bar_offset + beat
            # Kick on 1 and 3, Snare on 2 and 4
            if beat in [0, 2]:
                midi.addNote(TRACK_DRUMS, 9, 36, beat_pos, 0.5, 110)
            else:
                midi.addNote(TRACK_DRUMS, 9, 38, beat_pos, 0.5, 105)
            
            # Hi-hats on every 16th note
            for sixteenth in range(4):
                midi.addNote(TRACK_DRUMS, 9, 42, beat_pos + (sixteenth * 0.25), 0.2, 70)

# Write output file
with open("golden_hilltop_sprint.mid", "wb") as output_file:
    midi.writeFile(output_file)
