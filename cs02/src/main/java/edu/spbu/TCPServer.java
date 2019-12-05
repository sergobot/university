package edu.spbu;

import edu.spbu.net.ClientHandlerFactories;
import edu.spbu.net.UniversalTCPServer;

public class TCPServer {
  public static void main(String[] args) {
    UniversalTCPServer s = new UniversalTCPServer(8080, new ClientHandlerFactories.CapitalizerFactory(), 20);
    s.start();
  }
}
