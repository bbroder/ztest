cmake_minimum_required(VERSION 2.8)

include_directories (/usr/local/include ../zmq/cppzmq)
link_directories (/usr/local/lib)
add_executable (server server.cpp bondquote.pb.cc envelope.pb.cc)
target_link_libraries (server zmq protobuf)
add_executable (client client.cpp bondquote.pb.cc envelope.pb.cc)
target_link_libraries (client zmq protobuf)
