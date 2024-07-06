#include <iostream>
#include <iomanip>
#include <openssl/aes.h>
#include <openssl/rand.h>
using namespace std;

void aesEncrypt(const string &data, string &encryptedData, string &key, string &iv) {
    key.resize(AES_BLOCK_SIZE);
    iv.resize(AES_BLOCK_SIZE);

    // Generate random key and IV
    RAND_bytes((unsigned char*)&key[0], AES_BLOCK_SIZE);
    RAND_bytes((unsigned char*)&iv[0], AES_BLOCK_SIZE);

    AES_KEY encryptKey;
    AES_set_encrypt_key((unsigned char*)key.c_str(), 128, &encryptKey);

    encryptedData.resize((data.size() / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE);
    AES_cfb128_encrypt((unsigned char*)data.c_str(), (unsigned char*)&encryptedData[0], data.size(), &encryptKey, (unsigned char*)&iv[0], nullptr, AES_ENCRYPT);
}

void aesDecrypt(const string &encryptedData, const string &key, const string &iv, string &decryptedData) {
    AES_KEY decryptKey;
    AES_set_decrypt_key((unsigned char*)key.c_str(), 128, &decryptKey);

    decryptedData.resize(encryptedData.size());
    AES_cfb128_encrypt((unsigned char*)encryptedData.c_str(), (unsigned char*)&decryptedData[0], encryptedData.size(), &decryptKey, (unsigned char*)&iv[0], nullptr, AES_DECRYPT);
}

int main() {
    string data = "Sensitive Payment Information";
    string encryptedData, decryptedData, key, iv;

    aesEncrypt(data, encryptedData, key, iv);
    aesDecrypt(encryptedData, key, iv, decryptedData);

    cout << "Original Data: " << data << endl;
    cout << "Encrypted Data: " << encryptedData << endl;
    cout << "Decrypted Data: " << decryptedData << endl;

    return 0;
}
