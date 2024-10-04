# File Encryption and Decryption Tool

This is a lightweight C++ tool that securely encrypts and decrypts files using the XOR cipher. It operates by taking a predefined or random key and applying it to the contents of the file to obfuscate or restore the original data.

### Usage

Clone the repository
```bash
git clone https://github.com/aabboudi/file-encryption-tool.git
```

Build the project into an executable
```bash
g++ main.cpp utils.cpp actions.cpp -o lock
```

Encrypt your first file. This will output a secret key that must be stored somewhere safe
```bash
./lock --encrypt --file test-encrypt.txt
```

Decrypt the example file
```bash
./lock --decrypt --file test-decrypt.txt --key verySecretKey --overwrite
```
