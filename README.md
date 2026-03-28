🎧 MP3 Tag Reader and Editor

A terminal-based MP3 metadata reader and editor implemented in C, designed to extract and modify ID3v2 tags at the binary level without affecting audio data.

This project demonstrates low-level file handling, binary parsing, and system-level programming concepts.

📌 Project Highlights
-> 📖 View MP3 metadata: Title, Artist, Album, Year, Genre, Comments
-> ✏️ Edit specific ID3v2 frames and generate an updated MP3 file safely
-> 🎯 Focused support for **ID3v2.3.0**
-> ⚡ Lightweight command-line interface (CLI)
-> 🧩 Modular design with separate source and header files
-> 🔒 Ensures audio data integrity during metadata updates

🧾 Supported ID3 Frames
| Frame ID ->   Description |
| TIT2     ->   Title       |
| TPE1     ->   Artist      |
| TALB     ->   Album       |
| TYER     ->   Year        |
| TCON     ->   Genre       |
| COMM     ->   Comment     |

📂 Project Structure
-> MP3_main.c - CLI handling and program flow
-> MP3_view.c - Metadata reading logic
-> MP3_edit.c - Metadata editing logic
-> MP3_header.h - Header file with declarations
-> sample.mp3 - Sample test file
-> README.md - Project documentation

⚙️ Usage
▶️ View Metadata
./a.out -v <filename.mp3>

✏️ Edit Metadata
./a.out -e <tag_option> <new_value> <filename.mp3>

🏷️ Tag Options
Option	Description
-t	Title
-a	Artist
-A	Album
-y	Year
-c	Comment
-g	Genre

❓ Help Menu
./a.out --h

🧪 Example
Viewing Metadata
./a.out -v sample.mp3

----- MP3 TAGS -----
Title   : Jai Ho
Artist  : AR Rahman
Album   : Slumdog Millionarie
Year    : 2009
Genre   : Bollywood
Comment : eng

Editing Metadata
./a.out -e -t "New Song Title" sample.mp3
Title changed successfully!

⚙️ How It Works (High-Level)
🔹 Header & Version Validation -> Verifies the presence of "ID3" identifier 
    Supports only ID3v2.3.0 for safe parsing and editing
🔹 Frame Parsing -> Navigates through ID3 frames (TIT2, TPE1, TALB, etc.)
    Extracts metadata using file offsets and structured parsing
🔹 Editing Mechanism -> Creates a temporary file (temp.mp3)
    Copies existing data and replaces only the selected frame
    Renames the updated file back to the original
🔹 Endianness Handling -> Frame sizes are processed using byte-swapping techniques
    Ensures correct interpretation of binary data

🧠 Key Concepts Applied
Binary File Handling (fread, fwrite, fseek)
Bit Manipulation & Endianness
Pointers & Memory Management
Structures in C
Command-Line Argument Parsing
Modular Programming

⚠️ Limitations
Supports only ID3v2.3.0 (v2.4 not supported)
Fixed-size buffers (large metadata may be truncated)
Limited frame parsing (currently handles selected frames)
Assumes basic text encoding (ASCII/ISO-8859-1 only)

🛠️ Troubleshooting
❌ File not opening → Check file path and permissions
❌ Unsupported ID3 version → Ensure file uses ID3v2.3
❌ Invalid arguments → Use --h for help menu

🚀 Future Enhancements
Full support for ID3v2.4
Unicode support (UTF-16 / UTF-8)
Dynamic memory allocation for large metadata
Complete tag parsing (not limited to fixed frames)
GUI-based interface
Batch processing for multiple MP3 files

