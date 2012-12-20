#include "zmq.hpp"
#include <string>
#include <iostream>
#include "envelope.pb.h"
#include "bondquote.pb.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    srand (time(NULL));
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    std::string bob;
    for (int i = 0; i != 262100; i++) bob += (char) (rand() % 26 + 68);

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 1; request_nbr != 190001; request_nbr++) {
        zmq::message_t request (bob.size());
        memcpy ((void *) request.data (), (void *) bob.data(), bob.size());
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
//        std::cout << "Received World " << request_nbr << std::endl;

        if (request_nbr % 1000 == 0) fprintf (stdout, "Count: %d %f\n", request_nbr, double(request_nbr * 5242) / 1.0e6);
    }
    return 0;
}
