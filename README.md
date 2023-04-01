# Password Manager

Password Manager is a project that securely stores and manages passwords using RSA encryption implemented through the OpenSSL library. **While the project is still under development, the basic functionality is already in place. The program generates RSA keys, stores and retrieves them from files and encrypts and decrypts stored passwords using RSA encryption algorithm.**

In addition to RSA encryption, the Password Manager project is also working on adding an extra layer of SHA256 encryption to further enhance the security of the stored passwords. This document provides an overview of the project, its features, and its usage.

 # Simple example of how to use the Password Manager:
 
1. To generate an RSA key for the first time, select option 4 from the menu. The key will be saved in a file named "yourkey.PEM" inside the program files.

2. It's important to copy the key file out of the program files to save it because the key file will be destroyed when the program is closed.

3. Once the RSA key is generated, we can add or remove records to the "data.txt" file and list them as needed.

4. When the program is closed, all keys and password strings will be destroyed. As a result, two files will be created: "data.txt" with the list of items and "encrypted_message.dat" with the encrypted passwords.

![alt-text](https://github.com/pscieszka/passManager/blob/master/resources/Animation.gif)
# Reopening program

1. To retrieve the stored passwords, we need to select the "Read Key from File" option and provide the file path where the RSA key are stored on our computer.
2. Once the key is loaded, we can choose the "Show Password" option to select the password that we want to decrypt.

3. The password will be displayed in its decrypted form, without any encryption.

![alt-text](https://github.com/pscieszka/passManager/blob/master/resources/Animation2.gif)

# Files with data after use

yourkey.PEM
![]([image.jpg](https://github.com/pscieszka/passManager/blob/master/resources/key.png?raw=true))
