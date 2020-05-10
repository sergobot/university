package edu.spbu.net;

import java.io.*;
import java.net.Socket;
import java.util.stream.Collectors;

public class UniversalTCPClient {
  private Socket socket;
  private BufferedWriter output;
  private BufferedReader input;

  public void connect(String serverAddress, int port) throws IOException {
    this.socket = new Socket(serverAddress, port);
    this.input = new BufferedReader(new InputStreamReader(new DataInputStream(socket.getInputStream())));
    this.output = new BufferedWriter(new OutputStreamWriter(new DataOutputStream(socket.getOutputStream())));
  }

  public void sendRequest(String request) throws IOException {
    this.output.write(request);
    output.newLine();
    output.flush();
  }

  public String getResponse() {
    return this.input.lines().collect(Collectors.joining("\n"));
  }

  public void disconnect() throws IOException {
    this.socket.close();
  }
}
