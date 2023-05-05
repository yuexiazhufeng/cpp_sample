
#include <vector>
#include <iostream>
#include <cstring>
std::vector<uint8_t> arr = {0x03, 0x04, 0x05, 0x56, 0x67, 0x78, 0x89, 0x91, 0x12, 0xaa, 0xbb};

//std::hex
int main (int argc, char *argv[]){
    // std::string hexStr = "0123456789abcdef";
    std::stringstream ss;
    for (size_t i = 0; i < arr.size(); i++){
        ss << std::hex << static_cast<int>(arr[i]);
    }
    std::cout << ss.str().c_str() << std::endl;
    return 0;
}

//"0123456789abcdef"
int main (int argc, char *argv[]){
    std::string hexStr = "0123456789abcdef";
    std::stringstream ss;
    for (size_t i = 0; i < arr.size(); i++){
        ss << hexStr[arr[i] >> 4] << hexStr[arr[i] & 0x0f];
    }
    std::cout << ss.str().c_str() << std::endl;
    return 0;
}

//snprintf
int main (int argc, char *argv[]){
    char str[100];
    size_t temp_len = 0;
    memset(str, 0x00, sizeof(str));
    for (size_t i = 0; i < arr.size(); i++){
        temp_len += snprintf(str + temp_len, 100 - temp_len - 1, "%02x", arr[i]);
    }
    std::cout << str << std::endl;
    return 0;
}
