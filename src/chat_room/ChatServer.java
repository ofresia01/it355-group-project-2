package chat_room;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.locks.lock;
import java.util.concurrent.locks.ReentrantLock;

/*
 * Class that acts as the server host and facilitates all client interactions from ClientHandler.
 * No untrustworthy methods are passed immutable objects - conformant to CWE-374.
 * All multiple condition expressions handle the default case - conformant to CWE-478
 * Singleton Pattern is not used in this thread-intensive enironment - conformant to CWE-543
 */
public class ChatServer {
    // Static member fields declared final - conformant to CWE-500
    private static final int PORT = 8080; // Standard port for localhost
    private static int messagesRecieved = 0;
    private static Set<ClientHandler> clients = new HashSet<ClientHandler>(); // The set of clients currently connected.
                                                                              // Set is private and static, conformant
                                                                              // to CWE-582

    
    private static final Lock lock = new ReentrantLock();

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
        } finally {
            //On exit, print total number of messages server recieved
            System.out.println("Messages Recieved by Server: " + messagesRecieved);
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
            }//Default case here is that sender and reciever are the same so no message is sent, would be an empty block so its removed.
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

    /**
     * Method to update messagesRecieved value
     */
    public static void addMessageCount(){
        
        //Synchronization is properly setup so that only one Thread is accessing, conformant to CWE-362
        //Operation of updating shared resource is placed in a lock to prevent a race condition, conformant to CWE-366
        //Access to this shared datafield is synchronzied, conformant to CWE-567
        //This synchronized block is not empty and unnecessarily slows program, conformant to CWE-585
        //Lock here
        lock.lock();

        //Update Value
        messagesRecieved++;

        //Unlock here
        lock.unlock();
    }
}