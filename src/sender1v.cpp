/*
 * boostmas.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: jcalvopi
 */


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#define NUMMSG 21000

using boost::asio::ip::udp;

void handle_send(const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/);

int main(int argc, char* argv[])
{
	//char *server = "127.0.0.1";
  try
  {

	std::string host_name = "localhost";
	std::string port = "22222";

    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), host_name , port);
    udp::endpoint receiver_endpoint = *resolver.resolve(query);

    udp::socket socket(io_service);
    socket.open(udp::v4());

    boost::array<char, 5> send_buf = {{ "hola" }};

    for (int i = 0; i <= NUMMSG; i++){
     // for (;;){

     // socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
    	socket.async_send_to(boost::asio::buffer(send_buf), receiver_endpoint, handle_send);
    }

  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}

void handle_send(const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/)
  {
  }

