# Simplified-DES

This program is to encrypt and decrypt binary files using S-DES (Simplified DES) in the Cipher Block Chaining mode. The program takes the input of an initial key and an initial vector, reads the plaintext or ciphertext from a file, conducts the encryption or decryption, and writes the resulting ciphertext or plaintext into a second file.

Input Format:
----------------------------------------------------------------------------------------------------------------
The program takes a command in the following format:

SimplifiedDES_TCN5080.exe -m [mode:encrypt|decrypt] -k [key] -i [vector] -p [plain file] -c [ciphter file]

mode: can be only encrypt or decrypt
initial_key: 10-­‐bit initial key initial_vector: 8-­‐bit initial vector
plaintext_file: a binary (not text) file to store the plaintext 
ciphertext_file: a binary (not text) file to store the ciphertext

Output Format:
-----------------------------------------------------------------------------------------------------------------
The program prints output in the following format:
k1=subkey 1
k2=subkey 2
plaintext=all bytes of the plaintext separated by blanks, starting from the first byte 
ciphertext= all bytes of the ciphertext separated by blanks, starting from the first byte
