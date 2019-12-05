package edu.spbu.net;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientHandlerFactories {
  public static class CapitalizerFactory implements ClientHandlerFactory {
    @Override
    public Runnable handle(Socket socket) {
      return () -> {
        try {
          BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
          PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
          String line;
          while ((line = in.readLine()) != null) {
            out.println(line.toUpperCase());
            if (line.isEmpty())
              break;
          }
        } catch (IOException e) {
          e.printStackTrace();
        }
      };
    }
  }
}

