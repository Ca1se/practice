package com.wu.dao;

import com.wu.domain.ShapeBean;
import com.wu.domain.WorkBean;

import java.sql.SQLException;
import java.util.List;

public interface WorkDao {
    public void saveWork(WorkBean work, List<ShapeBean> shapes) throws SQLException;
    public void updateWork(WorkBean work, List<ShapeBean> shapes) throws SQLException;
}
