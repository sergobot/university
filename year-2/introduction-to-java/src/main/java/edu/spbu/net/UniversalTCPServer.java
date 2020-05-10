package edu.spbu.net;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class UniversalTCPServer {
  private ExecutorService pool;
  private ServerSocket socket;
  private ClientHandlerFactory handlerFactory;

  public UniversalTCPServer(int port, ClientHandlerFactory handlerFactory, int maxClients) {
    try {
      this.socket = new ServerSocket(port);
      this.handlerFactory = handlerFactory;
      this.pool = Executors.newFixedThreadPool(maxClients);
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public void start() {
    System.out.println("Server has started! Waiting for connection...");

    while (true) {
      try {
        Socket socket = this.socket.accept();
        System.out.println("Connected: " + socket);
        pool.submit(() -> {
              try {
                this.handlerFactory.handle(socket).run();
                socket.close();
                System.out.println("Connection closed: " + socket);
              } catch (IOException e) {
                System.out.println("Could not close connection: " + e);
              }
            }
        );
      } catch (IOException e) {
        System.out.println("Could not establish connection: " + e);
      }
    }
  }
}

