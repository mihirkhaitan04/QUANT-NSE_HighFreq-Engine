#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hProv;
    if (CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cout << "CryptAcquireContext OK\n";
        CryptReleaseContext(hProv, 0);
    } else {
        std::cout << "CryptAcquireContext Failed\n";
    }
    return 0;
}
