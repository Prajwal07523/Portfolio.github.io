#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
using namespace std;

// Function to generate RSA key pair
void generateRSAKeyPair(string &publicKey, string &privateKey) {
    RSA *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);

    BIO *pri = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(pri, rsa, NULL, NULL, 0, NULL, NULL);
    int pri_len = BIO_pending(pri);
    privateKey.resize(pri_len);
    BIO_read(pri, &privateKey[0], pri_len);

    BIO *pub = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(pub, rsa);
    int pub_len = BIO_pending(pub);
    publicKey.resize(pub_len);
    BIO_read(pub, &publicKey[0], pub_len);

    BIO_free_all(pub);
    BIO_free_all(pri);
    RSA_free(rsa);
}

// Function to encrypt data using RSA public key
string rsaEncrypt(const string &data, const string &publicKey) {
    BIO *keybio = BIO_new_mem_buf((void*)publicKey.c_str(), -1);
    RSA *rsa = PEM_read_bio_RSAPublicKey(keybio, NULL, NULL, NULL);

    int dataSize = data.size();
    int rsaLen = RSA_size(rsa);
    char *encrypted = new char[rsaLen];

    int resultLen = RSA_public_encrypt(dataSize, (unsigned char*)data.c_str(), (unsigned char*)encrypted, rsa, RSA_PKCS1_OAEP_PADDING);

    string encryptedStr(encrypted, resultLen);

    delete[] encrypted;
    RSA_free(rsa);
    BIO_free_all(keybio);

    return encryptedStr;
}

// Function to decrypt data using RSA private key
string rsaDecrypt(const string &encryptedData, const string &privateKey) {
    BIO *keybio = BIO_new_mem_buf((void*)privateKey.c_str(), -1);
    RSA *rsa = PEM_read_bio_RSAPrivateKey(keybio, NULL, NULL, NULL);

    int rsaLen = RSA_size(rsa);
    char *decrypted = new char[rsaLen];

    int resultLen = RSA_private_decrypt(rsaLen, (unsigned char*)encryptedData.c_str(), (unsigned char*)decrypted, rsa, RSA_PKCS1_OAEP_PADDING);

    string decryptedStr(decrypted, resultLen);

    delete[] decrypted;
    RSA_free(rsa);
    BIO_free_all(keybio);

    return decryptedStr;
}

int main() {
    string publicKey, privateKey;
    generateRSAKeyPair(publicKey, privateKey);

    string data = "Sensitive Payment Information";
    string encryptedData = rsaEncrypt(data, publicKey);
    string decryptedData = rsaDecrypt(encryptedData, privateKey);

    cout << "Original Data: " << data << endl;
    cout << "Encrypted Data: " << encryptedData << endl;
    cout << "Decrypted Data: " << decryptedData << endl;

    return 0;
}
