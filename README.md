# LSB Steganography in C

This project implements **Least Significant Bit (LSB) Steganography**, a method of hiding secret information within image files. The program encodes and decodes messages by manipulating the least significant bits of pixel values, ensuring the changes are imperceptible to the human eye.

## Features
- **Encoding**: Hide a secret message inside an image file.
- **Decoding**: Extract the hidden message from an encoded image.
- **File Support**: Supports bitmap images (`.bmp`) for encoding and decoding.
- **Data Security**: Provides a basic level of data hiding for secure communication.

## How It Works
1. **Encoding**:
   - The secret message is converted into binary.
   - The binary data is embedded into the least significant bits of the pixel values of the image.
2. **Decoding**:
   - The binary data is extracted from the least significant bits of the image.
   - The binary data is then converted back to retrieve the secret message.

## Usage
1. **Compile the program** using a C compiler:
   ```bash
   gcc lsb_steganography.c -o lsb_steganography
