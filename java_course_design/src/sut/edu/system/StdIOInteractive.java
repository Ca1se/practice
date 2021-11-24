package sut.edu.system;

import java.util.Scanner;

public class StdIOInteractive implements Interactive {
    private Scanner scanner;
    public StdIOInteractive() {
        scanner = new Scanner(System.in);
    }
    @Override
    public String PullMessage() {
        return scanner.nextLine();
    }

    @Override
    public void PushMessage(String msg) {
        System.out.println(msg);
    }

}
