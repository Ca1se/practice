package skt;

import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class Client {
    private static final String kServerAddr = "127.0.0.1";
    private static final int kServerPort = 55533;
    public static void main(String[] args) throws Exception {
        Socket socket = new Socket(kServerAddr, kServerPort);
        
        OutputStream outputStream = socket.getOutputStream();
        
        byte[] bytes = "你好，我是小娜。".getBytes(StandardCharsets.UTF_8);
        System.out.println(bytes.length);
        outputStream.write(bytes.length >> 8);
        outputStream.write(bytes.length & 0xff);

        outputStream.write(bytes);

        outputStream.close();
        socket.close();
    }
}
