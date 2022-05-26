package com.wu.dao;

import com.wu.domain.UserLogBean;

import java.sql.SQLException;
import java.util.List;

public interface LogDao {
    public void userLog(UserLogBean logInfo) throws SQLException;

    public List<UserLogBean> getUserLog() throws SQLException;
}
