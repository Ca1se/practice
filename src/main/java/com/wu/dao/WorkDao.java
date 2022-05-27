package com.wu.dao;

import com.wu.domain.ShapeBean;
import com.wu.domain.UserBean;
import com.wu.domain.WorkBean;
import com.wu.domain.WorkJson;

import java.sql.SQLException;
import java.util.List;

public interface WorkDao {
    public void saveWork(WorkBean work, List<ShapeBean> shapes) throws SQLException;
    public void updateWork(WorkBean work, List<ShapeBean> shapes) throws SQLException;
    public List<WorkJson> getWorks(UserBean user) throws SQLException;
    public List<ShapeBean> getShapes(WorkBean work) throws SQLException;
}
