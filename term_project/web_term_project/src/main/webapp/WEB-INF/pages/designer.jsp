<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page session="true" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Nice Paint - 新建</title>
        <link rel="stylesheet" href="styles/global.css">
        <link rel="stylesheet" href="styles/designer.css">
        <script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.6.0.min.js" type="text/javascript"></script>
        <script src="scripts/designer.js" type="module"></script>
        <script src="scripts/login.js" type="text/javascript"></script>
        <script type="text/javascript">
            function checkLogin() {
                location.href="LoginPage";
            }

            $(function () {
                autoLogin(function () {}, checkLogin);
            });
        </script>
    </head>
    <body>
        <div class="content">
            <header>
                <div class="return"><a href="WorksPage"></a></div>
                <div class="filename"><input type="text" name="filename" placeholder="未命名文件"></div>
                <div class="btn_box">
                    <a class="save button"><div>保存</div></a>
                    <a class="download button"><div style="cursor: pointer;">下载</div></a>
                    <a class="to-works button" href="WorksPage"><div>我的文件</div></a>
                </div>
                
            </header>
            <section>
                <div class="con_left">
                    <div class="title"><li>图形</li></div>
                    <div class="shpbtn_field">
                        <a class="shape_btn" draggable="true" id="rect"></a>
                        <a class="shape_btn" draggable="true" id="triangle"></a>
                        <a class="shape_btn" draggable="true" id="circle"></a>
                        <a class="shape_btn" draggable="true" id="hexagon"></a>
                    </div>
                    <div class="title"><li>属性</li></div>
                    <div class="toobtn_field">
                        <div class="tfield">
                            <div>x:<input class="attri_input" type="number" id="x_in"><span>px</span></div>
                            <div>y:<input class="attri_input" type="number" id="y_in"><span>px</span></div>
                            <div>z:<input class="attri_input" type="number" id="z_in"><span>px</span></div>
                        </div>
                        <div class="tfield">
                            <div>w:<input class="attri_input" type="number" id="w_in"><span>px</span></div>
                            <div>h:<input class="attri_input" type="number" id="h_in"><span>px</span></div>
                            <div>r:<input class="attri_input" type="number" id="r_in"><span style="font-size: 15px;">deg</span></div>
                        </div>
                        <div class="tfield" style="text-align: center;">
                            <div style="font-size: 15px">color:<input class="attri_input" id="color_in" style="width: 60px;"></div>
                            <div>fill:<input class="attri_input" type="checkbox" id="fill_in"></div>
                        </div>
                        <div class="tfield" style="text-align: center">
                            <button id="delete_shape">删除图元</button>
                        </div>
                    </div>
                </div>
                <div class="con_right">
                    <div class="canvas_layout">
                        <canvas id="back-canvas" width="1920px" height="1080px"></canvas>
                        <div id="wrapper">
                            <div id="container"></div>
                        </div>
                    </div>
                </div>
            </section>
        </div>
        <div id="work_id" style="visibility: hidden"><%=session.getAttribute("workId")%></div>
    </body>
</html>