package edu.spbu;

import edu.spbu.net.ClientHandlerFactories;
import edu.spbu.net.UniversalTCPServer;

public class HTTPFileServer {
  public static void main(String[] args) {
    UniversalTCPServer s = new UniversalTCPServer(8080, new ClientHandlerFactories.HTTPFilerServerFactory("build.gradle"), 20);
    s.start();
  }
}
