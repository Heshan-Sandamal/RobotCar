/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package robotcar;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Heshan Sandamal
 */
public class NetworkConnector {

    private static final int port = 8080;
    private static String serverName = "192.168.43.165";
    private static Socket client;
    private static Socket clientSocket;

    private static InputStream inputStream;
    private static OutputStream outputStream;

    public static void ConnectToServer() throws IOException {

        System.out.println("Connecting to " + serverName + " on port " + port);
        client = new Socket(serverName, port);
        System.out.println("Connected Client is " + client.getRemoteSocketAddress());
        outputStream = client.getOutputStream();

    }

    public static void startServer() throws IOException {

            ServerSocket sSocket = new ServerSocket(5000);
            System.out.println("Server started at: " + new Date());

            //Wait for a client to connect
            clientSocket = sSocket.accept();
            System.out.println("Server accepts connection from " + clientSocket.getRemoteSocketAddress());

            inputStream = clientSocket.getInputStream();

            new Thread() {

                @Override
                public void run() {
                    try {
                        NetworkConnector.read();
                    } catch (IOException ex) {
                        Logger.getLogger(RobotCar.class.getName()).log(Level.SEVERE, null, ex);
                    }finally{
                        try {
                            clientSocket.close();
                        } catch (IOException ex) {
                            Logger.getLogger(NetworkConnector.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                }

            }.start();
        
    }

    public static void write(String cmd) throws IOException {
        DataOutputStream dOut = new DataOutputStream(outputStream);
        dOut.writeChars(cmd);
        
    }

    public static void read() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        StringBuilder sb = new StringBuilder();

        while (true) {
            StringBuilder clientData = new StringBuilder();
            int red = -1;
            byte[] buffer = new byte[1204]; // a read buffer of 5KiB
            byte[] redData;
            String redDataText;
            while ((red = inputStream.read(buffer)) > -1) {
                redData = new byte[red];
                System.arraycopy(buffer, 0, redData, 0, red);
                redDataText = new String(redData, "UTF-8"); // assumption that client sends data UTF-8 encoded
                //System.out.println("message part recieved:" + redDataText);
                clientData.append(redDataText);
                break;
            }
            processInputValue(clientData.toString());
            //write("val");

        }

    }

    public static void processInputValue(String inputVal) {
        System.out.println(inputVal);
    }

}
