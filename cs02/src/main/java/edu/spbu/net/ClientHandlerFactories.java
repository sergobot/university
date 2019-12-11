package edu.spbu.net;

import java.io.*;
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

  public static class HTTPFilerServerFactory implements ClientHandlerFactory {
    String filename;

    public HTTPFilerServerFactory(String filename) {
      this.filename = filename;
    }

    @Override
    public Runnable handle(Socket socket) {
      return () -> {
        try {
          DataInputStream in = new DataInputStream(socket.getInputStream());
          DataOutputStream out = new DataOutputStream(socket.getOutputStream());

          BufferedReader inputReader = new BufferedReader(new InputStreamReader(in));

          String temp;
          while (!(temp = inputReader.readLine()).equals(""))
            System.out.println(temp);

          File file = new File(this.filename);
          String response;
          if (file.exists()) {
            FileReader fileReader = new FileReader(file);
            BufferedReader br = new BufferedReader(fileReader);

            StringBuilder b = new StringBuilder();
            String st;
            while ((st = br.readLine()) != null)
              b.append(st);
            String content = b.toString();

            response = "HTTP/1.1 200 OK\r\n" +
                "Server: Sergobot's file server\r\n" +
                "Content-Type: text/html\r\n" +
                "Connection: close\r\n\r\n" + content;
          } else {
            response = "HTTP/1.1 404 OK\r\n" +
                "Server: Sergobot's file server\r\n" +
                "Content-Type: text/html\r\n" +
                "Connection: close\r\n\r\n" +
                "<htlm><h1>404: File not found!</h1?</html>";
          }

          out.write(response.getBytes());
          out.flush();
        } catch (IOException e) {
          System.out.println("Could not serve file to socket: " + socket);
        }
      };
    }
  }
}

