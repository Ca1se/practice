package com.wu.servlet;

import com.alibaba.fastjson.JSON;
import com.wu.dao.WorkDao;
import com.wu.dao.WorkDaoImpl;
import com.wu.domain.ShapeBean;
import com.wu.domain.UserBean;
import com.wu.domain.WorkBean;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;


@WebServlet(name = "UploadServlet", urlPatterns = "/upload")
public class UploadServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doPost(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        UserBean user = (UserBean) req.getSession().getAttribute("user");
        if(user != null) {
            try {
                boolean update = Boolean.parseBoolean(req.getParameter("update"));
                String work_name = req.getParameter("work_name");
                String payload = req.getParameter("shape_list");
                List<ShapeBean> shapes = JSON.parseArray(payload, ShapeBean.class);

                WorkBean work = new WorkBean();
                work.setName(work_name);
                work.setAuthor_id(user.getId());
                WorkDao dao = new WorkDaoImpl();
                if(update) {
                    Integer work_id = Integer.parseInt(req.getParameter("work_id"));
                    work.setId(work_id);
                    dao.updateWork(work, shapes);
                }else {
                    dao.saveWork(work, shapes);
                }
                resp.setStatus(200);
            }catch (SQLException e) {
                e.printStackTrace();
                resp.setStatus(500);
            }
        }else {
            resp.setStatus(404);
        }
    }
}
