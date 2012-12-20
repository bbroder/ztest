#include <fstream>
#include <iostream>
#include "zmq.hpp"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "envelope.pb.h"
#include "bondquote.pb.h"

int
main (int argc, char** argv)
{
    int major, minor, patch;
    zmq_version (&major, &minor, &patch);
    fprintf (stdout, "Current 0MQ version is %d.%d.%d\n", major, minor, patch);
    std::fstream out ("sup", std::ios::out | std::ios::binary);
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    int count = 0;
    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);

        count ++;
        //  Do some 'work'
//        std::cout << request.size() << std::endl;
        out.write ((const char*) request.data(), request.size());
        zmq::message_t reply (0);
        memcpy ((void *) reply.data (), "", 0);
        socket.send (reply);

        if (count % 1000 == 0) {
                fprintf (stdout, "Count: %d\n", count);
                out.flush();
        }

    }
    fprintf (stdout, "Total count: %d", count);
    return 0;
}

