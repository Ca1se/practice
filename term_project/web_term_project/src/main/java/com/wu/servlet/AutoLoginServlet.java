package com.wu.servlet;

import com.alibaba.fastjson.JSON;
import com.wu.domain.UserBean;
import com.wu.domain.UserJson;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "AutoLoginServlet", urlPatterns = "/autologin")
public class AutoLoginServlet extends HttpServlet {


    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        UserBean user = (UserBean) req.getSession().getAttribute("user");
        if(user != null) {
            UserJson userJson = new UserJson();
            userJson.setId(user.getId());
            userJson.setName(user.getUsername());

            String json = JSON.toJSONString(userJson);
            resp.getWriter().print(json);
            resp.setStatus(200);
        }else {
            resp.setStatus(404);
        }
    }
}
