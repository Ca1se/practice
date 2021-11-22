package sut.edu.system;

import sut.edu.db.DBConnectionInfo;
import sut.edu.db.Database;

import java.io.InputStream;

public class StreamManager extends Manager {
    private InputStream stream;
    public StreamManager(Database db, InputStream stream) {
        super(db);
        this.stream = stream;
    }
}
