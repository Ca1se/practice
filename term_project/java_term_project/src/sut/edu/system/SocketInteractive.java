package sut.edu.system;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class SocketInteractive implements Interactive {
    private static final int kBufferSize = 1024;

    private Socket socket;
    private InputStream input;
    private OutputStream output;
    private byte[] buffer;
    public SocketInteractive(Socket socket) throws IOException {
        this.socket = socket;
        this.input = socket.getInputStream();
        this.output = socket.getOutputStream();
        buffer = new byte[kBufferSize];
    }

    @Override
    public String PullMessage() {
        try {
            int first = input.read();
            if(first == -1) {
                return null;
            }
            int second = input.read();
            int length = (first << 8) + second;
            input.read(buffer, 0, length);
            return new String(buffer, 0, length, StandardCharsets.UTF_8);
        }catch(IOException e) {
            return null;
        }
    }

    @Override
    public void PushMessage(String msg) {
        try {
            byte[] bytes = msg.getBytes(StandardCharsets.UTF_8);
            output.write(bytes.length >> 8);
            output.write(bytes.length & 0xff);
            output.write(bytes);
        }catch(IOException e) {}
    }
}
