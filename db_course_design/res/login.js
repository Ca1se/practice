$(document).ready(function () {
    $('#btn_login').click(function () {
        var user_name = $('#username').val();
        var password = $('#password').val();
        if(user_name === '') {
            alert('用户名为空!');
            return;
        }else if(password === '') {
            alert('密码为空!');
            return;
        }
        
        var form_data = {
            id: 0,
            username: user_name,
            password: password.hashCode(),
        };

        $.ajax({
            type: "POST",
            url: "/login",
            data: JSON.stringify(form_data),
            success: function (response) {
                alert(response);
                window.location.href = '/';
            },
            error: function (xhr) {
                var text = xhr.responseText;
                alert(text.substring(text.indexOf('message') + 8));
            }
        });
    });
});

String.prototype.hashCode = function() {
    var hash = 0;
    if (this.length == 0) {
        return hash;
    }
    for (var i = 0; i < this.length; i++) {
        char = this.charCodeAt(i);
        hash = ((hash<<5)-hash)+char;
        hash = hash & hash; // Convert to 32bit integer
    }
    return hash + '';
}