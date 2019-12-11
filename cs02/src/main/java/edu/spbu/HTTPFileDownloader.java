package edu.spbu;

import edu.spbu.net.UniversalTCPClient;

import java.io.IOException;

public class HTTPFileDownloader {
  UniversalTCPClient client;

  HTTPFileDownloader() {
    this.client = new UniversalTCPClient();
  }

  public String download(String serverAddress, int port, String path) throws IOException {
    this.client.connect(serverAddress, port);
    System.out.println("Connected successfully!");
    this.client.sendRequest("GET " + path + " HTTP/1.1\r\nHost: " + serverAddress + "\r\n\r\n");
    System.out.println("Request sent successfully!");
    String response = this.client.getResponse();
    System.out.println("Response received successfully!");
    this.client.disconnect();
    System.out.println("Connection closed successfully!");
    return response;
  }

  public static void main(String[] args) throws IOException {
    HTTPFileDownloader d = new HTTPFileDownloader();
    System.out.println(d.download("math.spbu.ru", 80, "/rus"));
  }
}
