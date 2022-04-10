$(document).ready(function () {
    var cookie = document.cookie;
    if (cookie === '') {
        return;
    }

    $.ajax({
        type: "GET",
        url: "/user/username",
        success: function (response) {
            $('#login_href').replaceWith(`<button class=\"hlink_button\" onclick=\"quit()\">退出</button><button class=\"hlink_button\" onclick=\"window.location.href=\'user_quz.html\'\">${response.username}</button>`);
        },
        error: function() {
            document.cookie = 'session_id=; expires=Thu, 01 Jan 1970 00:00:00 GMT';
        }
    });
});

function quit() {
    $.ajax({
        type: "GET",
        url: "/user/quit"
    });

    window.location.href='index.html';
}
