package sut.edu.log;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;

public class FileUtil {
    private BufferedWriter writer;
    private RandomAccessFile reader;

    public FileUtil(String filePath) throws IOException {
        writer = new BufferedWriter(new FileWriter(filePath, true));
        reader = new RandomAccessFile(filePath, "r");
    }

    public void append(String str) throws IOException {
        writer.write(str);
    }

    public void appendNewLine(String str) throws IOException {
        writer.write(str);
        writer.newLine();
    }

    public String readLine() throws IOException {
        return reader.readLine();
    }

    public void resetReader() throws IOException {
        reader.seek(0);
    }

    public void flushWriter() throws IOException {
        writer.flush();
    }

    public void close() throws IOException {
        writer.close();
        reader.close();
    }
}
