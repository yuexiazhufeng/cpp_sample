
#include "message_queue.hpp"
#include <iostream>
#include <thread>
#include <unistd.h>

typedef struct  {
    int flag;
} Message;

int main(int argc, char *argv[]) {
    MessageQueue<std::shared_ptr<Message>> msg;

    std::thread th([&msg](){
        int i = 3;
        while (i > 0) {
            std::shared_ptr<Message> mesg = std::make_shared<Message>();
            mesg->flag = i;
            msg.push(mesg);
            sleep(3);
            i--;
        }
        return ;
    });
    th.detach();

    while (1){
        std::shared_ptr<Message> mesg;
        std::cv_status status;
        status = msg.wait_for(mesg, std::chrono::seconds(1));
        if (std::cv_status::timeout == status) {
            std::cout << "wait for message timeout..." << std::endl;
        } else {
            std::cout << "message flag: "<< std::to_string(mesg->flag) << std::endl;
        }
    }
    return 0;
}