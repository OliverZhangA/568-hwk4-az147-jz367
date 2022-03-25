#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;

int initclient(const char* hostname, const char* port) {
    int status;
    int socket_fd;
    struct addrinfo host_info;
    struct addrinfo *host_info_list;
    //const char *hostname = mastername;
    //const char *port = "2618";
    
    memset(&host_info, 0, sizeof(host_info));

    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    //host_info.ai_flags = AI_PASSIVE;

    status = getaddrinfo(hostname, port, &host_info, &host_info_list);
    if (status != 0) {
        cerr << "Error: cannot get address info for host" << endl;
        cerr << "  (" << hostname << "," << port << ")" << endl;
        exit(EXIT_FAILURE);
    }
    //create a socket
    socket_fd = socket(host_info_list->ai_family, 
		     host_info_list->ai_socktype, 
		     host_info_list->ai_protocol);
    if (socket_fd == -1) {
        cerr << "Error: cannot create socket" << endl;
        cerr << "  (" << hostname << "," << port << ")" << endl;
        exit(EXIT_FAILURE);
    }
    //bind the socket
    //int yes = 1;
    // status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    // status = bind(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    // if (status == -1) {
    //     cerr << "Error: cannot bind socket" << endl;
    //     cerr << "  (" << hostname << "," << port << ")" << endl;
    //     exit(EXIT_FAILURE);
    // }
    // status = listen(socket_fd, 100);
    // if (status == -1) {
    //     cerr << "Error: cannot listen on socket" << endl; 
    //     cerr << "  (" << hostname << "," << port << ")" << endl;
    //     exit(EXIT_FAILURE);
    // }

    //connect
    status = connect(socket_fd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1) {
        cerr << "Error: cannot connect to socket" << endl;
        cerr << "  (" << hostname << "," << port << ")" << endl;
        return -1;
    }
    freeaddrinfo(host_info_list);
    //can not close the socket here, will use later
    return socket_fd;
}
// int fetch_portnum(int socket_num) {
//     struct sockaddr_in sock;
//     socklen_t length = sizeof(sock);
//     int status;
//     status = getsockname(socket_num, (struct sockaddr*)&sock, &length);
//     if(status == -1) {
//         cerr << "not able to get socketname and the port num"<<endl;
//         exit(EXIT_FAILURE);
//     }
//     return ntohs(sock.sin_port);
// }
int main(int argc, char* argv[]) {
    const char* master_name = "vcm-24561.vm.duke.edu";
    const char* port_num = "12345";
    int status;
    //connect the player to the ringmaster
    int player_socknum = initclient(master_name, port_num);
    
    //send and receive and store information accordingly before the start of the game
    //send port num of this client, how to get it?
    //cout<<"selfsockfd is"<<self_sockfd<<endl;
    //int player_portnum = fetch_portnum(self_sockfd);
    string buff = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
    "<create><account id=\"123456\" balance=\"1000\"/>" \
    "<symbol sym=\"SPY\">" \
    "<account id=\"123456\">100000</account>" \
    "</symbol>" \
    "</create>";
    //char send_data[] = buff.c_str();
    cout<<"client sending xml data: "<<endl<<buff<<endl;
    send(player_socknum, buff.c_str(), buff.size(), 0);
    close(player_socknum);
    return EXIT_SUCCESS;
}