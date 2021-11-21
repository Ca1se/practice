package skt;

import java.io.BufferedReader;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class Server {
    private static final int kServerPort = 55533;
    private static final int kBufferSize = 1024;
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(kServerPort);

        Socket socket = server.accept();
                
        InputStream inputStream = socket.getInputStream();
        byte[] bytes;

        while (true) {
            int first = inputStream.read();
            if(first==-1){
                break;
            }
            int second = inputStream.read();
            int length = (first << 8) + second;
            bytes = new byte[length];
            inputStream.read(bytes);
            System.out.println("get message from client: " + new String(bytes, "UTF-8"));
        }

        inputStream.close();
        socket.close();
        server.close();
    }
}
