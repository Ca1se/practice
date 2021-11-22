package sut.edu.system;

import sut.edu.db.Database;

import java.util.Scanner;

public class ScannerManager extends Manager {
    private Scanner scanner;
    public ScannerManager(Database db, Scanner scanner) {
        super(db);
        this.scanner = scanner;
    }
}
