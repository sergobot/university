package edu.spbu.net;

import java.io.*;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;

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

    public HTTPFilerServerFactory() {
    }

    @Override
    public Runnable handle(Socket socket) {
      return () -> {
        try {
          DataInputStream in = new DataInputStream(socket.getInputStream());
          DataOutputStream out = new DataOutputStream(socket.getOutputStream());

          BufferedReader inputReader = new BufferedReader(new InputStreamReader(in));

          String temp = inputReader.readLine();
          String filename = "." + temp.split(" ")[1];
          String response;

          File file = new File(filename);
          if (file.exists()) {
            response = "HTTP/1.1 200 OK\r\n" +
                "Server: Sergobot's file server\r\n" +
                "Content-Type: text/html\r\n" +
                "Connection: close\r\n\r\n";

            if (file.isDirectory()) {
              StringBuilder html = new StringBuilder();
              html.append("<!doctype html><html><body>");

              Files.list(new File(filename).toPath())
                  .forEach(path -> {
                    String p = path.toString().substring(2);
                    html.append("<a href=\"/").append(p).append("\">").append(p).append("</a><br>");
                  });

              html.append("</body></html>");
              response += html.toString();
            } else {
              FileReader fileReader = new FileReader(file);
              BufferedReader br = new BufferedReader(fileReader);

              StringBuilder b = new StringBuilder();
              String st;
              while ((st = br.readLine()) != null)
                b.append(st).append("\r\n");
              String content = b.toString();

              response += content;
            }
          } else {
            response = "HTTP/1.1 404 OK\r\n" +
                "Server: Sergobot's file server\r\n" +
                "Content-Type: text/html\r\n" +
                "Connection: close\r\n\r\n" +
                "<htlm><h1>404: File not found!</h1></html>";
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

