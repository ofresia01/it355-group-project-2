package chat_room;

import java.io.*;
import java.net.*;
import java.util.*;

/*
 * Class that acts as the server host and facilitates all client interactions from ClientHandler.
 * No untrustworthy methods are passed immutable objects - conformant to CWE-374.
 */
public class ChatServer {
    // Static member fields declared final - conformant to CWE-500
    private static final int PORT = 8080; // Standard port for localhost
    private static Set<ClientHandler> clients = new HashSet<ClientHandler>(); // The set of clients currently connected.
                                                                              // Set is private and static, conformant
                                                                              // to CWE-582

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server running on port " + PORT);

            // Infinite-loop that handles incoming connections
            while (true) {
                // Wait for a new connection...
                Socket socket = serverSocket.accept();
                System.out.println("Client connected on socket: " + socket.toString());

                // Make a ClientHandler for the newly-connected socket
                ClientHandler clientHandler = new ClientHandler(socket);
                clients.add(clientHandler);
                //Compliant with CWE-572, Uses start() and not run()
                clientHandler.start(); // Invoke the thread's `run` method
            }
        } catch (IOException exception) {
            System.err.println("Internal server error: " + exception.getMessage());
        }
    }

    /**
     * Method that displays a string from sender to all other clients in the
     * ChatServer.
     * 
     * @param message The message to be sent.
     * @param sender  The client that's sending the message.
     */
    public static void sendMessage(String message, ClientHandler sender) {
        for (ClientHandler client : clients) {
            //Compliant with CWE-481, is a comparison and not an assignment
            if (client != sender) {
                client.sendMessage(message);
            }
        }
    }

    /**
     * Method that removes a client from the set of connected clients.
     * 
     * @param client The client to be removed.
     */
    public static void removeClient(ClientHandler client) {
        clients.remove(client);
        try {
            client.finalize();
        }
        catch (Throwable throwedException) {
            throwedException.getMessage();
        }
    }
}