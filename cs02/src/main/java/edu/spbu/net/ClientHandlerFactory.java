package edu.spbu.net;

import java.net.Socket;

public interface ClientHandlerFactory {
  Runnable handle(Socket socket);
}
